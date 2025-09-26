#ifndef _SEM_H
#define _SEM_H

#include <semaphore.h>

class Semaforo {
public:
   Semaforo( int = 1 );
   ~Semaforo();
   int Signal();
   int Wait();
   int tryWait();
   int timedWait( long = 0, long = 0 );

private:
   sem_t semId;

};

#endif