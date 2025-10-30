#include "Contador.hpp"

Contador::Contador(int hilos, int est, std::string filename):
    hilos(hilos), estrategia(est), filename(filename), reader(filename, hilos, est)
    {
    }

Contador::~Contador(){}


void Contador::empezar_lectura(){
    
}

void Contador::printResults() const{
    for (const auto &pair : tagCount) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}