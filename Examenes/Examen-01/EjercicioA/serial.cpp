#include <iostream>
#include<vector>
#include<random>
#include<time.h>

int peso;
int tamaño;

int rng(int min, int max){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(generator);
}



int main(){
    std::cout << "Digite el peso maximo del carrito: ";
    std::cin >> peso;
    peso = 10;
    std::cout << "Digite la cantidad de productos: ";
    std::cin >> tamaño;
    tamaño = 6;
    std::vector<int> precios = {20, 5, 10, 40, 15, 25};
    std::vector<int> pesos = {1, 2, 3, 8, 7, 4};
    /*for(int i = 0; i < tamaño; i++){
        precios[i] = rng(tamaño, (tamaño*10));
        pesos[i] = rng(1, tamaño);
    }*/
    int precio_max = 0;
    int peso_acumulado = 0;
    int precio_acumulado = 0;
    int count = 0;
    std::vector<int> mas_pesados;
    int max = 0;
    int inicio = clock();
    int j;
    for(int i = 0; i < tamaño; i++){
        if(max < pesos[i]){
            max = pesos[i];
            j = i;
        }
    }
    int pesoMax = 10;
    int n = precios.size();

    std::vector<int> ganancia(pesoMax + 1, 0);  // ganancia[w] = ganancia máxima con peso w

    for (int i = 0; i < n; ++i) {
        for (int w = pesoMax; w >= pesos[i]; --w) {
            ganancia[w] = std::max(ganancia[w], ganancia[w - pesos[i]] + precios[i]);
        }
    }
    std::cout << "Ganancia máxima: " << ganancia[pesoMax] << std::endl;
    int fin = clock();


    double tiempo = (double)(fin - inicio)/CLOCKS_PER_SEC;
    std::cout << "Tiempo Serial: " << tiempo << std::endl;

    return 0; 
}