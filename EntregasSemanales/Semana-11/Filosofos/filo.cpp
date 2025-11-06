#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <omp.h>
#include <random>
#include "Mesa_MP.hpp"

int rng(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

Mesa_MP mesa;
void Filosofo(int id_ingreso) {
   int id = id_ingreso;

   for (int i = 0; i < 10; i++) {
        usleep(rng(40000, 120000));
        mesa.pickup(id);
        mesa.print();
        
        usleep(rng(60000, 160000));
        mesa.putdown(id);
        
        mesa.print();
        usleep(rng(40000, 120000));
    }

}
int main( int argc, char ** argv ) {
    long workers;

    workers = 5;
    if ( argc > 1 ) {
        workers = atol( argv[ 1 ] );
    }
    std::cout << "Simulación de " << workers << " filósofos comensales" << std::endl;

    #pragma omp parallel num_threads(workers)
    {
        int id = omp_get_thread_num();
        Filosofo(id);
    }

    std::cout << "\nNormal end of execution.\n";
    return 0;
}