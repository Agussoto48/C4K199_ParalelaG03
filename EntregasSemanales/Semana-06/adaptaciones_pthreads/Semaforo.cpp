#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "Semaforo.hpp"

/*
 *  sem_init
 */
Semaforo::Semaforo( int inicial ) {
   sem_init(&semId, 0, inicial);
}


/*
 *  sem_destroy
 */
Semaforo::~Semaforo() {
   sem_destroy(&semId);
}


/*
 *  sem_post
 */
int Semaforo::Signal() {

   return sem_post(&semId);

}


/*
 *  sem_wait
 */
int Semaforo::Wait() {
   return sem_wait(&semId);

}


/*
 *  sem_trywait
 */
int Semaforo::tryWait() {
   return sem_trywait(&semId);

}


/*
 *  sem_timedwait
 */
int Semaforo::timedWait( long sec, long nsec ) {
   struct timespec lapso;

   lapso.tv_nsec = nsec;
   lapso.tv_sec = sec;
   if (lapso.tv_nsec >= 1000000000) { // normalizar nanosegundos
        lapso.tv_sec++;
        lapso.tv_nsec -= 1000000000;
    }

   return sem_timedwait(&semId, &lapso);

}