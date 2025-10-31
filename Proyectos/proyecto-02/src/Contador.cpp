#include "Contador.hpp"

Contador::Contador(int hilos, int est, std::string filename):
    hilos(hilos), estrategia(est), filename(filename), reader(hilos, est,filename)
    {
    }

Contador::~Contador(){}


void Contador::empezar_lectura(){
    reader.iniciar_conteo();

    tiempo_ejecucion = this->reader.getTiempo();
}
void Contador::imprimir_datos(){
    this->reader.imprimir_tags();
    std::cout<<"-----------Informacion--------------------" << std::endl;
    std::cout << "Numero de hilos: " << this->hilos << std::endl;
    std::cout << "Estrategia implementada: " << this->estrategia << std::endl;
    if(this->reader.getTiempo() > 0) std::cout << "Tiempo de ejecucion: " << this->tiempo_ejecucion << std::endl;
    std::cout<<"-----------Fin de informacion-------------" << std::endl;
}