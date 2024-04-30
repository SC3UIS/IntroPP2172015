#include <stdio.h>
#include <mpi.h>

void arrange(int, int, int[], int[]); // Añadir array y array1 como parámetros

int main(int argc, char **argv) {
    int rank, size, count;
    int array[100], array1[100];
    int i, j, temp, max, maxdigits = 0, c = 0, n = 1;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter size of array: ");
        scanf("%d", &count);

        printf("Enter elements into array: ");
        for (i = 0; i < count; i++) {
            scanf("%d", &array[i]);
            array1[i] = array[i];
        }

        for (i = 0; i < count; i++) {
            int t = array[i];
            while (t > 0) {
                c++;
                t = t / 10;
            }
            if (maxdigits < c)
                maxdigits = c;
            c = 0;
        }

        while (--maxdigits)
            n = n * 10;
    }

    MPI_Bcast(&count, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(array, count, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(array1, count, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int chunk_size = count / size;
    int start = rank * chunk_size;
    int end = (rank == size - 1) ? count : start + chunk_size;

    for (i = start; i < end; i++) {
        max = array[i] / n;
        int t = i;
        for (j = i + 1; j < count; j++) {
            if (max > (array[j] / n)) {
                max = array[j] / n;
                t = j;
            }
        }
        temp = array1[t];
        array1[t] = array1[i];
        array1[i] = temp;
        temp = array[t];
        array[t] = array[i];
        array[i] = temp;
    }

    n = n / 10;

    while (n >= 1) {
        for (i = start; i < end;) {
            int t1 = array[i] / n;
            for (j = i + 1; t1 == (array[j] / n); j++);
                arrange(i, j, array, array1); // Pasar array y array1 como argumentos
            i = j;
        }
        n = n / 10;
    }

    MPI_Gather(array1 + start, chunk_size, MPI_INT, array1, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("\nSorted Array (Postman sort) :");
        for (i = 0; i < count; i++)
            printf("%d ", array1[i]);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}

void arrange(int k, int n, int array[], int array1[]) { // Agregar array y array1 como parámetros
    int i, j, temp;
    for (i = k; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (array1[i] > array1[j]) {
                temp = array1[i];
                array1[i] = array1[j];
                array1[j] = temp;
                temp = (array[i] % 10);
                array[i] = (array[j] % 10);
                array[j] = temp;
            }
        }
    }
}
