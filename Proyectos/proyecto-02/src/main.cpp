#include "logicaMain.hpp"

void menu(bool& menu_activo, int& opcion, int procesos ,std::vector<Contador*> registros, std::vector<std::string> archivos);

int main(int argc, char* argv[]) {
    int trabjadores = 0;
    std::vector<int> estrategias;
    std::vector<std::string> archivos;
    if(!manejar_parametros(argc, argv, trabjadores, estrategias, archivos)){
        return 1;
    }
    int procesos = archivos.size();
    pthread_t* threads = new pthread_t[procesos];
    std::vector<Contador*> registros;
    for(int i = 0; i < procesos; i++){
        Contador *contador = new Contador(trabjadores, estrategias[i], archivos[i]);
        registros.push_back(contador);
        pthread_create(&threads[i], nullptr, inicializar_tareas, (void*)contador);
    }
    for (int i = 0; i < procesos; i++)
        pthread_join(threads[i], nullptr);

    bool menu_activo = true;
    int opcion = 0;
    while(menu_activo){
        menu(menu_activo, opcion,procesos, registros, archivos);
    }
    for(int i = 0; i < procesos; i++){
        delete registros[i];
    }
    

    delete[] threads;
    return 0;
}

void menu(bool& menu_activo, int& opcion, int procesos ,std::vector<Contador*> registros, std::vector<std::string> archivos){
    int index = 0;
    std::cout << "Ingrese la opcion sobre la informacion que desea:" << std::endl;
    for(index = 0; index < procesos; index++){
        std::cout << index+1 << ") " << archivos[index] << std::endl;
    }
    std::cout<< index + 1 << ") Salir" << std::endl;
    std::cout << "Ingrese: "; std::cin>>opcion;
    if(opcion-1 >= 0 && opcion-1 < procesos){
        registros[opcion-1]->imprimir_datos();
    }
    else {
        std::cout<<"Saliendo del programa..." << std::endl;
        menu_activo = false;
    }
}