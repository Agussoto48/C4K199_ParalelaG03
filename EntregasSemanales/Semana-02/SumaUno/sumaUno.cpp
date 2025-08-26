
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
 
 long total = 0;
 
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
   Al igual que de Pi, usamos los pipes para compartir memoria,
   nada más que esta vez se crea un pipe por hijo por tema de
   rendimiento, es muy lento si se comparte un solo pipe para todo
 */
void ForkTest( int procesos, long &total ) {
   int proceso, pid;
   int fds[procesos][2];

   for ( proceso = 0; proceso < procesos; proceso++ ) {
      pipe(fds[proceso]);
      pid = fork();
      if ( ! pid ) {
         close(fds[proceso][0]);
         long suma = 0;
         AddOne(suma);
         write(fds[proceso][1], &suma, sizeof(long));
         close(fds[proceso][1]);
         exit(0);
      }
      else {
         close(fds[proceso][1]);
      }
   }
   for ( proceso = 0; proceso < procesos; proceso++ ) {
      int status;
      pid_t pid = wait( &status );
   }
   for(proceso = 0; proceso < procesos; proceso++){
      long rec = 0;
      read(fds[proceso][0], &rec, sizeof(long));
      close(fds[proceso][0]);
      total += rec;
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
    int proceso;
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
 