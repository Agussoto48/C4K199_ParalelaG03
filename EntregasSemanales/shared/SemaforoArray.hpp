#pragma once
#include <stdexcept>            // runtime_error
#include<sys/sem.h>
#include<iostream>
#define KEY 0xA12345

union semun{
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                 (Linux-specific) */
};
class SemaforoArray {
private:
    int id;		// Identificador del semaforo
public:
    union semun h;
    sembuf s;
    SemaforoArray(){
        throw std::runtime_error( "Semaforo::Semaforo( int , int)" );
    }
    SemaforoArray(int cantidad, int valorInicial){
        this->id = semget(KEY, cantidad, IPC_CREAT|0600);
        h.val = valorInicial;
        semctl(this->id, 0, SETVAL, h);

    }
    ~SemaforoArray() {
        semctl(this->id, 0, IPC_RMID);
    }
    int Signal(int numSem = 0){
        s.sem_num = numSem;
        s.sem_op = +1;
        s.sem_flg = 0;

        int resultado = semop(this->id, &s, 1);
        if ( -1 == resultado ) {
        //throw std::runtime_error( "Semaforo::Signal()" );
        }

        return resultado;

    }
    int Wait(int numSem = 0){
        s.sem_num = numSem;
        s.sem_op = -1;
        s.sem_flg = 0;

        int resultado = semop(this->id, &s, 1);
        if ( -1 == resultado ) {
            //throw std::runtime_error( "Semaforo::Wait()" );
        }
        return resultado;

    }
    void SP(int first, int second){
        sembuf semaforos[2];
        //Primer semaforo
        semaforos[0].sem_num = first;
        semaforos[0].sem_op = -1;
        semaforos[0].sem_flg = 0;
        //Segundo Semaforo
        semaforos[1].sem_num = second;
        semaforos[1].sem_op = -1;
        semaforos[1].sem_flg = 0;

        if (semop(this->id, semaforos, 2)  == -1) {
            throw std::runtime_error( "Semaforo::SP()" );
        }


    }
    void SV(int first, int second){
        sembuf semaforos[2];
        //Primer semaforo
        semaforos[0].sem_num = first;
        semaforos[0].sem_op = +1;
        semaforos[0].sem_flg = 0;
        //Segundo Semaforo
        semaforos[1].sem_num = second;
        semaforos[1].sem_op = +1;
        semaforos[1].sem_flg = 0;

        if (semop(this->id, semaforos, 2)  == -1) {
            throw std::runtime_error( "Semaforo::SV()" );
        }
    }

};