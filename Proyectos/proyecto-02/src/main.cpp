#include "logicaMain.hpp"

int main(int argc, char* argv[]) {
    int trabjadores = 0;
    std::vector<int> estrategias;
    std::vector<std::string> archivos;
    if(!manejar_parametros(argc, argv, trabjadores, estrategias, archivos)){
        return 1;
    }
    int procesos = archivos.size();
    pthread_t* threads = new pthread_t[procesos];
    for(int i = 0; i < procesos; i++){
        Contador *contador = new Contador(trabjadores, estrategias[i], archivos[i]);
        pthread_create(&threads[i], nullptr, inicializar_tareas, (void*)contador);
    }
    for (int i = 0; i < procesos; i++)
        pthread_join(threads[i], nullptr);

    delete[] threads;
    return 0;
}