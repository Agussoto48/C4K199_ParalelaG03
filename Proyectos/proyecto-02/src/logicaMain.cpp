#include "logicaMain.hpp"

bool manejar_parametros(int argc, char* argv[], int& trabajadores, std::vector<int>& estrategias, std::vector<std::string>& archivos){
    if (argc < 4) {
        std::cerr << "\nError: Tiene que ejecutar con el formato: " << argv[0] << " -t=int file.html ... -e=int,...\n";
        return false;
    }
    std::string basePath = "html/";
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg.rfind("-t=", 0) == 0) {
            std::string valor = arg.substr(3);
            if(valor.empty()){
                std::cerr << "Error: Debe especificar la cantidad de trabjadores correctamente.\n";
                return false;
            }
            trabajadores = std::stoi(valor);
        }
        else if (arg.rfind("-e=", 0) == 0) {
            std::string lista = arg.substr(3);
            if(lista.empty()){
                std::cerr << "Error: Debe especificar la cantidad de estrategias correctamente.\n";
                return false;
            }
            std::stringstream particion(lista);
            std::string numero;
            //dividir por comas
            while (std::getline(particion, numero, ',')) {
                int estrategia = std::stoi(numero);
                if(estrategia < 1 || estrategia > 4){
                    std::cerr << "Error: Debe ingresar una estrategia valida (1-4)\n";
                    return false;
                }
                estrategias.push_back(estrategia);

            }
        }
        else {
            archivos.push_back(basePath + arg);
        }
    }
    
    //Validar
    if(trabajadores <= 0){
        std::cerr << "Error: Debe especificar una cantidad de trabjadores valida.\n";
        return false;
    }
    if (archivos.empty()) {
        std::cerr << "Error: Debe especificar al menos un archivo.\n";
        return false;
    }
    if (estrategias.size() != archivos.size()) {
        std::cerr << "Error: Debe indicar una estrategia por cada archivo, ni mas ni menos\n";
        return false;
    }
    return true;
}

void* inicializar_tareas(void* arg){
    Contador * contador = (Contador*)arg;
    contador->empezar_lectura();


    return nullptr;
}

