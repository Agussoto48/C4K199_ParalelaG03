/**
  *  C++ class to encapsulate Unix message passing intrinsic structures and system calls
  *
  *  Author: Programacion Concurrente (Francisco Arroyo)
  *  Version: 2025/Ago/26
  *
 **/

#include <unistd.h>	// pid_t definition
#include <sys/msg.h>
#include<iostream>

#define KEY 0xA12345	// Valor de la llave del recurso
#define LABEL_SIZE 64

//Datos neccesarios para el mensaje

struct mensaje{
   long mtype;     // message type, must be > 0 
   int times;	// Times that label appears
   char label[ LABEL_SIZE ];  // Label to send to mailbox
};

class Buzon {    
private:
    int id;		// Identificador del buzon

public:
    Buzon() {
        // Use semget to create a System V semaphore set identifier
        this->id = msgget(KEY, IPC_CREAT|0600);
    }
    ~Buzon() {
        std::cout << "Destructor | " <<  msgctl( id, IPC_RMID, NULL );
    }
    ssize_t Enviar(const char * texto, long  etiqueta) {
        mensaje msg;
        msg.mtype = etiqueta;
        strcpy(msg.label, texto);
        msg.times = strlen(texto);

        ssize_t st = msgsnd(this -> id, &msg, sizeof(msg), IPC_NOWAIT);

        if(st == -1) {
            perror("msgsend");
        }
        return st;

    }
    ssize_t Recibir(mensaje &msg, long etiqueta = 1 ){ // size_t: space in buffer
        ssize_t st = msgrcv(this->id, &msg, sizeof(msg), etiqueta, IPC_NOWAIT);
        if(st == -1){
            perror("msgrcv");
        }
        return msgrcv(this->id, &msg, sizeof(msg), etiqueta, IPC_NOWAIT);
    }	

};