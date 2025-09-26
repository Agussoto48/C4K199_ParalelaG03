#include "Lock.hpp"

/*
 *  Creates a lock, using a mutex
 */
Lock::Lock() {
    mutex = new Mutex();
}


/**
 * Destroys the lock
 */
Lock::~Lock() {
    mutex->~Mutex();
    delete mutex;
}


/**
 * Acquires the lock
 *
 */
void Lock::Acquire() {
    mutex->Lock();

} 

  
/**
 * Release the lock
 *
 */
void Lock::Release() {
    mutex->Unlock();

}