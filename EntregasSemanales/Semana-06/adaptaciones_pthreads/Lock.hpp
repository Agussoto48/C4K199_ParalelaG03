#ifndef _LOCK_H
#define _LOCK_H
#include "Mutex.hpp"

class Lock {
   public:
      Lock();
      ~Lock();
      void Acquire();
      void Release();

   private:
      Mutex * mutex;

};

#endif

