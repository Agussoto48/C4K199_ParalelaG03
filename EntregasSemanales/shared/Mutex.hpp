#pragma once
#include "SemaforoArray.hpp"

class Mutex {
   public:
      Mutex();
      ~Mutex();
      void Lock();
      void Unlock();

   private:
      SemaforoArray * mutex;

};
