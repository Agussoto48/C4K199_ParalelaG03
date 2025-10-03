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
#define RED "\33[31m"
#define GREEN "\33[32m"
#define YELLOW "\33[33m"
#define BLUE "\33[34m"
#define RESET "\33[0m"



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
   int i, resultado;
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
      sleep(1);
      for(int i = 0; i < 5; i++){
         invasor( i, juego);
         usleep(rng(80000, 90000));
      }
      _exit( 0 );
   }

   // Espera que los participantes finalicen
   for ( i = 1; i <= participantes; i++ ) {
      wait( &resultado );
   }
   
   wait( &resultado );  // Espera por el invador

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
      receiver.Recibir(&juego, sizeof(RondaPapa), 0);
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
         //std::cout << "(" << id << ") estoy esperando" << std::endl;
         receiver.Recibir(&juego, sizeof(RondaPapa), 0);
         if(juego.mtype == 40){
            receiver.Recibir(&juego, sizeof(RondaPapa), 0);
            std::cout << YELLOW << "Invasor denegado por (" << id << ")" << RESET << std::endl;
         }
      }
      //Zona critica
      else{
         turno.Wait();
         std::cout<< BLUE << "Es mi turno("<<id<<")" << RESET << std::endl;
         
         valorPapa(&juego.valor_papa);
         pasarPapa(&juego);
         //Sale del juego si perdió
         if(juego.valor_papa == 1){
            juego.cuenta_jugadores -= 1;
            juego.estados[id-1] = false;
            juego.valor_papa = rng(5, 10);
            std::cout << RED << "Papa exploto" << RESET << std::endl;
            std::cout<< RED << "Jugador("<<id<<") sale" << RESET << std::endl;
         }
         for(int i = 0; i < participantes; i++){
            if(!(juego.estados[i] && i == id-1))
               sender.Enviar(&juego, sizeof(RondaPapa), 2025);
         }
         //Esperar entre 0.6 a 0.8 segundos
         usleep(rng(60000, 80000));
         turno.Signal();
      }
   }
   if(juego.cuenta_jugadores == 1 && juego.estados[id-1]){
      std::cout << GREEN << "Jugador (" << id << ") gana el juego" << RESET << std::endl;
   }
   _exit( 0 );
}
/**
  *   Código para el invasor
  *   Manda mensajes al azar a los participantes de la ronda
  *
 **/
void invasor( int id, struct RondaPapa juego  ) {
   juego.mtype = 40;
   juego.posicion_papa = 1;
   juego.valor_papa = rng(5, 10);
   sender.Enviar(&juego, sizeof(RondaPapa), 40);
   std::cout<< YELLOW << "Paquete sospechoso enviado" << RESET << std::endl;
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
   do{
      juego->posicion_papa += operacion;
      if(juego->posicion_papa < 1){
         juego->posicion_papa = 10;
      }
      if(juego->posicion_papa > 10){
         juego->posicion_papa = 1;
      }
   } while(!juego->estados[juego->posicion_papa - 1]);
   std::cout << "[";
   for(int i = 0; i < participantes; i++){
      std::cout << juego->estados[i] << ", ";
   }
   std::cout << "]" << std::endl;
   //std::cout << juego->posicion_papa << std::endl;
   return juego->posicion_papa;
}
int rng(int min, int max){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(generator);
}