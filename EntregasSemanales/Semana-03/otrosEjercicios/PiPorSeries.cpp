/**
  * Calcula el numero PI utilizando una serie "infinita"
  * Debe recibir la cantidad de iteraciones como parametro
  *
  *   pi = (-1)^i x 4/(2xi + 1)
  *
  *  Autor: Programacion Paralela y Concurrente (Francisco Arroyo)
  *  Fecha: 2025/Ago/21
  *
 **/

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include<sys/shm.h>
#include "../shared/Buzon.hpp"
#include<iostream>

#define KEY 0xA12345

struct resultado{
   long mtype;
   double answer;
};
/*
   Realiza la acumulacion de terminos desde una posicion inicial hasta un termino final
*/
double calcularSumaParcialPi( double Pi[], int proceso, long inicial, long terminos ) {
   double casiPi = 0;
   double alterna = 4;
   double divisor = 0;
   double termino;

   for ( termino = inicial; termino < terminos; termino++ ) {
      divisor = termino + termino + 1;		// 2 x termino + 1
      casiPi += alterna/divisor;		// 4 / (2xi + 1)
      alterna *= -1;				// Pasa de 4 a -4 y viceversa, para realizar la aproximacion de los terminos
   }
   return casiPi;			// Devuelve el resultado parcial

}


int main( int argc, char ** argv ) {
   long terminos, inicio, fin;
   int proceso;
   int pid;
   double casiPi[10] = { 0 };

   terminos = 1000000;
   if ( argc > 1 ) {
      terminos = atol( argv[ 1 ] );
   }

   Buzon sender(true);
   Buzon receiver(false);
   for ( proceso = 0; proceso < 10; proceso++ ) {
      inicio = proceso * terminos/10;
      fin = (proceso + 1) * terminos/10;
      /*struct resultado A;
      struct resultado B;
      A.mtype = 2025;
      B.mtype = 2025;
      A.answer = 15;
      sender.Enviar(&A, sizeof(A), 2025);
      receiver.Recibir(&B, sizeof(B), 2025);
      std::cout <<"\n\n" << B.answer << "\n\n";*/

      pid = fork();
      if (pid  == 0) {
         struct resultado res;
         res.mtype = 2000;
         res.answer = 0;
         res.answer = calcularSumaParcialPi( casiPi, proceso, inicio, fin );
         //std::cout << proceso << "Resultado pos calculo: " << res.answer << std::endl;
         sender.Enviar(&res, sizeof(res), 2000);
         exit(0);
      } else {
         /*struct resultado contenedor;
         contenedor.mtype = 2000;*/
         /*ssize_t a =*/ 
         //std::cout << "Resultado: " << a << " | " << res.answer << std::endl;
         printf("%d) Creating process %d: starting value %ld, finish at %ld\n",proceso , pid, inicio, fin );
      }
   }
   double pi = 0.0;
   for ( proceso = 1; proceso < 10; proceso++ ) {
      struct resultado contenedor;
      contenedor.mtype = 2000;
      contenedor.answer = 0;
      receiver.Recibir(&contenedor, sizeof(contenedor), 2000);
      pi += contenedor.answer;
   }
   for ( proceso = 0; proceso < 10; proceso++ ) {
      int status;
      wait( &status );
   }

   printf( "Valor calculado de Pi es \033[91m %g \033[0m con %ld terminos\n", pi, terminos );


}