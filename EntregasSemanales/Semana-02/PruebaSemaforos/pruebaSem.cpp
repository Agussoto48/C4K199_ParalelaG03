#include <stdio.h>
#include <unistd.h>
#include "Semaforo.hpp"


/*
 * 
 */
void primero() {
   printf( "Voy primero\n" );
}


/*
 * 
 */
void segundo() {
   printf( "Voy segundo\n" );
}


/*
 *  Este método explícitamente llama a los métodos "Primero" y "Segundo" para que la salida
 *  se despliegue en orden
 */
void pruebaSerial() {

   primero();
   segundo();

}

int main() {
    Semaforo s(0);	// El semáforo debe estar inicializado en cero

    pruebaSerial();
    if (!fork() ) {
       primero();
       // Para tener el mismo orden que la versión serial, aqui debemos esperar por el semáforo (wait)
       s.Signal();
      //s.Wait();
    }
    else {
      s.Wait();
       segundo();
       // Aqui debemos indicar que esta primera parte ya finalizó (signal)
       //s.Signal();
    }
    s.~Semaforo();

}
/*
   Salida esperada:
     Voy primero
     Voy segundo
     Voy primero
     Voy segundo
*/