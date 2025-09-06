#include<iostream>
#include<sys/shm.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<random>
#include "Buzon.hpp"

//El rango cercano de moleculas que se pueden crear si no se pasa argumentos
#define LIMITE 5

struct molecula{
    long mtype = 2025;
    int hid = 0;
    int ox = 0;
    int numMol = 0;
    int i = 0;
};

//Declaracion de funciones
void Hidrogeno(int i);
void Oxigeno(int i);
int rng();


Buzon sender(true);
Buzon receiver(false);



int main(int argc, char** argv){
    int i = 0;
    int maxMol = LIMITE;
    ////El rango cercano de moleculas que se pueden crear si se pasan argumentos
    if ( argc > 1 ) {
      maxMol = atol( argv[ 1 ] );
    }
    struct molecula agua;
    struct molecula msg;
    while(agua.numMol < maxMol){

        i++;
        int r = rng();
        if(!fork()){
            if(r == 0){
                std::cout << "Se creó un atomo de oxígeno [" << i << "]\n";  
                Oxigeno(i);
            }
            else {
                std::cout << "Se creó un atomo de Hidrogeno [" << i << "]\n";  
                Hidrogeno(i);
            }
        } 
        receiver.Recibir(&msg, sizeof(molecula), 2025);
        agua.hid += msg.hid;
        agua.ox += msg.ox;
        if(agua.hid > 1 && agua.ox > 0){
            agua.numMol++;
            agua.hid -= 2;
            agua.ox--;
            if(msg.hid == 1){
                std::cout << "Molecula de\033[36m agua \033[0mcreada por\033[33m hidrogeno \033[0m[" << msg.i << "]\n";
            }
            else {
                std::cout << "Molecula de\033[36m agua \033[0mcreada por\033[35m oxigeno \033[0m[" << msg.i << "]\n";
            }
        }
    }
    
    return 0;
}


//Definicion de funciones
void Oxigeno(int i){
    struct molecula oxigeno;
    oxigeno.ox = 1;
    oxigeno.i = i;
    sender.Enviar(&oxigeno, sizeof(molecula), 2025);
    _exit(0);
}
void Hidrogeno(int i){
    struct molecula hidrogeno;
    hidrogeno.hid = 1;
    hidrogeno.i = i;
    sender.Enviar(&hidrogeno, sizeof(molecula), 2025);
    _exit(0);
}

//Devuelve o un 1 o un 0
int rng(){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0,1);
    return distribution(generator);
}