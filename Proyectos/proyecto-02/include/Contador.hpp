#pragma once
#include "FileReader.hpp"
#include<time.h>

class Contador{

    private:
        int hilos;
        int estrategia;
        int numLineas;
        double tiempo_ejecucion;
        std::string filename;
        std::map<std::string, int> tagCount;
        FileReader reader;

    public:
        Contador(int hilos, int est, std::string filename);
        ~Contador();
        void empezar_lectura();
        void imprimir_datos();
};