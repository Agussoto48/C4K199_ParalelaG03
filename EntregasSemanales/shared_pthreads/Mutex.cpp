#include <stdlib.h>
#include <pthread.h>
#include "Mutex.hpp"

/**
 *
 *  pthread_mutex_init()
 *
**/
Mutex::Mutex() {
   pthread_mutex_init(&mutex, nullptr);

}


/**
 *
 * pthread_mutex_destroy()
 *
**/
Mutex::~Mutex() {
   pthread_mutex_destroy(&mutex);
}


/**
 *
 * pthread_mutex_lock()
 *
**/
int Mutex::Lock() {
   int resultado = pthread_mutex_lock(&mutex);

   return resultado;

}


/**
 *  pthread_mutex_trylock()
**/
int Mutex::TryLock() {
   return pthread_mutex_trylock(&mutex);

}

/**
 *  pthread_mutex_unlock()
**/
int Mutex::Unlock() {
   int resultado = pthread_mutex_unlock(&mutex);

   return resultado;

}


/**
 * 
**/
pthread_mutex_t * Mutex::getMutex() {

   return &this->mutex;

}
