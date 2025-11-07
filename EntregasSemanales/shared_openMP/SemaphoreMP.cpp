#include "SemaphoreMP.hpp"

//Constructor y destructor
SemaphoreMP::SemaphoreMP(int valorInical)
    :value(valorInical)
    {}
SemaphoreMP::~SemaphoreMP(){
}
void SemaphoreMP::Signal(){
   this->mutex.Acquire();
   this->value++;
   this->mutex.Release();
   this->sem.Release();
}
void SemaphoreMP::Wait(){
   while (true) {
      this->mutex.Acquire();
      if ( this->value > 0 ) 
      {
        this->value--;
        this->mutex.Release();
        break;
      } else 
      {
        this->mutex.Release();
        this->sem.Acquire();
      }
   }
}
