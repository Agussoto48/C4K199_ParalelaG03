#pragma once
#include "Lock.hpp"
#include "Condition.hpp"

#define FILOMAX 5

class Mesa {
   private:
     Mutex * mutex;
     void test( int );
     enum { THINKING, HUNGRY, EATING } state[ 5 ];
     Condition  * self[ 5 ];	// inanición (starvation)

   public:
      Mesa();
      ~Mesa();
      void pickup( int );
      void putdown( int );
      void print();
};