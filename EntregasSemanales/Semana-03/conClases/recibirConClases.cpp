

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

#include "../Buzon.hpp"

#define LABEL_SIZE 64

int main( int argc, char ** argv ) {

   mensaje msg;
   Buzon m;

   int st = m.Recibir(msg, 2025);  // Receives a message with 2019 type
   while ( st > 0 ) {
      printf("Label: %s, times %d \n", msg.label, msg.times );
      st = m.Recibir(msg, 2025);
   }

}
