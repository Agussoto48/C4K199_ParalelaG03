#include "FileReader.hpp"


/*
-----------Contructores------------------------
*/
FileReader::FileReader(std::string filename, int hilos, int estrategia):
    filename(filename),  numHilos(hilos), estrategia(estrategia)
    {
        pthread_mutex_init(&mutex, nullptr);
        threads = new pthread_t[numHilos];
    }
FileReader::~FileReader(){
    if(file.is_open()) file.close();
    pthread_mutex_destroy(&mutex);
    delete[] threads;
}
/*
-----------Lógica general de lectura------------------------
*/
int FileReader::contarLineas(){
    file.open(filename);
    if(!file.is_open()){
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return 0;
    }
    file.close();
}

//Estrategias
void* FileReader::estrategia_1(void*arg){
    std::cout<<"\nEstrategia 1\n";
    FileReader* trabajador = (FileReader*) arg;

    for (int i = 0; i < numHilos; ++i) {
       pthread_create(&threads[i], nullptr, estrategia_1, this); // o según la estrategia
    }

    for (int i = 0; i < numHilos; ++i) {
        pthread_join(threads[i], nullptr);
    }
    
}
void* FileReader::estrategia_2(void*arg){
    std::cout<<"\nEstrategia 2\n";
}
void* FileReader::estrategia_3(void*arg){
    std::cout<<"\nEstrategia 3\n";
}
void* FileReader::estrategia_4(void*arg){
    std::cout<<"\nEstrategia 4\n";
}