# Proyecto: Contador de Etiquetas HTML con Pthreads  

Este programa analiza archivos HTML y cuenta la cantidad de etiquetas que contiene, utilizando programación paralela conpthreads.
Permite probar las estrategias definidas en el enunciado entre los hilos y la estrategia adicinoal, la cual es explicará más adelante.

## Estrategia 4

Esta estrategia consiste en otorgar lineas a los hilos de manera aleatoria, parecida a la estrategia 3, pero en vez de revisar la linea siguiente disponible, elije una linea aleatoriomente y trabaja con ella, una vez trabajada no se puede leer mas y tocará leer con el resto de lineas que no han sido seleccionadas aún.

---

## Estructura del proyecto  

    Proyecto/

    ├── Makefile

    ├── src/ # Archivos fuente del programa (.cpp)

    ├── include/ # Archivos de encabezado (.hpp)

    ├── html/ # Carpeta donde deben estar los archivos HTML a analizar

    ├── bin/ # (Se crea automáticamente al compilar)


## Para compilar el proyecto:  
```bash
make build
```
o también
```
make 
```
## Estructura de como correr el programa
```
make run ARGS="-t=<num_hilos> <archivo.html> -e=<estrategia>"
```
Ejemplo:
```
make run ARGS="-t=50 archivo.html -e=2"
```
**NOTA:** Solo se tiene que poner el nombre del archivo y no la ruta completa (ej: html/archivo.html), pero es importante que este archivo esté dentro de la carpeta html, si no no lo leerá 

## Limpiar el bin
```
make clean
```