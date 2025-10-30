#include "Contador.hpp"

Contador::Contador(int hilos, int est, std::string filename):
    hilos(hilos), estrategia(est), filename(filename), reader(filename, hilos, est)
    {
    }

Contador::~Contador(){}


void Contador::empezar_lectura(){
    switch (estrategia)
    {
    case 1:
        reader.estrategia_1();
        break;
    case 2:
        reader.estrategia_2();
        break;
    case 3:
        reader.estrategia_3();
        break;
    case 4:
        reader.estrategia_4();
        break;
    default:
        std::cout << "Estrategia Invalida para el archivo: " << filename << std::endl;
        break;
    }
}

void Contador::printResults() const{
    for (const auto &pair : tagCount) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}