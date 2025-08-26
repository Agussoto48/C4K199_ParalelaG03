/*
 * Suma uno a un total mil veces por cada proceso generado
 * Recibe como parametro la cantidad de procesos que se quiere arrancar
 * Author: Programacion Concurrente (Francisco Arroyo)
 * Version: 2020/Ago/08
 */

 #include <stdlib.h>
 #include <stdio.h>
 #include <unistd.h>
 #include <sys/time.h>
 
/*
    Resultados:
    1) 10 , 10000, ms: 0.021000
    2) 100, 100000, ms: 0.204000
    3) 1000, 1000000, ms: 2.503000
    4) 10000, 10000000, ms: 26.300000

*/


 /*
  *  Do some work, by now add one to a variable
  */
 long Add( long * suma ) {
    int i;
 
    for ( i = 0; i < 1000; i++ ) {
       (* suma)++;			// Suma uno
    }
 
    return *suma;
 
 }
 
 
 /*
   Serial test
 */
 void SerialTest( int procesos, long * total ) {
    int i, proceso;
 
    for ( proceso = 0; proceso < procesos; proceso++ ) {
 
       for ( i = 0; i < 1000; i++ ) {
          (* total)++;		// Add 1000 to total
       }
 
    }
 
 }
 
 
 /*
  *
  */
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
    long procesos = 10;
    long total = 0;
    struct timeval timerStart;
    double used;
 
    if ( argc > 1 ) {
       procesos = atol( argv[ 1 ] );
    }
 
    startTimer( & timerStart );
 
    SerialTest( procesos, &total );
 
    used = getTimer( timerStart );
 
    printf( "Version Serial: Valor acumulado por %ld procesos es \033[91m %ld \033[0m en %f ms\n", procesos, total, used );
 
 }
 