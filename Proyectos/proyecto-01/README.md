# Tarea Programada 1

## Descripción
Este proyecto implementa la resolución de la **Tarea Programada 1** del curso CI-0117 Programación Concurrente y Paralela.  

Se desarrollan dos simulaciones independientes:
1. **Monos cruzando un barranco** (problema de sincronización).  
2. **Juego de la papa caliente** (problema de mensajes).  


## Estructura de fuentes
- `monos/*.cpp` → implementación del problema de los monos.  
- `PapaCaliente/*.cpp` → implementación del juego de la papa.  
- `../EntregasSemanales/shared/*.cpp` → código compartido (clases `Semaforo`, `Buzon`, etc.).  
- Ejecutables generados en `bin/`.  



## Ejercicios


### Monos
- **Parámetro:** `N` → número de monos a crear.  
- Cada mono obtiene un ID único.  
- Se controla el cruce del barranco asegurando que se respeten las condiciones de seguridad (sin choques).  

### Papa Caliente
- **Parámetros:**
  1. `n` → número de jugadores en la ronda.  
  2. `v` → valor inicial de la papa.  
  3. `clockwise` → dirección de giro (`1` horario, `0` antihorario).  
- Cada jugador espera su turno, aplica la regla de **Collatz** al valor de la papa y la pasa al siguiente.  
- Si la papa llega a 1, el jugador sale de la ronda.  
- El último jugador activo es declarado ganador.  
- Se simula también la acción de un **invasor**, que envía mensajes falsos a la ronda.  


## Compilación y ejecución

Este proyecto incluye un **Makefile** para facilitar la compilación:

### Como usarlo:
- `make buildMonos` → compila la simulación de monos.  
- `make buildPapa` → compila la simulación de la papa caliente.  
- `make` → compila ambos programas.  
- `make runMonos ARGS="..."` → ejecuta el binario de monos con argumentos.  
- `make runPapas ARGS="..."` → ejecuta el binario de la papa con argumentos.  
- `make clean` → elimina el directorio `bin/` con los ejecutables.  

## Ejemplos ejecución
### Monos
Ejecutar la simulación con 15 monos:
```bash
make runMonos ARGS="15"
```
### Papas
Ejecutar la simulación con de 25 jugadores, empezando en el jugador 7 y sentido antihorario:
```bash
make runPapas ARGS="25 7 0"
```
