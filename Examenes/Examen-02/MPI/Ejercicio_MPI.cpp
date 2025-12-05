#include <stdio.h>
#include <string>
#include <mpi.h>
#include <iostream>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    double inicio, fin;

    inicio = MPI_Wtime();
    // Codigo a hacer
    fin = MPI_Wtime();

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    {
        std::cout << "\nEl resultado de las cadenas fue:\n";

        std::cout << "Tiempo: " << (fin - inicio) << " segundos\n";
    }

    MPI_Finalize();
    return 0;
}