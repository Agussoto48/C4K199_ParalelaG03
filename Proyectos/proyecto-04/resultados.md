## Tabla de Tiempos

| Trabajadores (NP) | Serial (s)     | MPI (s)          |
|-------------------|----------------|------------------|
| 1                 | 0.0701292      | 0.0701292        |
| 4                 | 0.0701292      | 0.0397747        |
| 8                 | 0.0701292      | 0.0370318        |
| 12                | 0.0701292      | 0.0307666        |
| 16                | 0.0701292      | 0.031382         |
| 24                | 0.0701292      | 0.0334587        |

# Analisis

En las pruebas realizadas se observa que la versión serial mantiene un tiempo de ejecución bastante estable, cercano a los 0.07 segundos, ya que todo el cálculo de la subsecuencia común más larga (LCS) se realiza dentro de un solo proceso sin tener que comunicarse con otros hilos, por otra parte, la versión paralela con MPI muestra una mejora en la ejecución cuando se utilizan varios procesos, especialmente al pasar de 1 a 8 u 12 trabajadores. Esto se debe a que el algoritmo distribuye las ramas iniciales de búsqueda entre diferentes procesos, permitiendo que cada hilo explore una posible subsecuencia de manera independiente, pero después de cierto punto (por ejemplo, al usar 16 procesos), el tiempo empieza a aumentar levemente, lo que podría indicar un tope de lo que se puede distribuir dentro del algoritmo hasta ciertos procesos.
