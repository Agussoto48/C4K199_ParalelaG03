#include "conditionS.hpp"
#include "Tren.hpp"
#include "Lock.hpp"

class Monitor{
private:
    Lock * candado;
    enum {ESPERANDO = 0, EN_TREN = 1, PASADO = 2} state[256];
    int prioridad[256] = {0};
    int numPasajeros;
    int capacidadTren;
    int actuales = 0;
    Condition  * pasajeros[256];
    Tren tren;
    void test(int cual){
        if(this->state[cual] == ESPERANDO){
            this->state[cual] = EN_TREN;
            this->pasajeros[cual]->Signal();
        }
    }
public:
    Monitor(int n):
        numPasajeros(n),
        tren(n),
        capacidadTren(n)
        {
            for(int i = 0; i <  this -> numPasajeros; i++){
                this->state[i] = ESPERANDO; 
                pasajeros[i] = new Condition();
            }
        }
    ~Monitor(){
        for(int i = 0; i < this->numPasajeros; i++){
            delete this->pasajeros[i];
        }
    }
    void esperarTren(int cual){
        this->state[cual] = ESPERANDO;

    }
    void Abordar(int cual){
        this->candado->Acquire();
        test(cual);
        if(state[cual] == ESPERANDO){
           this->pasajeros[cual]->Wait(this->candado);
        }
        this->candado->Release();
    }
    void Salir(int cual){
        this->candado->Acquire();
        if(this->state[cual] == EN_TREN){
            tren.liberarPasajero();
        }
        this->state[cual] = PASADO;
        for(int i = 0; i < this->numPasajeros; i++){
        if(i == cual)
            continue;
        if(this->state[cual] == ESPERANDO)
            test(cual);
        }

        this->candado->Release();        
    }
    bool agregarPasajero(){
        if(actuales + 1 < capacidadTren){
            this->actuales += 1;
            return true;
        }
        return false;
    }
    void setState(){
        for(int i = 0; i < numPasajeros; i++){
            this->state[i] = ESPERANDO;
        }
    }


};