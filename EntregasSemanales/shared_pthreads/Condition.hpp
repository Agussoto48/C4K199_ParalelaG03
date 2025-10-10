
#ifndef _COND_H
#define _COND_H

#include <pthread.h>
#include "Lock.hpp"

class Condition {

   public:
      Condition();
      ~Condition();
      int Wait( Mutex * );
      int TimedWait( Mutex * , const struct timespec *abstime);
      int Signal();
      int Broadcast();

   private:
      pthread_cond_t vc;

};

#endif