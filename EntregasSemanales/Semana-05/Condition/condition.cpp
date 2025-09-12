#include "condition.hpp"

/*
 *  Creates a new condition variable
 *
 *  Uses an internal structure to make workers wait for resources
 *
**/
Condition::Condition() {

   this->workers = 0;
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

   this->workers++;

   // To be completed by students

} 

  
/**
 *  Notify one worker from the queue, if empty has no effect
 *
**/
void Condition::NotifyOne() {

   if ( this->workers > 0 ) {
      this->workers--;	// One
   // To be completed by students

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
 *  Signal all workers from the queue, if empty has no effect
 *
**/
void Condition::NotifyAll() {

   while ( this->workers > 0 ) {
      this->workers--;
   // To be completed by students
   }

}