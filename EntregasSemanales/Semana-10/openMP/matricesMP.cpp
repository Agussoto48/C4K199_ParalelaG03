#include <iostream>
#include <random>
#include <iomanip>
#include <time.h>
#include <omp.h>

#define RANGO 25

int A[RANGO][RANGO];
int B[RANGO][RANGO];
int C[RANGO][RANGO];

int rng(int min, int max);

void printA() {
    std::cout << "\nMatriz A:\n"; 
    for (int i = 0; i < RANGO; i++) {
        for (int j = 0; j < RANGO; j++) {
            std::cout << std::setw(4) << A[i][j] << "|";
        }
        std::cout << "\n";
    }
}

void printB() {
    std::cout << "\nMatriz B:\n";
    for (int i = 0; i < RANGO; i++) {
        for (int j = 0; j < RANGO; j++) {
            std::cout << std::setw(4) << B[i][j] << "|";
        }
        std::cout << "\n";
    }
}

void printC() {
    std::cout << "\nMatriz C:\n";
    for (int i = 0; i < RANGO; i++) {
        for (int j = 0; j < RANGO; j++) {
            std::cout << std::setw(4) << C[i][j] << "|";
        }
        std::cout << "\n";
    }
}

int main() {
    for (int i = 0; i < RANGO; i++) {
        for (int j = 0; j < RANGO; j++) {
            A[i][j] = rng(1, 9);
            B[i][j] = rng(1, 9);
            C[i][j] = 0;
        }
    }

    printA();
    printB();

    int procesos = rng(2, 5);
    omp_set_num_threads(procesos);
    std::cout << "\nNúmero de hilos: " << procesos << std::endl;

    double inicio = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < RANGO; i++) {
        for (int j = 0; j < RANGO; j++) {
            C[i][j] = A[i][j] * B[i][j];
        }
    }

    double fin = omp_get_wtime();

    printC();
    std::cout << "\nTiempo ejecutado: " << (fin - inicio) << " segundos" << std::endl;

    return 0;
}

int rng(int min, int max) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(generator);
}
