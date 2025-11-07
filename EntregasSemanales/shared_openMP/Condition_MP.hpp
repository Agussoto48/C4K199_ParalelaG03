#include <omp.h>
#include "LockMP.hpp"

class Condition_MP {
private:
    int workers;
    LockMP internalWaitMechanism;
public:
    Condition_MP();
    ~Condition_MP();
    void Wait( LockMP * );
    void NotifyOne();
    void NotifyAll();
    void Signal();
};