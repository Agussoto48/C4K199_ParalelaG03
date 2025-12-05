#include <cstdio>
#include <random>
#include <omp.h>
#include <iostream>
#include <exception>
#include <cstring>

int main(int cantidad, char **parametros)
{

    int hilos = 1;

    omp_set_num_threads(hilos);
    double inicio = omp_get_wtime();

    // Codigoa a hacer

    double final = omp_get_wtime();

    
    double total = final - inicio;

    std::cout << "\nTiempo final: " << total << std::endl;
    return 0;
}
