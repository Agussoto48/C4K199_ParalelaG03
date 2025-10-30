#include "Contador.hpp"

Contador::Contador(int hilos, int est, std::string filename):
    hilos(hilos), estrategia(est), filename(filename), reader(hilos, est,filename)
    {
    }

Contador::~Contador(){}


void Contador::empezar_lectura(){
    reader.iniciar_conteo();
}

void Contador::printResults() const{
    for (const auto &pair : tagCount) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

void Contador::imprimir_datos(){
    std::cout<<"\n------------------------------";
    std::cout << "\nHilos: " << this->hilos << ", Est: " << this->estrategia << ", file: " << this->filename; 
    std::cout << std::endl;
}