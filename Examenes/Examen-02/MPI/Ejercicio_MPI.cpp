#include <stdio.h>
#include <string>
#include <mpi.h>
#include <iostream>

void fibonacci_desde_0(int tripleta[3], int n, int rank, int size, bool sentido)
{
    if (rank == 0)
    {
        tripleta[0] = 0;
        tripleta[1] = 1;
        tripleta[2] = n - 2;

        std::cout << "Rank " << rank << " inicia con {" << tripleta[0] << ", " << tripleta[1] << ", " << tripleta[2] << "}\n";
        int next = sentido ? (rank + 1) % size : (rank - 1 + size) % size;
        MPI_Send(tripleta, 3, MPI_INT, next, 0, MPI_COMM_WORLD);
    }
    bool terminado = false;
    while (!terminado)
    {
        // Recibe desde el rank anterior
        int source = sentido ? (rank - 1 + size) % size : (rank + 1) % size;
        MPI_Recv(tripleta, 3, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (tripleta[2] == -1)
        {
            int next = sentido ? (rank + 1) % size : (rank - 1 + size) % size;
            MPI_Send(tripleta, 3, MPI_INT, next, 0, MPI_COMM_WORLD);
            terminado = true;
            continue;
        }

        int a = tripleta[0];
        int b = tripleta[1];
        int pasos = tripleta[2];
        if (pasos == 0)
        {
            std::cout << "\n============================================"
            <<"\nRank " << rank << " tiene el resultado final: " << a + b
            << "\n============================================\n";

            int kill_msg[3] = {-1, -1, -1};
            int next = sentido ? (rank + 1) % size : (rank - 1 + size) % size;
            MPI_Send(kill_msg, 3, MPI_INT, next, 0, MPI_COMM_WORLD);
            terminado = true;
            continue;
        }

        int c = a + b;
        int next_tripleta[3] = {b, c, pasos - 1};
        int orden_de_impresion = n - pasos - 1;
        std::cout << orden_de_impresion << ") " << "Rank " << rank << " recibe {" << a << ", " << b << ", " << pasos << "} y envía {"
                  << next_tripleta[0] << ", " << next_tripleta[1] << ", " << next_tripleta[2] << "}\n";

        // Enviar al siguiente
        int next = sentido ? (rank + 1) % size : (rank - 1 + size) % size;
        MPI_Send(next_tripleta, 3, MPI_INT, next, 0, MPI_COMM_WORLD);
    }
}
void fibonacci_para_0(int tripleta[3], int n, int rank, int size, bool sentido, int rank_inicial)
{
    if (rank == rank_inicial)
    {
        tripleta[0] = 0;
        tripleta[1] = 1;
        tripleta[2] = n - 2;

        std::cout << "Rank " << rank << " inicia con {" << tripleta[0] << ", " << tripleta[1] << ", " << tripleta[2] << "}\n";
        int next = sentido ? (rank + 1) % size : (rank - 1 + size) % size;
        MPI_Send(tripleta, 3, MPI_INT, next, 0, MPI_COMM_WORLD);
    }
    bool terminado = false;
    while (!terminado)
    {
        // Recibe desde el rank anterior
        int source = sentido ? (rank - 1 + size) % size : (rank + 1) % size;
        MPI_Recv(tripleta, 3, MPI_INT, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (tripleta[2] == -1)
        {
            int next = sentido ? (rank + 1) % size : (rank - 1 + size) % size;
            MPI_Send(tripleta, 3, MPI_INT, next, 0, MPI_COMM_WORLD);
            terminado = true;
            continue;
        }

        int a = tripleta[0];
        int b = tripleta[1];
        int pasos = tripleta[2];
        if (pasos == 0)
        {
            
            std::cout << "\n============================================"
            <<"\nRank " << rank << " tiene el resultado final: " << a + b
            << "\n============================================\n";

            int kill_msg[3] = {-1, -1, -1};
            int next = sentido ? (rank + 1) % size : (rank - 1 + size) % size;
            MPI_Send(kill_msg, 3, MPI_INT, next, 0, MPI_COMM_WORLD);
            terminado = true;
            continue;
        }

        int c = a + b;
        int next_tripleta[3] = {b, c, pasos - 1};
        int orden_de_impresion = n - pasos - 1;
        std::cout << orden_de_impresion << ") " << "Rank " << rank << " recibe {" << a << ", " << b << ", " << pasos << "} y envía {"
                  << next_tripleta[0] << ", " << next_tripleta[1] << ", " << next_tripleta[2] << "}\n";

        // Enviar al siguiente
        int next = sentido ? (rank + 1) % size : (rank - 1 + size) % size;
        MPI_Send(next_tripleta, 3, MPI_INT, next, 0, MPI_COMM_WORLD);
    }
}

bool analizarArgumentos(int cantidad, char **parametros, int &pasos_fibonacci, bool &sentido, bool &terminar_en_cero)
{
    bool condicion = true;
    for (int i = 1; i < cantidad; i++)
    {
        if (strncmp(parametros[i], "-n=", 3) == 0)
        {
            pasos_fibonacci = atoi(parametros[i] + 3);
        }
        else if (strncmp(parametros[i], "-s=", 3) == 0)
        {
            sentido = atoi(parametros[i] + 3);
        }
        else if (strncmp(parametros[i], "-f=", 3) == 0)
        {
            terminar_en_cero = atoi(parametros[i] + 3);
        }
        else
        {
            std::cerr << "ERROR: Parámetro desconocido: " << parametros[i] << "\n";
            condicion = false;
        }
    }
    return condicion;
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);
    int pasos_fibonacci = 8;
    bool sentido = true;
    bool terminar_en_cero = true;

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (size < 2)
    {
        if (rank == 0)
            std::cerr << "Error: Este programa requiere al menos 2 procesos MPI.\n";
        MPI_Finalize();
        return 0;
    }
    if (!analizarArgumentos(argc, argv, pasos_fibonacci, sentido, terminar_en_cero))
    {
        if (rank == 0)
            std::cerr << "Error: Argumentos incorrectos.\n";

        MPI_Finalize();
        return 0;
    }

    double inicio, fin;

    inicio = MPI_Wtime();

    int tripleta[3];
    if (!terminar_en_cero)
    {
        fibonacci_desde_0(tripleta, pasos_fibonacci, rank, size, sentido);
    }
    else
    {
        int k = pasos_fibonacci - 1;
        int rank_inicial = sentido ? (size - (k % size)) % size : (k % size);
        fibonacci_para_0(tripleta, pasos_fibonacci, rank, size, sentido, rank_inicial);
    }

    fin = MPI_Wtime();

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    {
        std::cout << "Tiempo: " << (fin - inicio) << " segundos\n";
    }

    MPI_Finalize();
    return 0;
}