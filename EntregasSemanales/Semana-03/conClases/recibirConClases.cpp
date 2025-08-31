/**
  *  C++ program to receive messages via operating system message passing queues
  *
  *  Author: Programacion Concurrente (Francisco Arroyo)
  *
  *  Version: 2025/Ago/26
  *
 **/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<iostream>
#include "../Buzon.hpp"

#define LABEL_SIZE 64


int main( int argc, char ** argv ) {


struct msgbuf {
   long mtype;     // message type, must be > 0 
   int times;	// Times that label appears
   char label[ LABEL_SIZE ];  // Label to send to mailbox
};
   struct msgbuf A;
   int st;
   Buzon m(false);

   st = m.Recibir((void *) &A, sizeof(A), 2025); 
   while ( st > 0 ) {
      printf("Label: %s, times %d \n", A.label, A.times);
      st = m.Recibir( (void *)  &A, sizeof(A) ,2025 );
   }
}
