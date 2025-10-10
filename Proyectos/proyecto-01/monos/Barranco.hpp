#pragma once
#include "Cuerda.hpp"
#include "conditionS.hpp"

#define MONOS_DEFAULT 10

enum {CUERDA_1 = 1, CUERDA_2 = 2};


class Barranco{
    private:
        Lock * candado;
        int cantidadMonos;
        //arreglos para controlar el comportamiento de los monos
            enum {ESPERANDO = 0, EN_CUERDA_1 = 1, EN_CUERDA_2 = 2, PASO = 3} state[256];
            int origen_mono[256];
            int cuerda_elegida[256];
        Condition * monos[256];
        Cuerda cuerda1;
        Cuerda cuerda2;
        void test(int mono);

        void testCuerda1(int mono);
        void testCuerda2(int mono);


    public:
        //Constructores y destructor
        Barranco(int cantidad);
        ~Barranco();   

        //Funciones para la logica del juego
        void entrarPuente(int mono, int puente);
        void entrarCuerda1(int mono);
        void entrarCuerda2(int mono);

        void cruzar(int mono);
        void cruzarCuerda1(int mono);
        void cruzarCuerda2(int mono);

        bool comprobar_paso(int mono);
        void setDireccion(int mono, int dir);
        void print();
        void cuentaPuentes(){
            std::cout <<"C1: " << cuerda1.getNumMonos() << "| C2: " << cuerda2.getNumMonos() << "\n";
        }

        void setState(){
            for(int i = 0; i < this->cantidadMonos; i++){
                state[i] = ESPERANDO;
                origen_mono[i] = -1;
            }
        }
        void setCuerda(int mono, int cuerda){
            this->cuerda_elegida[mono] = cuerda;
        }
        void printEstados(){
            for(int i = 0; i < this->cantidadMonos; i++){
                std::cout << state[i] << " | ";
            }
            std::cout<<"\n";
        }
        int getEstado(int mono){
            return this->state[mono];
        }
};