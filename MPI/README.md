# Versión MPI de Postman Sort

El siguiente código es una adaptación del algoritmo Postman Sort para que pueda ejecutarse en un entorno de programación paralela utilizando la biblioteca MPI (Message Passing Interface).

## 1. CARGA DEL MODULO MPI
se debe cargar el modulo mpi

```Bash
 module load devtools/mpi/openmpi/4.0.1
 ```

## 2. COMPILAR
para compilar el codigo se hace con el siguiente comando

```Bash
 mpicc postman_sort_mpi.c -o postman_sort_mpi -lm
```

## 3. EJECUTAR

para ejecutar en GUNE se usa el siguiente comando 

```Bash
time mpirun -np 4 postman_sort_mpi
```


