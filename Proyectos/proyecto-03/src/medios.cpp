#include <cstdio>
#include <random>
#include "VectorPuntos.h"
#include "LockMP.hpp"
#include<omp.h>

#define PUNTOS 100000
#define CLASES 17

int totalCambios = 0;

// Declaraciones de funciones
int rng(int min, int max);
void asignarPuntosAClases(long *clases, int modo);

int main(int cantidad, char **parametros)
{
   long cambios, clase, minimo, pto;
   Punto *punto;
   long casillas = CLASES;
   long muestras = PUNTOS;

   // Procesar los parámetros del programa
   // ...
   //------

   VectorPuntos *centros = new VectorPuntos(casillas);
   VectorPuntos *puntos = new VectorPuntos(muestras, 10); // Genera un conjunto de puntos limitados a un círculo de radio 10
   long clases[muestras];                                 // Almacena la clase a la que pertenece cada punto
   long contClases[casillas];

   asignarPuntosAClases(clases, 0); // Asigna los puntos a las clases establecidas

   do
   {
      // Coloca todos los centros en el origen
      // Promedia los elementos del conjunto para determinar el nuevo centro

      cambios = 0; // Almacena la cantidad de puntos que cambiaron de conjunto
                   // Cambia la clase de cada punto al centro más cercano

      totalCambios += cambios;

   } while (cambios > 0); // Si no hay cambios el algoritmo converge

   printf("Valor de la disimilaridad en la solución encontrada %g, con un total de %ld cambios\n", centros->disimilaridad(puntos, clases), totalCambios);

   // Con los valores encontrados genera el archivo para visualizar los resultados
   puntos->genEpsFormat(centros, clases, (char *)"ci0117.eps");
}

// Definición de funciones
int rng(int min, int max)
{
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<> dist(min, max);
   return dist(gen);
}
/**
 *  Coloca a cada punto en una clase de manera aleatoria
 *  Utiliza el vector de clases para realizar la asignación
 *
 **/
void asignarPuntosAClases(long *clases, int modo)
{
   long clase, pto;

   switch (modo)
   {
   case 0: // Aleatorio
      for (pto = 0; pto < PUNTOS; pto++)
      {
         clase = rand() % CLASES;
         clases[pto] = clase;
      }
      break;
   case 1: // A construir por los estudiantes
      break;
   }
}