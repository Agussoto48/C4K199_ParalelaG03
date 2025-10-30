#include "Contador.hpp"



int main(int argc, char* argv[]) {
    std::string basePath = "files/";
    // Validar argumentos
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " archivo1.html [archivo2.html ...]" << std::endl;
        return 1;
    }
    return 0;
}