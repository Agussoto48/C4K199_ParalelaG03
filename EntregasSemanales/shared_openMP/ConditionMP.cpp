#include "Condition_MP.hpp"

Condition_MP::Condition_MP() {
   this->workers = 0;
}

Condition_MP::~Condition_MP() {
}

void Condition_MP::Wait(LockMP * externalLock){
    internalWaitMechanism.Acquire();
    workers++;
    internalWaitMechanism.Release();

    
    externalLock->Release();
    internalWaitMechanism.Acquire();
    internalWaitMechanism.Release();
    externalLock->Acquire();
}

void Condition_MP::NotifyOne() {
    internalWaitMechanism.Acquire();
    if (workers > 0) {
        workers--;
    }
    internalWaitMechanism.Release();
}

void Condition_MP::Signal() {
   NotifyOne();
}

void Condition_MP::NotifyAll() {
    internalWaitMechanism.Acquire();
    while (workers > 0) {
        workers--;
        internalWaitMechanism.Release();
        internalWaitMechanism.Acquire();
    }
    internalWaitMechanism.Release();
}
