#pragma once
#include <omp.h>

class LockMP {
private:
    omp_lock_t lock; 

public:
    //Constructor y destructor
    LockMP();
    ~LockMP();

    //Lógica del candado
    void Acquire();
    void Release();
};
