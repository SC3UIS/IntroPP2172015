# IntroPP2172015
# Implementación Paralela del Algoritmo Postman Sort con OpenMP

Este repositorio contiene una implementación paralela del algoritmo Postman Sort en C utilizando OpenMP.

## Descripción del Código

El código original implementa el algoritmo de ordenación Postman Sort en C. Este algoritmo ordena un array de números enteros en orden ascendente utilizando el método de ordenación radix. La implementación original es secuencial y ordena los elementos del array de manera serial.

## Modificaciones Realizadas

1. **Inclusión de OpenMP**: Se ha agregado la librería OpenMP para habilitar la paralelización del código.
2. **Región Paralela**: Se ha envuelto la sección del código que realiza la ordenación del array dentro de una región paralela utilizando la directiva `#pragma omp parallel`.
3. **Directivas OpenMP**: Se han agregado directivas OpenMP como `private` y `for` para especificar variables privadas y bucles paralelizables, respectivamente.
4. **Optimización**: Se han aplicado optimizaciones menores para mejorar el rendimiento de la implementación paralela.

## Ejecución del Código

### Compilación y Ejecución en Local

