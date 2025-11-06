#pragma once
#include "LockMP.hpp"
#include<omp.h>

class SemaphoreMP{
private:
    LockMP mutex;
    LockMP sem;		
    int owner;		
    int value;		
public:
    //Constructor y destructor
    SemaphoreMP(int valorInical = -1);
    //Lógica del semaforo
    ~SemaphoreMP();
    void Signal();
    void Wait();

};