#include "Barranco.hpp"


Barranco::Barranco(int cantidad)
    :   cuerda1(1),
        cuerda2(2),
        cantidadMonos(cantidad)
    {
        candado = new Lock();
        for(int i = 0; i < this->cantidadMonos; i++){
            this -> state[i] = ESPERANDO;
            this -> monos[i] = new Condition();
        }

    }
Barranco::~Barranco() {
    delete candado;
    for(int i = 0; i < this->cantidadMonos; i++){
        delete this->monos[i];
    }
}   


//Secciones critica
void Barranco::entrarCuerda1(int mono){
    this->candado->Acquire();
    
    testCuerda1(mono);

    if(state[mono] == ESPERANDO){
        this->monos[mono]->Wait(this->candado);
    }

    this->candado->Release();
}
void Barranco::entrarCuerda2(int mono){
    this->candado->Acquire();
    
    testCuerda2(mono);

    if(state[mono] == ESPERANDO){
        this->monos[mono]->Wait(this->candado);
    }
    this->candado->Release();
}
//Esta funcion sera reemplazada por las de arriba
/*
    NO OLVIDAR ESTO
*/
void Barranco::entrarPuente(int mono, int puente){
    this->candado->Acquire();
    test(mono);
    if(state[mono] != EN_CUERDA_1 || state[mono] != EN_CUERDA_2){
        this->monos[mono]->Wait(this->candado);
    }
    this->candado->Release();
}
//Seccion critica
void Barranco::cruzar(int mono){
    this->candado->Acquire();
    if(this->state[mono] == EN_CUERDA_1){
        this->cuerda1.liberarMono();
    }
    else if(this->state[mono] == EN_CUERDA_2) {
        this->cuerda2.liberarMono();
    }
    this->state[mono] = PASO;

    //Cambiar a que no dependa del origen de los monos sino a la cuerda elegida
    for(int mono = 0; mono < this->cantidadMonos; mono++){
        if(this->cuerda_elegida[mono] == CUERDA_1){
            testCuerda1(mono);
        }
        else {
            testCuerda2(mono);
        }
    }

    this->candado->Release();
}
void Barranco::cruzarCuerda1(int mono){
    this->candado->Acquire();
    if(this->state[mono] == EN_CUERDA_1){
        this->cuerda1.liberarMono();
    }
    this->state[mono] = PASO;
    for(int i = 0; i < this->cantidadMonos; i++){
        if(i == mono)
            continue;
        if(this->cuerda_elegida[i] == CUERDA_1){
            if(this->state[mono] == ESPERANDO)
                testCuerda1(mono);
        }
    }
    this->candado->Release();
}
void Barranco::cruzarCuerda2(int mono){
    this->candado->Acquire();
    if(this->state[mono] == EN_CUERDA_2){
        this->cuerda2.liberarMono();
    }
    this->state[mono] = PASO;
    for(int i = 0; i < this->cantidadMonos; i++){
        if(i == mono)
            continue;
        if(this->cuerda_elegida[i] == CUERDA_2){
            if(this->state[mono] == ESPERANDO)
                testCuerda2(mono);
        }
    }
    this->candado->Release();
}

void Barranco::test(int mono){
    if(this->origen_mono[mono] == IZQUIERDA){ 
        if(state[mono] == ESPERANDO && cuerda1.agregarMono(this->origen_mono[mono])){
            state[mono] = EN_CUERDA_1;
            monos[mono]->Signal();
        }
    }
    else {
        if(state[mono] == ESPERANDO && cuerda2.agregarMono(this->origen_mono[mono])){
            state[mono] = EN_CUERDA_2;
            monos[mono]->Signal();
        }
    }
}

//Nuevos tests individuales

void Barranco::testCuerda1(int mono){
    if(this->state[mono] == ESPERANDO && cuerda1.agregarMono(this->origen_mono[mono])){
        this->state[mono] = EN_CUERDA_1;
        this->monos[mono]->Signal();
    }
}
void Barranco::testCuerda2(int mono){
    if(this->state[mono] == ESPERANDO && cuerda2.agregarMono(this->origen_mono[mono])){
        this->state[mono] = EN_CUERDA_2;
        this->monos[mono]->Signal();
    }
}



bool Barranco::comprobar_paso(int mono){
    if(state[mono] == PASO)
        return true;
    return false;
    
}

void Barranco::setDireccion(int mono, int dir){
    this->origen_mono[mono] = dir;
}

void Barranco::print(){
    this->candado->Acquire();

    std::cout << "Lado Izquierdo (Sin pasar): ";
    for(int i = 0; i < this->cantidadMonos; i++){
        char l = (this->origen_mono[i] == IZQUIERDA) ? 'I' : 'D';
        if(state[i] == ESPERANDO && origen_mono[i] == IZQUIERDA)
            std::cout<< i << "(" << this->cuerda_elegida[i] << "," << l << ")" << ", ";
    }
    std::cout<<"\n";
    std::cout << "Lado Izquierdo (Pasado): ";
    for(int i = 0; i < this->cantidadMonos; i++){
        char l = (this->origen_mono[i] == IZQUIERDA) ? 'I' : 'D';
        if(state[i] == PASO && origen_mono[i] == DERECHA)
            std::cout<< i << "(" << this->cuerda_elegida[i] << "," << l << ")" << ", ";
    }
    std::cout<<"\n";

    std::cout<<"Cuerda1: ";
    for(int i = 0; i < this->cantidadMonos; i++){
        char l = (this->origen_mono[i] == IZQUIERDA) ? 'I' : 'D';
        if(state[i] == EN_CUERDA_1)
            std::cout<< i << "(" << this->cuerda_elegida[i] << "," << l << ")" << ", ";
    }
    std::cout<<"\n";
    std::cout<<"Cuerda2: ";
    for(int i = 0; i < this->cantidadMonos; i++){
        char l = (this->origen_mono[i] == IZQUIERDA) ? 'I' : 'D';
        if(state[i] == EN_CUERDA_2)
            std::cout<< i << "(" << this->cuerda_elegida[i] << "," << l << ")" << ", ";
    }
    std::cout<<"\n";


    std::cout << "Lado Derecho (Sin pasar): ";
    for(int i = 0; i < this->cantidadMonos; i++){
        char l = (this->origen_mono[i] == IZQUIERDA) ? 'I' : 'D';
        if(state[i] == ESPERANDO && origen_mono[i] == DERECHA)
           std::cout<< i << "(" << this->cuerda_elegida[i] << "," << l << ")" << ", ";
    }
    std::cout<<"\n";
    std::cout << "Lado Derecho (Pasado): ";
    for(int i = 0; i < this->cantidadMonos; i++){
        char l = (this->origen_mono[i] == IZQUIERDA) ? 'I' : 'D';
        if(state[i] == PASO && origen_mono[i] == IZQUIERDA)
            std::cout<< i << "(" << this->cuerda_elegida[i] << "," << l << ")" << ", ";
    }
    std::cout<<"\n\n\n";

    this->candado->Release();
}