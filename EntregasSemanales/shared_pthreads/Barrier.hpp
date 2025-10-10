#ifndef _BARRIER_H
#define _BARRIER_H

#include <pthread.h>
#include<stdexcept>

class Barrier {
public:
   Barrier( int );
   ~Barrier();
   void Wait();

private:
   pthread_barrier_t  barrier;
   pthread_barrierattr_t * attr;
   unsigned int count;
};

#endif
