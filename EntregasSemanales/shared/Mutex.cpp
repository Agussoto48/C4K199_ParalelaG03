#include "Mutex.hpp"

/*
 *  Creates a mutex, using a semaphore
 */
Mutex::Mutex() {

   this->mutex = new SemaforoArray( 1, 1 );

}


/**
 * Destroys the lock
 */
Mutex::~Mutex() {

   delete this->mutex;

}


/**
 * Acquires the lock
 *
 */
void Mutex::Lock() {

   this->mutex->Wait();

} 

  
/**
 * Release the lock
 *
 */
void Mutex::Unlock() {

   this->mutex->Signal();

}

