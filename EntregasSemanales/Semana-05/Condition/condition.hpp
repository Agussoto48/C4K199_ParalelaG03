
#include "Lock.hpp"

class Condition {

   public:
      Condition();
      ~Condition();
      void Wait( Lock * );
      void NotifyOne();
      void NotifyAll();
      void Signal();

   private:
     int workers;
     Lock * internalWaitMechanism;

};