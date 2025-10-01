#include "Cuerda.hpp"


//Constructores
Cuerda::Cuerda(int idCuerda)
    :   numMonos(0),
        idCuerda(idCuerda),
        direccion_actual(SIN_DIRECCION)
    {

    }

Cuerda::~Cuerda() = default;

//Funciones para la logica del ejercicio
/*void Cuerda::changeDirection(){
    if(cruceCount >= CambioDireccion){
        switch(direccion){
            case DirIzqADer:
                this->direccion = DirDerAIzq;
                std::cout << "Cambio de dir de cuerda " << idCuerda << " I<-D\n";
                break;
            case DirDerAIzq:
                this->direccion = DirIzqADer;
                std::cout << "Cambio de dir de cuerda " << idCuerda << " I->D\n";
                break;
        }
        cruceCount = 0;
    }
}*/
bool Cuerda::agregarMono(int direccion_mono){
    if(this->direccion_actual == SIN_DIRECCION){
        this->direccion_actual = direccion_mono;
    }
    if(this->numMonos < MaxEnCuerda && direccion_mono == direccion_actual){
        this->numMonos++;
        return true;
    }
    //std::cout<<"Capacidad maxima alcanzada de cuerda " << idCuerda << "\n";
    return false;
}
void Cuerda::liberarMono(){
    if(this->numMonos > 0){
        //Implementar que compruebe la direccion que lleva el mono
        //No solo en esta funcion
        this->numMonos--;
    }
    //Si la cuerda se queda sin monos, entonces está libre para usar para cualquier lado
    if(this->numMonos == 0){
        this->direccion_actual = SIN_DIRECCION;
    }
}
