#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <pthread.h>

int n;
bool encontrado = false;
int primo1 = 0, primo2 = 0;
pthread_mutex_t mutex;

bool esPrimo(int num) {
    if (num < 2) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

struct Rango {
    int inicio;
    int fin;
    std::vector<int>* primos;
};

void* buscarSuma(void* arg) {
    Rango* r = (Rango*)arg;
    std::vector<int>& primos = *(r->primos);

    for (int i = r->inicio; i < r->fin && !encontrado; ++i) {
        for (size_t j = i; j < primos.size() && !encontrado; ++j) {
            if (primos[i] + primos[j] == n) {
                if(encontrado)
                    return nullptr;
                pthread_mutex_lock(&mutex);
                if (!encontrado) {
                    encontrado = true;
                    primo1 = primos[i];
                    primo2 = primos[j];
                }
                pthread_mutex_unlock(&mutex);
                return nullptr;
            }
            if(encontrado)
                return nullptr;
        }
    }
    return nullptr;
}

int main() {
    std::cout << "Ingrese un numero par mayor o igual a 4: ";
    std::cin >> n;

    if (n < 4 || n % 2 != 0) {
        std::cout << "El numero debe ser par y mayor o igual a 4." << std::endl;
        return 0;
    }

    int numHilos;
    std::cout << "Ingrese la cantidad de hilos: ";
    std::cin >> numHilos;

    clock_t inicio = clock();

    // Genera lista de números primos hasta n
    std::vector<int> primos;
    for (int i = 2; i <= n; i++) {
        if (esPrimo(i)) primos.push_back(i);
    }

    pthread_t hilos[numHilos];
    pthread_mutex_init(&mutex, nullptr);

    int total = primos.size();
    int rango = total / numHilos;
    std::vector<Rango> rangos(numHilos);

    for (int i = 0; i < numHilos; ++i) {
        rangos[i].inicio = i * rango;
        rangos[i].fin = (i == numHilos - 1) ? total : (i + 1) * rango;
        rangos[i].primos = &primos;
        pthread_create(&hilos[i], nullptr, buscarSuma, &rangos[i]);
    }

    for (int i = 0; i < numHilos; ++i) {
        pthread_join(hilos[i], nullptr);
    }

    clock_t fin = clock();
    double tiempo = double(fin - inicio) / CLOCKS_PER_SEC;

  
    std::cout << "Representacion de " << n << " como suma de dos primos:\n" << n << " = " << primo1 << " + " << primo2 << std::endl;
    std::cout << "\nTiempo de ejecucion: " << tiempo << " segundos\n";

    pthread_mutex_destroy(&mutex);
    return 0;
}