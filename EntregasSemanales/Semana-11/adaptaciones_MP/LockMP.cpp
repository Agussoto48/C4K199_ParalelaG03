#include "LockMP.hpp"

//Constructor y destructor
LockMP::LockMP() {
    omp_init_lock(&lock);
}
LockMP::~LockMP() {
    omp_destroy_lock(&lock);
}

//Lógica del candado
void LockMP::Acquire() {
    omp_set_lock(&lock);
}
void LockMP::Release() {
    omp_unset_lock(&lock);
}