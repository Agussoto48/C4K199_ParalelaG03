#include "conditionS.hpp"

/*
 *  Creates a new condition variable
 *
 *  Uses an internal structure to make hilos wait for resources
 *
**/
Condition::Condition() {
   this->hilos = 0;
   this->internalWaitMechanism = new Lock();	// Could be any other mechanism

}


/**
 * Destroys our condition variable
**/
Condition::~Condition() {

   delete this->internalWaitMechanism;

}


/**
 *  Wait for the condition controlled by our variable
 *
**/
void Condition::Wait( Lock * affectedLock ) {

   this->hilos++;
   affectedLock->Release();
   this->internalWaitMechanism->Acquire();
   this->internalWaitMechanism->Release();
   affectedLock->Acquire();

} 

  
/**
 *  Notify one worker from the queue, if empty has no effect
 *
**/
void Condition::NotifyOne() {
   if ( this->hilos > 0 ) {
      this->hilos--;	// One
      this->internalWaitMechanism->Release();
   }
}


/**
 *  Same method as notify one, declared for compatibility with many examples
 *
**/
void Condition::Signal() {
   this->NotifyOne();
}

/**
 *  Signal all hilos from the queue, if empty has no effect
 *
**/
void Condition::NotifyAll() {
   while ( this->hilos > 0 ) {
      this->hilos--;
      this->internalWaitMechanism->Release();
   }

}