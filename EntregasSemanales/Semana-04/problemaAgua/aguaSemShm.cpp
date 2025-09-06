#include<iostream>
#include<sys/shm.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<random>
#include "Semaforo.hpp"

#define KEY 123456
//El rango cercano de moleculas que se pueden crear si no se pasa argumentos
#define LIMITE 5

struct molecula{
    int hid = 0;
    int ox = 0;
    int numMol = 0;
};

//Declaracion de funciones
void Hidrogeno(int i);
void Oxigeno(int i);
int rng();

Semaforo sO(0);
Semaforo sH(0);

int id = 0;
struct molecula* agua;

int main(int argc, char** argv){
    int i = 0;
    int maxMol = LIMITE;
    ////El rango cercano de moleculas que se pueden crear si se pasan argumentos
    if ( argc > 1 ) {
      maxMol = atol( argv[ 1 ] );
    }
    
    id = shmget(KEY, sizeof(molecula), 0600 | IPC_CREAT);
    agua = (molecula *) shmat(id, NULL, 0);

    while(agua->numMol < maxMol){
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
    }
    
    //Limpia la memoria compartida
    shmdt(agua);
    shmctl(id, IPC_RMID, NULL);

    return 0;
}


//Definicion de funciones
void Oxigeno(int i){
    if(agua->hid > 1){
        std::cout << "Molecula de agua creada por oxigeno [" << i << "]\n";
        sH.Signal();
        sH.Signal();
        agua->hid -= 2;
        agua->numMol++;
    }
    else {
        agua -> ox++;
        sO.Wait();
    }
    _exit(0);
}
void Hidrogeno(int i){
    if((agua -> hid > 0) && (agua->ox > 0)){
        std::cout << "Molecula de agua creada por hidrogeno [" << i << "]\n";
        agua->ox--;
        agua->hid--;
        agua->numMol++;
        sH.Signal();
        sO.Signal();
    }
    else {
        agua->hid++;
        sH.Wait();
    }
    _exit(0);
}


int rng(){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0,1);
    return distribution(generator);
}