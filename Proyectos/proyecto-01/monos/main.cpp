/*
 *  Ejemplo base para el problema de los monos
 *
 *  CI-0117 Programacion concurrente y paralela
 *  Fecha: 2025/Set/16
 *
 */

/*
#include <string.h>
#include <sys/sem.h>
#include <time.h>
#include <stdbool.h>
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<iostream>
#include<random>
#include "Barranco.hpp"



enum Direccion { IzqDer = 1, DerIzq = 2};

struct compartido {
   Barranco barranco;
};


//Declaracion de funciones
void mono_cruce(int mono, int lado, Barranco * escenario);
int rng(int min, int max);

//Main
int main( int argc, char ** argv ) {
    int numMonos = 0, shmId, resultado;

    //Definicion de cuantos monos hay depende de los parametros
    if ( argc > 1 ) {
        numMonos = atoi( argv[ 1 ] );
    }
    if ( numMonos <= 0 ) {
        numMonos = MONOS_DEFAULT;
    }
    struct compartido * escenario;
    //Creacion de memoria compartida
        shmId = shmget( IPC_PRIVATE, sizeof( struct compartido ), IPC_CREAT | 0600 );
        if ( -1 == shmId ) {
            perror( "main shared memory create" );
            exit( 1 );
        }
        escenario = (struct compartido *) shmat( shmId, NULL, 0 );
        new (&escenario->barranco) Barranco(numMonos);
        escenario->barranco.setState();
        if ( (void *) -1 == escenario ) {
            perror( "main Shared Memory attach" );
            exit( 1 );
        }
    //Fin de creacion de memoria compartida
    printf( "Creando una manada de %d monos\n", numMonos);
    for (int mono = 0; mono < numMonos; mono++ ) {
        //Definir la direccion del mono tanto la cuerda que le toca
        int lado = rng(1,2);
        if (!fork()) {
            //Decidir cual direccion le toca al mono
            if (lado == 1) {
                mono_cruce(mono, lado, &escenario->barranco);
            }
            else{ 
                mono_cruce(mono, lado, &escenario->barranco);
            }
        }
    }

    // Wait for all processes before destroy shared memory segment and finish
    for (int id_mono = 1; id_mono <= numMonos; id_mono++ ) {
        wait( &resultado );
    }
    //Destruir memoria compartida
    resultado = shmdt( escenario );
    shmctl( shmId, IPC_RMID, 0 );

    return 0;
}

//Definicion de funciones

/*
 *  Método para representar a cada mono
 *  Recibe como parámetro la dirección en la que cada mono quiere cruzar
 *  Cada mono debe respetar las reglas impuestas en la definición del problema
 */
void mono_cruce(int mono, int lado, Barranco * escenario) {
    int entrar, cruzar;
    int cuerda_asignacion = rng(1, 2);

    //Asignamos valores a los arreglos para controlar los monos
    escenario->setDireccion(mono, lado);
    escenario->setCuerda(mono, cuerda_asignacion);
    switch (lado){
        case IZQUIERDA:
            std::cout << "El mono " << mono << " es del lado izquierdo, le toca cuerda " << cuerda_asignacion << "\n";
            break;
        case DERECHA:
            std::cout << "El mono " << mono << " es del lado derecho, le toca cuerda "  << cuerda_asignacion << "\n";
            break;
    }
    //Logica de la cuerda
    //---------Entrar-----------
    entrar = rng(200000, 500000);
    usleep(entrar);
    while(escenario->getEstado(mono) == 0){
        if(cuerda_asignacion == 1){
            escenario->entrarCuerda1(mono);     
        }
        else if(cuerda_asignacion == 2){
            escenario->entrarCuerda2(mono);
        }   
    }
    //escenario->cuentaPuentes();
    escenario->print();
    //--------Cruzar--------
    cruzar = rng(200000, 500000);
    usleep(cruzar);
    if(cuerda_asignacion == 1){
        escenario->cruzarCuerda1(mono);
    }
    else if(cuerda_asignacion == 2){
        escenario->cruzarCuerda2(mono);
    }
    //escenario->cruzar(mono);
    //escenario->cuentaPuentes();
    escenario->print();
    //Fin de la logica de la cuerda

    _exit( 0 );	// Everything OK
}
int rng(int min, int max){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(generator);
}