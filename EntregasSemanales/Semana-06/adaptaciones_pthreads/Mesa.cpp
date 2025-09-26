#include <stdio.h>
#include<iostream>
#include "Mesa.hpp"

Mesa::Mesa() {
   int filo;
   this->mutex = new Mutex(); 
   for ( filo = 0; filo < FILOMAX; filo++ ) {
      this->state[ filo ] = THINKING;
      this->self[ filo ] = new Condition();
   }
}

Mesa::~Mesa() {
   int filo;

   delete this->mutex;
   for ( filo = 0; filo < FILOMAX; filo++ ) {
      delete this->self[ filo ];
   }

}

//Empieza a comer el filosofo actual
//Funcion punto critico
void Mesa::pickup( int filosofo ) {
   this->mutex->Lock();
   {
      //Se pone hambriento
      this->state[ filosofo ] = HUNGRY;
      //Comprobamos que sí pueda empezar a comer
      test( filosofo );
      //Si no puede empezar a comer entonces esperamos
      if ( this->state[ filosofo ] != EATING ) {
         //Hacemos lock en la mesa
         this->self[ filosofo ]->Wait(this->mutex );
      }
   }
   this->mutex->Unlock();

}

//Termino de comer el filosofo actual
//Funcion punto critico
void Mesa::putdown( int filosofo ) {

   this->mutex->Lock();
   {

      this->state[ filosofo ] = THINKING;
      test( (filosofo + 4 ) % 5 );
      test( (filosofo + 1 ) % 5 );
   }
  this->mutex->Unlock();

}

//Funcion que comprueba que puede comer, solo si cumple las condiciones
void Mesa::test( int filosofo ) {
   if (  //Filosofo de la derecha no esta comiendo
        this->state[ (filosofo + 4) % 5 ] != EATING &&
        //Filosofo de la izquierda no esta comiendo
        this->state[ (filosofo + 1) % 5 ] != EATING &&
        //Filosofo esta hambriento
        this->state[ filosofo ] == HUNGRY ) 
      {
         this->state[ filosofo ] = EATING;
         this->self[ filosofo ]->Signal();
      }
}

void Mesa::print(){
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