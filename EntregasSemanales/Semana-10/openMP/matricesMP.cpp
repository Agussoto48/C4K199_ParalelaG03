#include<iostream>
#include<random>
#include<pthread.h>
#include<iomanip>
#include<time.h>
#include<omp.h>

#define RANGO 25
struct Info{
    int inicio;
    int fin;
};
int A[RANGO][RANGO];
int B[RANGO][RANGO];
int C[RANGO][RANGO];

int rng(int min, int max);
void* multiplicacion(void * arg){
    Info* informacion = (Info *) arg;
    for(int i = informacion->inicio; i <  informacion->fin; i++){
        for(int j = 0; j < RANGO; j++){
            C[i][j] = A[i][j] * B[i][j];
        }
    }
    return nullptr;
}
void printA(){
   std::cout<<"\nMatriz A:\n"; 
    for(int i = 0; i <  RANGO; i++){
        for(int j = 0; j < RANGO; j++){
            std::cout << std::setw(4) << A[i][j] << "|";
        }
        std::cout << "\n";
    }
}
void printB(){
    std::cout<<"\nMatriz B:\n";
    for(int i = 0; i <  RANGO; i++){
        for(int j = 0; j < RANGO; j++){
            std::cout << std::setw(4) << B[i][j] << "|";
        }
        std::cout << "\n";
    }
}
void printC(){
    std::cout<<"\nMatriz C:\n";
    for(int i = 0; i <  RANGO; i++){
        for(int j = 0; j < RANGO; j++){
            std::cout << std::setw(4) << C[i][j] << "|";
        }
        std::cout << "\n";
    }
}
int main(){
    for(int i = 0; i <  RANGO; i++){
        for(int j = 0; j < RANGO; j++){
            A[i][j] = rng(1, 9);
            B[i][j] = rng(1, 9);
            C[i][j] = 0;
        }
    }
    printA();
    printB();
    int procesos = rng(2, 5);
    std::cout << "numero de hilos es: " << procesos << std::endl;
    pthread_t hilos[procesos];
    Info informacion[procesos];

    int distribucion = RANGO / procesos;
    int resto = RANGO % procesos;
    int incio = clock();
    for(int i = 0; i < procesos; i++){
        if(i < resto)
        {
            informacion[i].inicio = i * (distribucion + 1);
            informacion[i].fin = informacion[i].inicio + (distribucion + 1);
        }
        else
        {
            informacion[i].inicio = i * distribucion + resto;
            informacion[i].fin = informacion[i].inicio + distribucion;
        }
        pthread_create(&hilos[i], NULL ,multiplicacion, &informacion[i]);
    }
    for(int i = 0; i < procesos; i++){
        pthread_join(hilos[i], NULL);
    }
    printC();
    int fin = clock();
    double tiempo = (double)(fin - incio)/CLOCKS_PER_SEC;
    std::cout<<"\nTiempo ejecutado: " << tiempo << std::endl;

    return 0;
}

int rng(int min, int max){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(generator);
}