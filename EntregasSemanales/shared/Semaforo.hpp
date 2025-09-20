/*
 *  C++ class to encapsulate Unix semaphore intrinsic structures and system calls
 *  Author: Programacion Concurrente (Francisco Arroyo)
 *  Version: 2025/Ago/18
 *
 * Ref.: https://en.wikipedia.org/wiki/Semaphore_(programming)
 *
 */
#pragma once
#include <stdexcept>            // runtime_error
#include<sys/sem.h>
#include<iostream>
union semun{
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                 (Linux-specific) */
};

class Semaforo {
private:
    int id;		// Identificador del semaforo
public:
    union semun h;
     sembuf s;
    Semaforo();
    Semaforo( int = 0 );
    ~Semaforo();
    int Signal();	// Puede llamarse V
    int Wait();	// Puede llamarse P

};