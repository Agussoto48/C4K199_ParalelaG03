#pragma once
#include "LockMP.hpp"
#include "Condition_MP.hpp"

#define FILOMAX 5

class Mesa_MP {
   private:
      LockMP mutex;
      void test( int );
      enum { THINKING, HUNGRY, EATING } state[ 5 ];
      Condition_MP self[ 5 ];

   public:
      Mesa_MP();
      ~Mesa_MP();
      void pickup( int );
      void putdown( int );
      void print();
};