#include "FileReader.hpp"


/*
-----------Contructores------------------------
*/
FileReader::FileReader(int hilos, int estrategia, std::string filename):
    numHilos(hilos),  estrategia(estrategia), numLineas(0), lineaActual(0) ,filename(filename)
    {
        contarLineas();
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
void FileReader::contarLineas(){
    file.open(filename);
    if(!file.is_open()){
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return;
    }
    std::string line;
    while(std::getline(file, line)){
        this->lineas.push_back(line);
        this->numLineas++;
    }
    file.close();
}

//----------------------Empezar a Contar tags-----------------------
struct hilo_info{
    int id_hilo;
    FileReader* copia;
};
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
    for (int i = 0; i < this->numHilos; ++i){
        hilo_info *informacion = new hilo_info;
        informacion->copia = this;
        informacion->id_hilo = i;
        pthread_create(&threads[i], nullptr, estrategia_escogida, (void*)informacion);
    }
    for (int i = 0; i < this->numHilos; ++i)
        pthread_join(threads[i], nullptr);
}

//Funiones para la estrategia 3
bool FileReader::hasNext(){
    pthread_mutex_lock(&this->mutex);
    bool disponible = (this->lineaActual < numLineas);
    pthread_mutex_unlock(&this->mutex);
    return disponible;
}
std::string FileReader::getNext(){
    pthread_mutex_lock(&this->mutex);
    std::string linea;
    if (lineaActual < numLineas) {
        linea = lineas[lineaActual];
        lineaActual++;
    }
    pthread_mutex_unlock(&this->mutex);
    return linea;
}
//Zona critica, una vez terminen de contar agregar al map principal
void FileReader::agregar_tags(std::map<std::string, int> hilo_tags){
    pthread_mutex_lock(&this->mutex);
    for(const auto& [key, value] : hilo_tags){
        this->tagCount[key] += value;
    }
    pthread_mutex_unlock(&this->mutex);
}

void FileReader::imprimir_tags(){
    std::cout << std::endl;
    for(const auto& par : this->tagCount){
        std::cout << par.first << ": " << par.second << std::endl;
    }
}


//------------------------------Estrategias de Lectura---------------------------
void* estrategia_1(void*arg){
    std::map<std::string, int> hilo_tags;
    hilo_info *informacion = (hilo_info*)arg;
    FileReader * reader = informacion->copia;
    int id = informacion->id_hilo;
    
    int calculo = (reader->getNumLineas()/reader->getNumHilos());
    int inicio = id * calculo;
    int fin = (id == reader->getNumHilos() - 1)? reader->getNumLineas() : inicio + calculo;
    
    clock_t start = clock();
    for(int i = inicio; i < fin; i++){
        const std::string& linea = reader->lineas[i];
        size_t pos = 0;
        while ((pos = linea.find('<', pos)) != std::string::npos) {
            size_t cierre = linea.find('>', pos + 1);
            if (cierre != std::string::npos) {
                std::string tag = linea.substr(pos + 1, cierre - pos - 1);

                // quitar posibles espacios iniciales/finales
                tag.erase(0, tag.find_first_not_of(" \t"));
                tag.erase(tag.find_last_not_of(" \t") + 1);

                // ignorar cierres </> o comentarios <!-- -->
                if (tag.empty() || tag[0] == '/' || tag.rfind("!--", 0) == 0)
                    { pos = cierre + 1; continue; }

                // si tiene atributos, tomar solo el nombre de la etiqueta
                size_t espacio = tag.find(' ');
                if (espacio != std::string::npos)
                    tag = tag.substr(0, espacio);

                // contar una sola vez la etiqueta de apertura
                hilo_tags[tag]++;

                pos = cierre + 1;
            } else break;
        }
    }
    clock_t end = clock();
    double tiempoFinal = double (end - start)/CLOCKS_PER_SEC;
    reader->setTiempo(tiempoFinal);

    informacion->copia->agregar_tags(hilo_tags);
    delete informacion;
    return nullptr;
}
void* estrategia_2(void*arg){
    std::map<std::string, int> hilo_tags;
    hilo_info *informacion = (hilo_info*)arg;
    FileReader * reader = informacion->copia;
    int id = informacion->id_hilo;

    clock_t start = clock();
    for (int i = id; i < reader->getNumLineas(); i += reader->getNumHilos()) {
        // este hilo procesa solo las líneas que cumplan el residuo
        //if (i % reader->getNumHilos() != id) continue;

        const std::string& linea = reader->lineas[i];

        size_t pos = 0;
        while ((pos = linea.find('<', pos)) != std::string::npos) {
            size_t cierre = linea.find('>', pos + 1);
            if (cierre != std::string::npos) {
                std::string tag = linea.substr(pos + 1, cierre - pos - 1);

                // limpiar espacios
                tag.erase(0, tag.find_first_not_of(" \t"));
                tag.erase(tag.find_last_not_of(" \t") + 1);

                // ignorar cierres </...> o comentarios
                if (tag.empty() || tag[0] == '/' || tag.rfind("!--", 0) == 0) {
                    pos = cierre + 1;
                    continue;
                }

                // cortar atributos
                size_t espacio = tag.find(' ');
                if (espacio != std::string::npos)
                    tag = tag.substr(0, espacio);

                // contar etiqueta de apertura
                hilo_tags[tag]++;
                pos = cierre + 1;
            } else break;
        }
    }

    clock_t end = clock();
    double tiempoFinal = double(end - start) / CLOCKS_PER_SEC;
    reader->setTiempo(tiempoFinal);

    
    informacion->copia->agregar_tags(hilo_tags);
    delete informacion;
    return nullptr;
}
void* estrategia_3(void*arg){
    std::map<std::string, int> hilo_tags;
    hilo_info *informacion = (hilo_info*)arg;
    FileReader * reader = informacion->copia;

    clock_t start = clock();

    // Cada hilo pide líneas dinámicamente
    while (reader->hasNext()) {
        std::string linea = reader->getNext();
        if (linea.empty()) continue;

        size_t pos = 0;
        while ((pos = linea.find('<', pos)) != std::string::npos) {
            size_t cierre = linea.find('>', pos + 1);
            if (cierre == std::string::npos) break;

            std::string tag = linea.substr(pos + 1, cierre - pos - 1);

            // limpiar espacios
            tag.erase(0, tag.find_first_not_of(" \t"));
            tag.erase(tag.find_last_not_of(" \t") + 1);

            // ignorar cierres o comentarios
            if (tag.empty() || tag[0] == '/' || tag.rfind("!--", 0) == 0) {
                pos = cierre + 1;
                continue;
            }

            // cortar atributos si hay
            size_t espacio = tag.find(' ');
            if (espacio != std::string::npos)
                tag = tag.substr(0, espacio);

            hilo_tags[tag]++;
            pos = cierre + 1;
        }
    }

    clock_t end = clock();
    double tiempoFinal = double(end - start) / CLOCKS_PER_SEC;
    reader->setTiempo(tiempoFinal);


    informacion->copia->agregar_tags(hilo_tags);
    delete informacion;
    return nullptr;
}
void* estrategia_4(void*arg){
    std::map<std::string, int> hilo_tags;
    hilo_info *informacion = (hilo_info*)arg;
    std::cout << "Estratregia 4\n";   

    
    informacion->copia->agregar_tags(hilo_tags);
    delete informacion;
    return nullptr;
}