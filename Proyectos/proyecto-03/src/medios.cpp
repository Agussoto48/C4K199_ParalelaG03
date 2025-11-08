#include <cstdio>
#include <random>
#include "VectorPuntos.h"
#include <omp.h>
#include <iostream>
#include <exception>
#include <cstring>

#define PUNTOS 100000
#define CLASES 23
#define RADIO_CIRCULO 10
enum modos
{
   ALEATORIO = 0,
   CAMBIO_CLASE = 1
};

long totalCambios = 0;

// Declaraciones de funciones
bool analizarArgumentos(int cantidad, char **parametros, int &hilos, long &casillas, long &muestras);
void asignarPuntosAClases(long *clases_puntos, int modo, VectorPuntos *centros, VectorPuntos *puntos, long &cambios, long muestras, long casillas);

int main(int cantidad, char **parametros)
{
   long cambios = 0, casillas = CLASES, muestras = PUNTOS;
   int hilos = 1;

   if (!analizarArgumentos(cantidad, parametros, hilos, casillas, muestras))
   {
      return 0;
   }

   VectorPuntos *centros = new VectorPuntos(casillas);
   VectorPuntos *puntos = new VectorPuntos(muestras, RADIO_CIRCULO);
   long *clases_puntos = new long[muestras];

   asignarPuntosAClases(clases_puntos, ALEATORIO, centros, puntos, cambios, muestras, casillas);

   omp_set_num_threads(hilos);
   double inicio = omp_get_wtime();
   do
   {
      cambios = 0;
      // Sacar promedio de los puntos en el area y asignar punto del centro
      #pragma omp parallel for schedule(dynamic)
      for (int i = 0; i < casillas; i++)
      {
         double sumaX = 0, sumaY = 0;
         int cantidad = 0;
         for (int j = 0; j < muestras; j++)
         {
            if (clases_puntos[j] == i)
            {
               sumaX += (*puntos)[j]->getX();
               sumaY += (*puntos)[j]->getY();
               cantidad++;
            }
         }
         if (cantidad > 0)
         {
            (*centros)[i]->modificar(sumaX / cantidad, sumaY / cantidad);
         }
      }

      asignarPuntosAClases(clases_puntos, CAMBIO_CLASE, centros, puntos, cambios, muestras, casillas);

      totalCambios += cambios;

   } while (cambios > 0);
   double final = omp_get_wtime();

   std::cout << "Valor de la disimilaridad en la solución encontrada " << centros->disimilaridad(puntos, clases_puntos);
   std::cout << ", con un total de " << totalCambios << " cambios\n";

   std::cout << "Tiempo total de ejecucion: " << final - inicio << "s con " << hilos << " hilos";
   std::cout << ", " << casillas << " centros y " << muestras << " puntos totales" << std::endl;
   puntos->genEpsFormat(centros, clases_puntos, (char *)"ci0117.eps");

   delete centros;
   delete puntos;
   delete[] clases_puntos;

   return 0;
}

// Definición de funciones
bool analizarArgumentos(int cantidad, char **parametros, int &hilos, long &clases, long &puntos)
{
   bool condicion = true;
   for (int i = 1; i < cantidad; i++)
   {
      if (strncmp(parametros[i], "-t=", 3) == 0)
      {
         hilos = atoi(parametros[i] + 3);
      }
      else if (strncmp(parametros[i], "-p=", 3) == 0)
      {
         puntos = atol(parametros[i] + 3);
      }
      else if (strncmp(parametros[i], "-c=", 3) == 0)
      {
         clases = atol(parametros[i] + 3);
      }
      else
      {
         std::cerr << "ERROR: Parámetro desconocido: " << parametros[i] << "\n";
         condicion = false;
      }
   }
   return condicion;
}
void asignarPuntosAClases(long *clases_puntos, int modo, VectorPuntos *centros, VectorPuntos *puntos, long &cambios, long muestras, long casillas)
{
   long clase, pto;

   switch (modo)
   {
   case ALEATORIO:
      for (pto = 0; pto < muestras; pto++)
      {
         clase = rand() % casillas;
         clases_puntos[pto] = clase;
      }
      break;
   case CAMBIO_CLASE:
      #pragma omp parallel for reduction(+: cambios)
      for (int j = 0; j < muestras; j++)
      {
         long nuevaClase = centros->masCercano((*puntos)[j]);
         if (nuevaClase != clases_puntos[j])
         {
            clases_puntos[j] = nuevaClase;
            cambios++;
         }
      }
      break;
   }
}