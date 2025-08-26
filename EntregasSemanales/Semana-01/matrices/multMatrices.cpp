#include<iostream>

int rangoMatriz();
void pedirDatosMatriz(int** matriz, int rango, int &num);
void multiplicacion(int** matriz1, int** matriz2, int** res, int rango);
void imprimirMatriz(int** matriz, int rango);

int main(){
    int rango = rangoMatriz();
    int **matriz1 = new int*[rango], **matriz2 = new int*[rango], **resultado = new int*[rango];
    for(int i = 0; i < rango; i++){
        matriz1[i] = new int[rango];
        matriz2[i] = new int[rango];
        resultado[i] = new int[rango];
    }
    int num = 1;
    pedirDatosMatriz(matriz1, rango, num);
    pedirDatosMatriz(matriz2, rango, num);
    multiplicacion(matriz1, matriz2, resultado, rango);
    imprimirMatriz(resultado, rango);
    for(int i = 0; i < rango; i++){
        delete matriz1[i];
        delete matriz2[i];
        delete resultado[i];
    }
    delete[] matriz1;
    delete[] matriz2;
    delete[] resultado;

    return 0;
}

int rangoMatriz(){
    std::cout << "Digite el rango de la matriz: ";
    int rango;
    std::cin >> rango;
    return rango;
}
void pedirDatosMatriz(int** matriz, int rango, int &num){
    std::cout<<"Datos Matriz de la " << num++ << "\n";
    for(int i = 0; i < rango; i++){
        for(int j = 0; j < rango; j++){
            std::cout<< "Digite el numero [" << i << "][" << j << "]: ";
            std::cin >> matriz[i][j]; 
        }
    }
}
void multiplicacion(int** matriz1, int** matriz2, int** res ,int rango){
    for(int i = 0; i < rango; i++){
        for(int j = 0; j < rango; j++){
            res[i][j] = 0;
            res[i][j] += matriz1[i][j] * matriz2[i][j];
        }
    }
}
void imprimirMatriz(int** matriz, int rango){
    std::cout<<"Matriz final: \n";
    for(int i = 0; i < rango; i++){
        for(int j = 0; j < rango; j++){
            std::cout<< matriz[i][j] << " |";
        }
        std::cout<<"\n";
    }
}