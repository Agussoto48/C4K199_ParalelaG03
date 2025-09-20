#ifndef _LOCK_H
#define _LOCK_H
#include "SemaforoArray.hpp"
//#include "Semaforo.hpp"

class Lock {
   public:
      Lock();
      ~Lock();
      void Acquire();
      void Release();

   private:
      SemaforoArray * semaforo;

};

#endif