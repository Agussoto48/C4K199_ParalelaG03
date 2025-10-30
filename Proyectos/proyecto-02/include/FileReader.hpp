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
    int contarLineas();

    bool hasNext(){
        return !file.eof();
    }
    std::string getNext(){
        std::string line;
        if(std::getline(file, line)){
            return line;
        }
        return "";
    }

    //Estrategias
    static void* estrategia_1(void* arg);
    static void* estrategia_2(void* arg);
    static void* estrategia_3(void* arg);
    static void* estrategia_4(void* arg);
};
