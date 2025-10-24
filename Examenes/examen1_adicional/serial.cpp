#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

bool esPrimo(int num) {
    if (num < 2) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}
int main() {
    int n;
    std::cout << "Ingrese un numero par mayor o igual a 4: ";
    std::cin >> n;

    if (n < 4 || n % 2 != 0) {
        std::cout << "El numero debe ser par y mayor o igual a 4." << std::endl;
        return 0;
    }

    clock_t inicio = clock();

    // Genera lista de números primos hasta n
    std::vector<int> primos;
    for (int i = 2; i <= n; i++) {
        if (esPrimo(i)) primos.push_back(i);
    }

    std::cout << "Representacion de " << n << " como suma de dos primos:\n";
    bool condicion = false;
    for (size_t i = 0; i < primos.size(); ++i) {
        for (size_t j = i; j < primos.size(); ++j) {
            if (primos[i] + primos[j] == n) {
                std::cout << n << " = " << primos[i] << " + " << primos[j] << std::endl;
                condicion = true;
                break;
            }
        }
        if(condicion)
            break;
    }

    clock_t fin = clock();
    double tiempo = double(fin - inicio) / CLOCKS_PER_SEC;

    std::cout << "\nTiempo de ejecucion: " << tiempo << " segundos\n";

    return 0;
}