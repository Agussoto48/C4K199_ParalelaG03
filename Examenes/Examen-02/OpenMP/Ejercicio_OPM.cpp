#include <cstdio>
#include <random>
#include <omp.h>
#include <iostream>
#include <exception>
#include <cstring>
#include "adn.h"

//Mi computadora tiene un total de 6 cores, 2 hilos cada uno
//El speeup dió como resultado: 1,073578595, teniendo así un 7% de mejora con respecto al serial, usando 2 hilos

bool analizarArgumentos(int cantidad, char **parametros, int &hilos);

int main(int cantidad, char **parametros)
{
    int hilos = 1;
    analizarArgumentos(cantidad, parametros, hilos);
    if(hilos < 1)
    {
        hilos = 1;
    }
    std::string eleccion = "";
    std::cout << "\nIngrese la palabra con la que quiere trabajar: ";
    std::getline(std::cin, eleccion); 
    std::cout << eleccion;

    ADN *palabra = new ADN(eleccion);
    omp_set_num_threads(hilos);
    double inicio = omp_get_wtime();

    double final = omp_get_wtime();

    std::string palindromo = palabra->Palindromo();

    double total = final - inicio;

    if (palindromo.size() <= 1)
    {
        std::cout << "\nNo hay palindromo en esa palabra" << std::endl;
    }
    else
    {
        std::cout << "\npalindromo: " << palindromo << std::endl;
        std::cout << "\nTamaño del palindromo: " << palindromo.size() << std::endl;
    }
    std::cout << "\nTiempo final: " << total << std::endl;
    return 0;
}
bool analizarArgumentos(int cantidad, char **parametros, int &hilos)
{
    bool condicion = true;
    for (int i = 1; i < cantidad; i++)
    {
        if (strncmp(parametros[i], "-h=", 3) == 0)
        {
            hilos = atoi(parametros[i] + 3);
        }
        else
        {
            std::cerr << "ERROR: Parámetro desconocido: " << parametros[i] << "\n";
            condicion = false;
        }
    }
    return condicion;
}