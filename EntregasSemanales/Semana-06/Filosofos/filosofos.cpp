#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include "../adaptaciones_pthreads/Mesa.hpp"


Mesa *mesa = new Mesa();

/*
 *  Philosophers code
 */
void * Filosofo(void* arg) {
   int i;
   int eat, think;
   int id = *(int*)arg;

   srand( getpid() );
   for ( i = 0; i < 10; i++ ) {	// Do a round for thinking and eating
      think = rand() & 0xfffff;
      usleep( think );
      mesa->pickup(id);
      mesa->print();
      //printf( "El filósofo %d está comiendo\n", cual );
      eat = rand() & 0xfffff;
      usleep( eat );
      mesa->putdown(id);
      //printf( "El filósofo %d está pensando\n", cual );
      mesa->print();
      think = rand()  & 0xfffff;
      usleep( think );
   }

   return NULL;

}
/*
 *
 */
int main( int argc, char ** argv ) {
   long workers;
   pthread_t hilos[FILOMAX];
   int ids[FILOMAX];


   workers = 5;
   if ( argc > 1 ) {
      workers = atol( argv[ 1 ] );
   }

   for(int i = 0; i < workers; i++){
    ids[i] = i;
    pthread_create(&hilos[i], NULL, Filosofo, &ids[i]);
   }
   for(int i = 0; i < workers; i++){
    pthread_join(hilos[i], NULL);
   }

   printf( "\nNormal end of execution.\n" );

}