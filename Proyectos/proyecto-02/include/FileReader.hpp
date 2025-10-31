#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include<vector>
#include <string>
#include<pthread.h>
#include<time.h>

class FileReader {
private:
    int numHilos;
    int estrategia;
    int numLineas;
    double tiempo_ejecutado;
    int lineaActual;
    std::string filename;
    std::ifstream file;
    std::map<std::string, int> tagCount;

    //Variables para pthreads
    pthread_t* threads;
    pthread_mutex_t mutex;

public:
    std::vector<std::string> lineas;

    FileReader(int hilos, int estrategia, std::string filename);
    ~FileReader();

    //Lógica para contar tags
    void contarLineas();
    void iniciar_conteo();
    void agregar_tags(std::map<std::string, int> hilo_tags);
    void imprimir_tags();

    //Comprobantes para seguir leyendo
    bool hasNext();
    std::string getNext();

    //Getters
    inline int getNumLineas() {return numLineas;}
    inline int getNumHilos() { return numHilos;}
    inline double getTiempo() { return tiempo_ejecutado;}

    //setters
    inline void setTiempo(double tiempoFinal) {this->tiempo_ejecutado = tiempoFinal;}
};

//Estrategias
void* estrategia_1(void* arg);
void* estrategia_2(void* arg);
void* estrategia_3(void* arg);
void* estrategia_4(void* arg);