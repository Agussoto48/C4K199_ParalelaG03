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

void FileReader::iniciar_conteo(){
    //Puntero generico para que apunte a una fucnion
    void* (*estrategia_escogida)(void*) = nullptr;
    switch (estrategia) {
        case 1: estrategia_escogida = estrategia_1; break;
        case 2: estrategia_escogida = estrategia_2; break;
        case 3: estrategia_escogida = estrategia_3; break;
        case 4: estrategia_escogida = estrategia_4; break;
        default:
            std::cerr << "Estrategia inválida en archivo: " << filename << std::endl;
            return;
    }
    //Revisar que si tiene asignada funcion
    if (!estrategia_escogida){
        std::cerr << "\nAlgo salió mal al asignar la estrategia en el archivo: " << this->filename << std::endl;
        return;
    } 

    //Creacion y destruccion de los hilos, pasando la clase como parametro
    for (int i = 0; i < this->numHilos; ++i)
        pthread_create(&threads[i], nullptr, estrategia_escogida, this);

    for (int i = 0; i < this->numHilos; ++i)
        pthread_join(threads[i], nullptr);

}

bool FileReader::hasNext(){
        return !file.eof();
    }
std::string FileReader::getNext(){
    std::string line;
    if(std::getline(file, line)){
        return line;
    }
    return "";
}

//------------------------------Estrategias de Lectura---------------------------
void* estrategia_1(void*arg){
    std::cout << "Estratregia 1\n";   
}
void*estrategia_2(void*arg){
    std::cout<<"\nEstrategia 2\n";
}
void* estrategia_3(void*arg){
    std::cout<<"\nEstrategia 3\n";
}
void* estrategia_4(void*arg){
    std::cout<<"\nEstrategia 4\n";
}