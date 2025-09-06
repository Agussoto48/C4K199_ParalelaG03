/**
 *  C++ class to encapsulate Unix semaphore intrinsic structures and system calls
 *  Author: Programacion Concurrente (Francisco Arroyo)
 *  Version: 2025/Ago/18
 *
 * Ref.: https://en.wikipedia.org/wiki/Semaphore_(programming)
 *
 **/



#include "Semaforo.hpp"

 

#define KEY 0xA12345

Semaforo::Semaforo(){
   throw std::runtime_error( "Semaforo::Semaforo( int )" );
}
Semaforo::Semaforo( int valorInicial ) {
    // Use semget to create a System V semaphore set identifier
    this->id = semget(KEY, 1, IPC_CREAT|0600);
    // Use semctl to state a initial value to semaphore set
   h.val = valorInicial;
   semctl(this->id, 0, SETVAL, h);

}



Semaforo::~Semaforo() {
   // Use semctl to destroy a semaphore set identifier
   semctl(this->id, 0, IPC_RMID);
}


int Semaforo::Signal() {
   s.sem_num = 0;
   s.sem_op = +1;
   s.sem_flg = 0;
   
   int resultado = semop(this->id, &s, 1);
   if ( -1 == resultado ) {
      //throw std::runtime_error( "Semaforo::Signal()" );
   }

   return resultado;

}


int Semaforo::Wait() {
   s.sem_num = 0;
   s.sem_op = -1;
   s.sem_flg = 0;

   int resultado = semop(this->id, &s, 1);
   if ( -1 == resultado ) {
      //throw std::runtime_error( "Semaforo::Wait()" );
   }

   return resultado;

}