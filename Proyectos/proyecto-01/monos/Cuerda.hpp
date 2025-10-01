#pragma once
#include<iostream>


#define MaxEnCuerda 3		// Capacidad máxima de la cuerda
#define CambioDireccion 5	// Cantidad permitada antes de cambiar la dirección
#define DirIzqADer 1		// El mono cruza de izquierda a derecha
#define DirDerAIzq 2		// El mono cruza de derecha a izquierda

enum {SIN_DIRECCION, IZQUIERDA = 1, DERECHA = 2};
class Cuerda{
    private:
        int numMonos;
        //Esta se define con el primer mono que entre
        int direccion_actual;
        int idCuerda;
        //Array de los monos en la cuerda
        

    public:
        //Contructores y Destructor
        Cuerda(int idCuerda);
        ~Cuerda();
        //Funciones para la logica del ejercicio
        //Esta funcion ya no tiene uso
            void changeDirection();
        //Combprobar 
        bool agregarMono(int direccion_mono);
        void liberarMono();

        //Getters
        inline int getNumMonos() {return numMonos;}
        inline int getIdCuerda() {return idCuerda;}
        inline int getDireccionCuerda() { return direccion_actual;}

};
//