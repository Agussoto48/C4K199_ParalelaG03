#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <thread>
#include <vector>
#include <sys/time.h>
#include <omp.h>
// Shared variables
long total;



/*
  Serial test
*/
long SerialTest( long hilos ) {
    long i, hilo;

    for ( hilo = 0; hilo < hilos; hilo++ ) {

        for ( i = 0; i < 1000; i++ ) {
            total++;
        }

    }

    return total;

}
void mpTest(){
    #pragma omp parallel for reduction(+:total)
    for (int i = 0; i < 1000; i++ ) {
        total++;
    }
}
long RaceCondition( long hilos ) {
    omp_set_num_threads(hilos);

    #pragma omp parallel
    {
        mpTest();
    }
    return total;

}


void startTimer( struct timeval * timerStart) {
   gettimeofday( timerStart, NULL );
}
double getTimer( struct timeval timerStart ) {
   struct timeval timerStop, timerElapsed;

   gettimeofday(&timerStop, NULL);
   timersub(&timerStop, &timerStart, &timerElapsed);
   return timerElapsed.tv_sec*1000.0+timerElapsed.tv_usec/1000.0;
}



int main( int argc, char ** argv ) {
    long hilos;
    double inicio, fin, tiempoTotal;


    hilos = 8;
    if ( argc > 1 ) {
        hilos = atol( argv[ 1 ] );
    }
    
    total = 0;
    inicio = omp_get_wtime();
    SerialTest( hilos );
    fin = omp_get_wtime();
    tiempoTotal = fin - inicio;
    printf( "Serial version:      total es \033[91m %ld \033[0m con %ld hilos, CPU time %g seconds\n", total, hilos, tiempoTotal);

    total = 0;
    inicio = omp_get_wtime();
    RaceCondition(hilos);
    fin = omp_get_wtime();
    tiempoTotal = fin - inicio;
    printf( "OpenMP:    total es \033[91m %ld \033[0m con %ld hilos, CPU time %g seconds\n", total, hilos, tiempoTotal);
}