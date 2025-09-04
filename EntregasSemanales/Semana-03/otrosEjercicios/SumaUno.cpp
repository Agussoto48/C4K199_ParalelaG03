
/*
 * Suma uno a un total mil veces por cada proceso generado
 * Recibe como parametro la cantidad de procesos que se quiere arrancar
 * Author: Programacion Concurrente (Francisco Arroyo)
 * Version: 2020/Ago/08
 */

 #include <stdlib.h>
 #include <stdio.h>
 #include <sys/types.h>
 #include <unistd.h>
 #include <sys/wait.h>
 #include <sys/time.h>
 #include "../shared/Buzon.hpp"
 
 long total = 0;
 
struct sumatoria{
    long mtype;
    long suma;
};

 /*
  *  Do some work, by now add one to a variable
  */
 void AddOne( long &suma ) {
   int i;
   for ( i = 0; i < 1000; i++ ) {
      usleep( 1 );
      suma++;  // Suma uno
   }
 }
 /*
   Serial test
 */
void SerialTest( int procesos, long &total ) {
   for (int proceso = 0; proceso < procesos; proceso++ ) {
      for (int i = 0; i < 1000; i++ ) {
         total++;    // Suma uno
      }
   }
 } 
 /*
   Fork test
   El envío de mensajes se hace mediante esta funcion, el total se suma con lo que recibe las estructura con el buzon
 */
void ForkTest( int procesos, long &total ) {
   int proceso, pid;
   Buzon sender(true);
   Buzon receiver(false);
   for ( proceso = 0; proceso < procesos; proceso++ ) {
      pid = fork();
      if ( ! pid ) {
        struct sumatoria A;
        A.mtype = 2025;
        A.suma = 0;
        AddOne(A.suma);
        sender.Enviar(&A, sizeof(A), 2025); 
         exit(0);
      }
   }
   for ( proceso = 0; proceso < procesos; proceso++ ) {
      int status;
      wait( &status );
   }
   for(proceso = 0; proceso < procesos; proceso++){
      struct sumatoria B;
      B.mtype = 2025;
      B.suma = 0;
      receiver.Recibir(&B, sizeof(B), 2025);
      total += B.suma;
   }
 }
 void startTimer( struct timeval * timerStart) {
    gettimeofday( timerStart, NULL );
 }
 /*
  *  time elapsed in ms
  */
 double getTimer( struct timeval timerStart ) {
    struct timeval timerStop, timerElapsed;
 
    gettimeofday(&timerStop, NULL);
    timersub(&timerStop, &timerStart, &timerElapsed);
    return timerElapsed.tv_sec*1000.0+timerElapsed.tv_usec/1000.0;
 }

 int main( int argc, char ** argv ) {
    long procesos;
    struct timeval timerStart;
    double used;
 
    procesos = 100;
    if ( argc > 1 ) {
       procesos = atol( argv[ 1 ] );
    }
    
    //Serial
    startTimer( & timerStart );
    total = 0;
    SerialTest( procesos, total);
    used = getTimer( timerStart );
    printf( "Serial version:      Valor acumulado por %ld procesos es \033[91m %ld \033[0m en %f ms\n", procesos, total, used );
 
    //Fork
    startTimer( & timerStart );
    total = 0;
    ForkTest( procesos, total);
    used = getTimer( timerStart );
    printf( "Fork   version:      Valor acumulado por %ld procesos es \033[91m %ld \033[0m en %f ms\n", procesos, total, used );
 
 }
 