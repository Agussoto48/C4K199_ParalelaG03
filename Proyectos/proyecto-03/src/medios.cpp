#include <cstdio>
#include <random>
#include "VectorPuntos.h"
#include "LockMP.hpp"
#include <omp.h>
#include <iostream>
#include <exception>

#define PUNTOS 1000
#define CLASES 17
#define RADIO_CIRCULO 10
enum modos
{
   ALEATORIO = 0,
   CAMBIO_CLASE = 1
};

int totalCambios = 0;

// Declaraciones de funciones
int rng(int min, int max);
void asignarPuntosAClases(long *clases_puntos, int modo, VectorPuntos *centros, VectorPuntos *puntos, long &cambios, long muestras, long casillas);

int main(int cantidad, char **parametros)
{
   long cambios = 0, casillas = CLASES, muestras = PUNTOS;
   int hilos;
   Punto *punto;

   if (cantidad > 3)
   {
      casillas = atoi(parametros[1]);
      muestras = atoi(parametros[2]);
      hilos = atoi(parametros[3]);
   }
   else
   {
      std::cerr << "Ingrese los parametros de forma correcta: ./exe <clases> <puntos> <hilos>\n";
      return 0;
   }

   VectorPuntos *centros = new VectorPuntos(casillas);
   VectorPuntos *puntos = new VectorPuntos(muestras, RADIO_CIRCULO);
   long *clases_puntos = new long[muestras];

   asignarPuntosAClases(clases_puntos, ALEATORIO, centros, puntos, cambios, muestras, casillas);
   do
   {
      cambios = 0;
      // Sacar promedio de los puntos en el area y asignar punto del centro
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

   printf("Valor de la disimilaridad en la solución encontrada %g, con un total de %ld cambios\n", centros->disimilaridad(puntos, clases_puntos), totalCambios);

   puntos->genEpsFormat(centros, clases_puntos, (char *)"ci0117.eps");

   delete centros;
   delete puntos;
   delete[] clases_puntos;

   return 0;
}

// Definición de funciones
int rng(int min, int max)
{
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<> dist(min, max);
   return dist(gen);
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