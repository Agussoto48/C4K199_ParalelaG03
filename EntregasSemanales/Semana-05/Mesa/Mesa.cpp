#include <stdio.h>
#include "Mesa.hpp"

/*
 *
**/
Mesa::Mesa() {
   int filo;

   this->lock = new Lock(); 
   for ( filo = 0; filo < FILOMAX; filo++ ) {
      this->state[ filo ] = THINKING;
      this->self[ filo ] = new Condition();
   }
}

Mesa::~Mesa() {
   int filo;

   delete this->lock;
   for ( filo = 0; filo < FILOMAX; filo++ ) {
      delete this->self[ filo ];
   }

}


int Mesa::pickup( int filosofo ) {

   this->lock->Acquire();
   this->state[ filosofo ] = HUNGRY;
   test( filosofo );
   if ( this->state[ filosofo ] != EATING ) {
      this->self[ filosofo ]->Wait( this->lock );
   }

   this->lock->Release();

}

int Mesa::putdown( int filosofo ) {

   this->lock->Acquire();

   this->state[ filosofo ] = THINKING;
   test( (filosofo + 4 ) % 5 );
   test( (filosofo + 1 ) % 5 );

   this->lock->Release();

}

int Mesa::test( int filosofo ) {

   if ( this->state[ (filosofo + 4) % 5 ] != EATING &&
        this->state[ (filosofo + 1) % 5 ] != EATING &&
        this->state[ filosofo ] == HUNGRY ) {
      this->state[ filosofo ] = EATING;
      this->self[ filosofo ]->Signal();
   }

}