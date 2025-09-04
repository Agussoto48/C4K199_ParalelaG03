# Ejercicios de Comunicación y Sincronización en C++

## Descripción

Este semana contiene varios programas en C/C++ que implementan la comunicación entre procesos con buzones. 

El `Makefile` permite compilar y ejecutar fácilmente los distintos programas, organizándolos en la carpeta `bin`.

## Makefile

- `make` o `make default` : Compila todos los programas (con clases, sin clases y los ejercicios adicionales).  
- `make buildClase` : Compila los programas de **enviar y recibir con clases**.  
- `make buildSinClase` : Compila los programas de **enviar y recibir sin clases**.  
- `make buildPi` : Compila el ejercicio de cálculo de **Pi por series**.  
- `make buildSHM` : Compila el ejercicio de **memoria compartida con semáforos**.  
- `make buildSu` : Compila el ejercicio de **SumaUno**.  

### Ejecución
- `make runEC` : Ejecuta el programa **enviar con clases**.  
- `make runRC` : Ejecuta el programa **recibir con clases**.  
- `make runE` : Ejecuta el programa **enviar sin clases**.  
- `make runR` : Ejecuta el programa **recibir sin clases**.  
- `make runPi` : Ejecuta el programa de **Pi por series**.  
- `make runShm` : Ejecuta el programa de **memoria compartida**.  
- `make runSU` : Ejecuta el programa de **SumaUno**.  

### Limpieza
- `make clean` : Elimina todos los ejecutables dentro de la carpeta `bin`.
