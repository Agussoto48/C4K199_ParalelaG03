# Proyecto: Comparación de ADN con Paralelismo MPI

Este proyecto implementa un programa en C++ capaz de encontrar la **subsecuencia común más larga (LCS)** entre dos cadenas de ADN.  
La solución incluye:

- Una versión serial
- Una versión paralela usando **MPI**

El objetivo es comparar secuencias de ADN de manera eficiente, aprovechando múltiples procesos de ejecución.


## Objetivo del Proyecto

Dadas dos cadenas de ADN (compuestas de A, C, G, T), el programa calcula la subsecuencia común más larga entre ambas,  
la versión paralela divide el árbol de búsqueda del algoritmo en ramas independientes, asignando cada una a un proceso MPI distinto.


## Estructura del Proyecto

- /src  
  - main.cpp  
  - adn.cpp  
- /include  
  - adn.h  
- /bin  
- Makefile  
- README.md  
- resultados.md

---
## Requerimientos

Debe tener instalado:

- **g++ o mpicxx**
- **OpenMPI**
- Make

En Ubuntu/Debian:

```bash
sudo apt install openmpi-bin libopenmpi-dev
```

## Descripción del Makefile

El proyecto utiliza un Makefile para automatizar las tareas de compilación, ejecución y limpieza del programa, este está configurado para compilar código C++ con soporte para MPI utilizando `mpicxx`.

### Comandos

* Compilación: `make` o `make build`
* Ejecución: `make run NP=x`, donde x es el numero de hilos
* Limpieza: `make clean`

# Autores

* Agustín Soto C4K199
* Andrés Salas C37104

