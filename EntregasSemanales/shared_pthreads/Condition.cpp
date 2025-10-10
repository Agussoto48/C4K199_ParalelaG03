
#include "Condition.hpp"

/*
 * pthread_cond_init
 */
Condition::Condition() {
   pthread_cond_init(&vc, NULL);
}


/*
 * pthread_cond_destroy
 */
Condition::~Condition() {
   pthread_cond_destroy(&vc);
}


/*
 * pthread_cond_wait
 */
int Condition::Wait( Mutex * mutex ) {
   return pthread_cond_wait(&vc, mutex->getMutex());
}


/*
 * pthread_cond_timedwait
 */
int Condition::TimedWait( Mutex * mutex, const struct timespec *abstime) {
   return pthread_cond_timedwait(&vc, mutex->getMutex(), abstime);

}


/*
 * pthread_cond_signal
 */
int Condition::Signal() {
   return pthread_cond_signal(&vc);
   
}


/*
 * pthread_cond_broadcast
 */
int Condition::Broadcast() {
   return pthread_cond_broadcast(&vc);   
}

