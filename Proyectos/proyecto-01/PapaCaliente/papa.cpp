/*
 *  Ejemplo base para el problema de la ronda
 *
 *  CI-0117 Programacion concurrente y paralela
 *  Fecha: 2025/Set/16
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include<random>
#include "Buzon.hpp"
#include "Semaforo.hpp"

#define MaxParticipantes 10

// Variable global para el número de participantes
int participantes = MaxParticipantes;

/**
  *  Estructura para el paso de mensajes entre procesos
  *  posicion_papa: almacena que jugador tiene la papa
  *  valor_papa: valor para ver si explota o no
  *  cuenta_jugadores: cuenta de los jugadores activos
  *  Estado jugadores: array para ver si un jugador esta vivi
  *  clockwise: booleano para saber que dirección se juega
  *   -True: Derecha ->
  *   -False: Izquierda <-
 **/
struct RondaPapa {
   long mtype;
   int posicion_papa;
   int valor_papa;
   int cuenta_jugadores;
   bool clockwise;
   bool estados[10];
};
extern Semaforo turno(1);

//Inicializamos buzones
Buzon sender(true);
Buzon receiver(false);

//Declaracion de funcciones 
int valorPapa(int *papa);
int pasarPapa(RondaPapa* juego);
bool comprobarMensaje();

void manejo_jugador( int id , struct RondaPapa juego);
void invasor( int id , struct RondaPapa juego );
int rng(int min, int max);


int main( int argc, char ** argv ) {
   int i, j, resultado;
   if ( argc > 1 ) {
      participantes = atoi( argv[ 1 ] );
   }
   if ( participantes <= 0 ) {
      participantes = MaxParticipantes;
   }

   struct RondaPapa juego;
   //Estas variables por default ahora
   juego.clockwise = true;
   juego.posicion_papa = 1;
   juego.valor_papa = rng(5, 10);
   for(int i = 0; i < 10; i++){
      juego.estados[i] = true;
   }
   //printf( "Creando una ronda de %d participantes\n", participantes );
   for ( i = 1; i <= participantes; i++ ) {
      if ( ! fork() ) {
         juego.mtype = 2025;
         juego.cuenta_jugadores = i;
         //std::cout<<"Estuve aqui" << std::endl; 
         manejo_jugador( i, juego);
      }
   }
   // Creación del proceso invasor
   if ( ! fork() ) {
      invasor( i, juego);
   }

   // Espera que los participantes finalicen
   for ( i = 1; i <= participantes; i++ ) {
      j = wait( &resultado );
   }
   
   j = wait( &resultado );  // Espera por el invador

   return 0;

}


//------Definicion de funciones---------

/**
  *   Código para cada participante
  *   Debe cambiar el valor de la papa y determinar si explotó
 **/
void manejo_jugador(int id, struct RondaPapa juego){
   //Esperamos hasta que todos los jugadores estén
   if(juego.cuenta_jugadores < 10){
      receiver.Recibir(&juego, sizeof(RondaPapa), 2025);
   }
   //Cuando llegue el ultimo le notifica a los demás
   else{
      for(int i = 1; i < participantes; i++)
         sender.Enviar(&juego, sizeof(RondaPapa), 2025);
   }

   //------------------Empezó el juego------------------------
   while(juego.estados[id-1] && juego.cuenta_jugadores > 1){
      //Si no es su turno, espera hasta un mensaje nuevo
      if(juego.posicion_papa != id){
         receiver.Recibir(&juego, sizeof(RondaPapa), 2025);
         //Lock
      }
      //Zona critica
      else{
         turno.Wait();
         std::cout<<"Es mi turno("<<id<<")" << std::endl;
         
         valorPapa(&juego.valor_papa);
         //std::cout<<"Estuve aqui V" << std::endl; 
         pasarPapa(&juego);
         //std::cout<<"Estuve aqui P" << std::endl; 
         int sendCount = juego.cuenta_jugadores;
         //Sale del juego si perdió
         if(juego.valor_papa == 1){
            juego.cuenta_jugadores -= 1;
            juego.estados[id-1] = false;
            juego.valor_papa = rng(5, 10);
            std::cout<<"Jugador("<<id<<") sale" << std::endl;
         }
         //std::cout<<"Estuve aqui Perdi" << std::endl; 
         for(int i = 1; i < sendCount; i++){
            sender.Enviar(&juego, sizeof(RondaPapa), 2025);
         }
         //std::cout<<"Estuve aqui Envio" << std::endl; 
         turno.Signal();
      }
   }
   if(juego.cuenta_jugadores == 1 && juego.estados[id-1]){
      std::cout << "Jugador (" << id << ") gana el juego" << std::endl;
   }
   _exit( 0 );
}
/**
  *   Código para el invasor
  *   Manda mensajes al azar a los participantes de la ronda
  *
 **/
void invasor( int id, struct RondaPapa juego  ) {

   _exit( 0 );

}
/**
  *  Aplica las reglas de Collatz al valor de la papa
  *
 **/
int valorPapa(int *papa) {
   if(*papa % 2 == 0){
      *papa /= 2;
   }
   else{
      *papa = (3 * (*papa)) + 1;
   }
   return *papa;
}
int pasarPapa(struct RondaPapa* juego){
   int operacion = (juego->clockwise) ? 1 : -1;
   int index;
   do{
      index = juego->posicion_papa;
      juego->posicion_papa += operacion;
      if(juego->posicion_papa < 1){
         juego->posicion_papa = 10;
      }
      if(juego->posicion_papa > 10){
         juego->posicion_papa = 0;
      }
   } while(!juego->estados[index]);
   std::cout << "[";
   for(int i = 0; i < participantes; i++){
      std::cout << juego->estados[i] << ", ";
   }
   std::cout << "]" << std::endl;
   return juego->posicion_papa;
}
int rng(int min, int max){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(generator);
}




//Con estos comentarios funciona la base
         /*juego.cuenta_jugadores -= 1;
         juego.posicion_papa += 1;
         if(juego.posicion_papa > 10){
            juego.posicion_papa = 1;
         }*/