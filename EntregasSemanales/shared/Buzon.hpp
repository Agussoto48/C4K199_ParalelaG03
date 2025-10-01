#pragma once
/**
  *  C++ class to encapsulate Unix message passing intrinsic structures and system calls
  *
  *  Author: Programacion Concurrente (Francisco Arroyo)
  *  Version: 2025/Ago/26
  *
 **/

#include <unistd.h>	// pid_t definition
#include<sys/msg.h>
#include<stdexcept>
#include<cstring>

#define KEY 0xA12345	// Valor de la llave del recurso
class Buzon {
private:
    int id;		// Identificador del buzon
    pid_t owner;	// Dueño del recurso
    bool creador;
public:
    Buzon(bool crear = true) {
        if(crear){
            id = msgget(KEY, 0600 | IPC_CREAT);
            creador = true;
        }
        else{
            id = msgget(KEY, 0600);
            creador = false;
        }
        if(id == -1){
            if(errno == ENOENT){
                perror("No se ha creado un buzón aún, nada que recibir: ");
            } else {
                throw std::runtime_error("Error al crear el buzon");
            }
        }
        owner = getpid();
    }
    ~Buzon() {
        //El que recibe el mensaje se encarga de cerrar el buzon, ya que si se cierra antes de recibirlo no llega nada
        if(!creador){
            msgctl(id, IPC_RMID, NULL);
        }
    }
    ssize_t Enviar( const void *buffer, size_t size, long type = 1){ // Send a message (len sized) pointed by buffer to mailbox
        return msgsnd(this->id, buffer, size, 0);
    }
    ssize_t Recibir(void *buffer, size_t size, long type = 1){ // size_t: space in buffer
        return msgrcv(id, buffer, size, type, 0);
    }
};
