

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

struct msg {
   long mtype;
   int times;
   char mtext[64];
};
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


   int i;
   ssize_t st;
   struct msg A;
   Buzon m(true);
   A.mtype = 2025;
   i = 0;

   while ( strlen(html_labels[ i ] ) ) {
      strcpy(A.mtext, html_labels[ i ]);
      A.times = i;
      st = m.Enviar((void *) &A, sizeof(A), 2025);  // Send a message with 2025 type, (label,n)
      printf("Label: %s, status %ld \n", html_labels[ i ], st );
      i++;
   }

}
