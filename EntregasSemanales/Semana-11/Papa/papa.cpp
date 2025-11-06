#include <iostream>
#include <omp.h>
#include <unistd.h>
#include <random>
#include "LockMP.hpp"
#include "SemaphoreMP.hpp"
#include "Condition_MP.hpp"

#define MAX_PARTICIPANTES 10
#define RED "\33[31m"
#define GREEN "\33[32m"
#define YELLOW "\33[33m"
#define BLUE "\33[34m"
#define RESET "\33[0m"

int rng(int min, int max) {
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<> dist(min, max);
   return dist(gen);
}

struct RondaPapa {
   int posicion_papa;
   int valor_papa;
   int cuenta_jugadores;
   bool clockwise;
   bool estados[MAX_PARTICIPANTES];
};

SemaphoreMP turno(1);         
LockMP mutex;                 
Condition_MP cond;            

int participantes = MAX_PARTICIPANTES;

// Funciones del juego
int valorPapa(int *papa) {
   if (*papa % 2 == 0) *papa /= 2;
   else *papa = (3 * (*papa)) + 1;
   return *papa;
}

int pasarPapa(RondaPapa* juego) {
   int operacion = (juego->clockwise) ? 1 : -1;
   do {
      juego->posicion_papa += operacion;
      if (juego->posicion_papa < 1)
         juego->posicion_papa = participantes;

      if (juego->posicion_papa > participantes)
         juego->posicion_papa = 1;

   } while(!juego->estados[juego->posicion_papa - 1]);

   return juego->posicion_papa;
}

int main(int argc, char** argv) {
   RondaPapa juego;
   participantes = (argc > 1) ? atoi(argv[1]) : MAX_PARTICIPANTES;
   if (participantes <= 0 || participantes > MAX_PARTICIPANTES) participantes = MAX_PARTICIPANTES;

   juego.posicion_papa = (argc > 2) ? atoi(argv[2]) : 1;
   juego.clockwise = (argc > 3) ? atoi(argv[3]) : true;
   juego.valor_papa = rng(5, 10);
   juego.cuenta_jugadores = participantes;
   for (int i = 0; i < participantes; i++) juego.estados[i] = true;

   std::cout << "Iniciando ronda con " << participantes << " jugadores.\n";

   #pragma omp parallel num_threads(participantes) shared(juego)
   {
      int id = omp_get_thread_num() + 1;

      while (true) {
         mutex.Acquire();
         if (!juego.estados[id - 1]) {
            mutex.Release();
            break;
         }
         while (juego.posicion_papa != id && juego.cuenta_jugadores > 1) {
            cond.Wait(&mutex);
         }

         if (juego.cuenta_jugadores <= 1) {
            mutex.Release();
            break;
         }

         std::cout << BLUE << "Jugador (" << id << ") tiene la papa" << RESET << std::endl;
         valorPapa(&juego.valor_papa);

         if (juego.valor_papa == 1) {
            juego.estados[id - 1] = false;
            juego.cuenta_jugadores--;
            juego.valor_papa = rng(5, 10);
            std::cout << RED << "jugador (" << id << ") explotó y sale del juego." << RESET << std::endl;
         }

         juego.posicion_papa = pasarPapa(&juego);

         usleep(rng(60000, 80000));

         cond.NotifyAll();
         mutex.Release();

         if (juego.cuenta_jugadores <= 1) break;
      }
      mutex.Acquire();
      if (juego.cuenta_jugadores == 1 && juego.estados[id - 1]) 
      {
         std::cout << GREEN << "Jugador (" << id << ") gana el juego!" << RESET << std::endl;
      }
      mutex.Release();
   }

   return 0;
}