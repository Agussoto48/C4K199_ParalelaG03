#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<iostream>
#include<random>
#include "Monitor.hpp"
#include "Shared_mem.hpp"

struct Informacion{
    Monitor monitor;
};



int EsperarTren( int cual, Monitor * monitor ) {
   int espera;

   monitor->esperarTren(cual);
   espera = random() & 0x3;
   sleep( espera );

   return espera;

}
int Abordar( int cual, Monitor * monitor  ) {
   int espera;

   espera = random() & 0x3;
   sleep( espera );

   return espera;

}

int Salir( int cual, Monitor * monitor  ) {
   int espera;
   monitor->Salir(cual); 
   espera = random() & 0x3;
   sleep( espera );

   return espera;

}
int Pasajero( int cual, Monitor * monitor ) {

    int espera;
   srand( getpid() );
   printf( "Se produjo un pasajero %d\n", cual );

   monitor->esperarTren(cual);
   std::cout<< std::endl << cual << "Espera el tren" << std::endl;
   espera = random() & 0x3;
   sleep( espera );
   monitor->Abordar(cual);
   std::cout<< std::endl << cual << "Abordó el tren" << std::endl;
   espera = random() & 0x3;
   sleep( espera );
   monitor->Salir(cual);
   std::cout<< std::endl << cual << "salió el tren" << std::endl;
   espera = random() & 0x3;
   sleep( espera );
   exit( 0 );

}

int main( int argc, char ** argv ) {
    long workers;
    int worker, pid;
    
    workers = 10;
    if ( argc > 1 ) {
        workers = atol( argv[ 1 ] );
    }
    Informacion * info;
    int shmid;
    shmid = shmget( IPC_PRIVATE, sizeof(struct Informacion), IPC_CREAT | 0600 );
    info = (struct Informacion *) shmat( shmid, NULL, 0 );
    new(&info->monitor) Monitor(workers);
    info->monitor.setState();

    // Create passengers
    for ( worker = 0; worker < workers; worker++ ) {
        pid = fork();
        if ( ! pid ) {
            Pasajero( worker, &info->monitor);
        }
    }

    for ( worker = 0; worker < workers; worker++ ) {
        int status;
        pid_t pid = wait( &status );
    }
    shmdt( info );
    shmctl( shmid, IPC_RMID, 0 );
    return 0;

}
