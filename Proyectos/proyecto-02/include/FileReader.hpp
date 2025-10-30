#include <iostream>
#include <fstream>
#include <map>
#include<vector>
#include <string>
#include<pthread.h>

//Estructura para 
struct hilo_info{
    int linea_inicio;
    int linea_final;

};

class FileReader {
private:
    int numHilos;
    int estrategia;
    std::string filename;
    std::ifstream file;
    std::map<std::string, int> tagCount;

    pthread_t* threads;
    pthread_mutex_t mutex;

public:
    FileReader(std::string filename, int hilos, int estrategia);
    ~FileReader();

    //Lógica para contar tags
    int contarLineas();
    void iniciar_conteo();

    //Comprobantes para seguir leyendo
    bool hasNext();
    std::string getNext();
};

//Estrategias
void* estrategia_1(void* arg);
void* estrategia_2(void* arg);
void* estrategia_3(void* arg);
void* estrategia_4(void* arg);