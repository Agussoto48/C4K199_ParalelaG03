# Examen 2 _ Segundo Semestre _ 2025

### Comandos

* Compilación: `make`
* Ejecución: 
    - MPI: `make runMPI ARGS="-n=30 -s=1 -f=0" NP=x`
        - -n es: la cantidad de pasos de la serie de fibonacci
        - -s es: 1 si se quiere ir en sentido del reloj, 0 si contrareloj
        - -f es: "1" si quiere terminar en rank-0, "0" si quiere empezar desde rank-0
        - NP=x es: la cantidad de hilos que quiere trabajar, algo como: NP=6, se trabajarían 6 hilos
    - OPM `make runOPM ARGS="-h=2"`
        - -h es: la cantidad de hilos que se quieren ejecutar
* Limpieza: `make clean`

## Palindromo

La solución del palindromo se encuentran en el main (ejercicio_opm.cpp) y en adn.cpp, en adn.cpp están las funciones con la lógica del algoritmo

La impresión de los pasos aparecen algunas veces desordenados, por eso mismo se puso un prefijo con un numero para indicar el orden en el que se ejecutó el programa, ejemplo:

"1)" rank 5 ....

"3)" rank 7 ....

"2)" rank 6 ....

Aquí el orden sería rank 5 luego 6 y finalmente 7, siguiendo su prefijo correspondiente

## Fibonacci

La solución se encuentra en el main (ejercicio_mpi.cpp)

# Autor

Agustín Soto Chaves | C4K199