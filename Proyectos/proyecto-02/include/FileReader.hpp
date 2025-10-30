#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include<vector>
#include <string>
#include<pthread.h>

class FileReader {
private:
    int numHilos;
    int estrategia;
    int numLineas;
    std::string filename;
    std::ifstream file;
    std::map<std::string, int> tagCount;
    std::vector<std::string> lineas;

    //Variables para pthreads
    pthread_t* threads;
    pthread_mutex_t mutex;

public:
    FileReader(int hilos, int estrategia, std::string filename);
    ~FileReader();

    //Lógica para contar tags
    void contarLineas();
    void iniciar_conteo();
    void agregar_tags(std::map<std::string, int> hilo_tags);

    //Comprobantes para seguir leyendo
    bool hasNext();
    std::string getNext();
};

//Estrategias
void* estrategia_1(void* arg);
void* estrategia_2(void* arg);
void* estrategia_3(void* arg);
void* estrategia_4(void* arg);