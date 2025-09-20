#include "Lock.hpp"

/*
 *  Creates a lock, using a semaphore
 */
Lock::Lock() {

   this->semaforo = new SemaforoArray(1, 1);

}


/**
 * Destroys the lock
 */
Lock::~Lock() {

   delete this->semaforo;

}

/**
 * Acquires the lock
 *
 */
void Lock::Acquire() {

   this->semaforo->Wait();

} 

  
/**
 * Release the lock
 *
 */
void Lock::Release() {

   this->semaforo->Signal();

}