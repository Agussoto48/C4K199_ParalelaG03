#include <stdio.h>
#include<iostream>
#include "Mesa_MP.hpp"

Mesa_MP::Mesa_MP() {
   int filo;
   for ( filo = 0; filo < FILOMAX; filo++ ) {
      this->state[ filo ] = THINKING;
   }
}

Mesa_MP::~Mesa_MP() {

}
void Mesa_MP::pickup( int filosofo ) {
   mutex.Acquire();
   {
      this->state[ filosofo ] = HUNGRY;
      test( filosofo );
      if ( this->state[ filosofo ] != EATING ) {
         this->self[ filosofo ].Wait(&this->mutex);
      }
   }
   mutex.Release();

}

//Termino de comer el filosofo actual
//Funcion punto critico
void Mesa_MP::putdown( int filosofo ) {

   mutex.Acquire();
   {

      this->state[ filosofo ] = THINKING;
      test( (filosofo + 4 ) % 5 );
      test( (filosofo + 1 ) % 5 );
   }
  mutex.Release();

}

//Funcion que comprueba que puede comer, solo si cumple las condiciones
void Mesa_MP::test( int filosofo ) {
   if (this->state[ (filosofo + 4) % 5 ] != EATING && this->state[ (filosofo + 1) % 5 ] != EATING && this->state[ filosofo ] == HUNGRY) 
    {
        this->state[ filosofo ] = EATING;
        this->self[ filosofo ].Signal();
    }
}

void Mesa_MP::print(){
   for (int i = 0; i < FILOMAX; i++) {
      std::cout << "F" << i+1 << ": ";
      switch (this->state[i])
      {
      case THINKING:
         std::cout << "\033[34mT\033[0m | ";
         break;
      case HUNGRY:
         std::cout << "\033[33mH\033[0m | ";
         break;
      case EATING:
         std::cout << "\033[31mE\033[0m | ";
         break;
      default:
         break;
      }
   }
   
   std::cout << "\n\n";
}