/**
  *  C++ program to send messages via operating system message passing queues
  *
  *  Author: Programacion Concurrente (Francisco Arroyo)
  *
  *  Version: 2025/Ago/26
  *
 **/


#define LABEL_SIZE 64
#include <stdio.h>
#include <string.h>
#include "../Buzon.hpp"

const char * html_labels[] = {
   "a",
   "b",
   "c",
   "d",
   "e",
   "li",
   ""
};

int main( int argc, char ** argv ) {


   int id, i, size, st;
   Buzon m;

   i = 0;

   while ( strlen(html_labels[ i ] ) ) {
      size = sizeof(html_labels[ i ]);
      m.Enviar( html_labels[ i ], 2025);  // Send a message with 2019 type, (label,n)
      printf("Label: %s, status %d \n", html_labels[ i ], st );
      i++;
   }

}