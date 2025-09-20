#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include "../Mesa/Mesa.hpp"


struct FiloMesa {
   Mesa redonda;
};

/*
 *  Philosophers code
 */
int Filosofo( int cual, Mesa * mesa ) {
   int i;
   int eat, think;

   srand( getpid() );
   for ( i = 0; i < 10; i++ ) {	// Do a round for thinking and eating
      think = rand() & 0xfffff;
      usleep( think );
      mesa->pickup( cual );
      mesa->print();
      //printf( "El filósofo %d está comiendo\n", cual );
      eat = rand() & 0xfffff;
      usleep( eat );
      mesa->putdown( cual );
      //printf( "El filósofo %d está pensando\n", cual );
      mesa->print();
      think = rand()  & 0xfffff;
      usleep( think );
   }

   exit( 0 );

}


/*
 *
 */
int main( int argc, char ** argv ) {
   long workers;
   int worker, pid, memId;
   FiloMesa * filoMesa;
   Mesa * mesa = new Mesa();


   workers = 5;
   if ( argc > 1 ) {
      workers = atol( argv[ 1 ] );
   }

// Create shared memory area and copy object image to it
   memId = shmget( IPC_PRIVATE, sizeof( struct FiloMesa ), IPC_CREAT | 0600 );
   if ( -1 == memId ) {
      perror( "Fail to create shared memory segment" );
      exit( 1 );
   }

   filoMesa = (struct FiloMesa *) shmat( memId, NULL, 0 );
   new (&filoMesa->redonda) Mesa();
   //¿memcpy(filoMesa, mesa, sizeof( Mesa ) );	// Copy object to shared segment

// Create philosophers
   for ( worker = 0; worker < workers; worker++ ) {
      pid = fork();
      if ( ! pid ) {
         Filosofo( worker, & filoMesa->redonda );
      }
   }

   for ( worker = 0; worker < workers; worker++ ) {
      int status;
      wait( &status );
   }
   printf( "\nNormal end of execution.\n" );
   shmdt( filoMesa );
   shmctl( memId, IPC_RMID, NULL );

}