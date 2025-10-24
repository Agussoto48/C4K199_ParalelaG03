/*
 * Calcula el numero PI utilizando una serie "infinita"
 * Debe recibir la cantidad de iteraciones como parametro
 *
 *   pi = (-1)^i x 4/(2xi + 1)
 *
 *  Autor: Programacion Paralela y Concurrente (Francisco Arroyo)
 *  Fecha: 2025/Ago/18
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include<time.h>
#include<omp.h>


/*
   Realiza la acumulacion de terminos desde una posicion inicial hasta un termino final
*/
double calcularSumaParcialPi( double Pi[], int proceso, long inicial, long terminos ) {
   double casiPi = 0;
   double alterna = 4;
   long divisor = 0;
   long termino;

   for ( termino = inicial; termino < terminos; termino++ ) {
      divisor = termino + termino + 1;
      casiPi += alterna/divisor;		
      alterna *= -1;			
   }
   Pi[ proceso ] = casiPi;	
   return casiPi;			
}


int main( int argc, char ** argv ) {
   long terminos, inicio, fin;
   int pid;
   double casiPi[ 10 ] = { 0 };

   terminos = 1000000;
   if ( argc > 1 ) {
      terminos = atol( argv[ 1 ] );
   }

   int hilos = 10;
   omp_set_num_threads(hilos);

   for (int proceso = 0; proceso < 10; proceso++ ) {

      inicio = proceso * terminos/10;
      fin = (proceso + 1) * terminos/10;
      if (!pid){
         double resultado = calcularSumaParcialPi(casiPi, proceso, inicio, fin );
      } else {
         printf("Creating process %d: starting value %ld, finish at %ld\n", pid, inicio, fin );
      }
   }

   printf( "Valor calculado de Pi es \033[91m %g \033[0m con %ld terminos\n", casiPi[ 0 ], terminos );

}