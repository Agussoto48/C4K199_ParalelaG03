#pragma once
#include "FileReader.hpp"

class Contador{

    private:
        int hilos;
        int estrategia;
        int numLineas;
        std::string filename;
        std::map<std::string, int> tagCount;
        FileReader reader;

    public:
        Contador(int hilos, int est, std::string filename);
        ~Contador();
        void empezar_lectura();
        void printResults() const;  
        void imprimir_datos();
};