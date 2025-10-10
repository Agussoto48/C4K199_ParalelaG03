#include "Barrier.hpp"


/*
 *  pthread_barrier_init
 */
Barrier::Barrier( int limit ) {
    int res = pthread_barrier_init(&barrier, NULL, limit);
    if(res != 0){
        throw std::runtime_error("Error inicializando la barrera");
    }
}


/*
 * pthread_barrier_destroy
 */
Barrier::~Barrier() {
    pthread_barrier_destroy(&barrier);
}


/*
 * pthread_barrier_wait
 */
void Barrier::Wait() {
    pthread_barrier_wait(&barrier);
}