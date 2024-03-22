#include <stdio.h>
#include <omp.h> // Agregar la librería OpenMP

void arrange(int, int);
int array[100], array1[100];
int i, j, temp, max, count, maxdigits = 0, c = 0;

int main()
{
    int t1, t2, k, t, n = 1;

    printf("Enter size of array :");
    scanf("%d", &count);
    printf("Enter elements into array :");
    for (i = 0; i < count; i++)
    {
        scanf("%d", &array[i]);
        array1[i] = array[i];
    }
#pragma omp parallel private(i, j, temp, max, t, t1)
    {
        // Calcular el número de dígitos máximo para normalizar
#pragma omp for
        for (i = 0; i < count; i++)
        {
            t = array[i]; /*primer elemento en t */
            while (t > 0)
            {
                c++;
                t = t / 10; /* Encuentra el dígito más significativo */
            }
#pragma omp critical
            {
                if (maxdigits < c)
                    maxdigits = c; /* número de dígitos de cada número */
                c = 0;
            }
        }
        while (--maxdigits)
            n = n * 10;

#pragma omp for private(t1, t, max)
        for (i = 0; i < count; i++)
        {
            max = array[i] / n; /* MSB - División por la base particular */
            t = i;
            for (j = i + 1; j < count; j++)
            {
                if (max > (array[j] / n))
                {
                    max = array[j] / n; /* MSB más grande */
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
        while (n >= 1)
        {
#pragma omp for private(t1, i, j)
            for (i = 0; i < count;)
            {
                t1 = array[i] / n;
                for (j = i + 1; t1 == (array[j] / n); j++)
                    ;
#pragma omp single
                arrange(i, j);
                i = j;
            }
            n = n / 10;
        }
    } // Fin de la región paralela

    printf("\nSorted Array (Postman sort) :");
    for (i = 0; i < count; i++)
        printf("%d ", array1[i]);
    printf("\n");

    return 0;
}

/* Función para organizar la secuencia que tiene la misma base */
void arrange(int k, int n)
{
    for (i = k; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (array1[i] > array1[j])
            {
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
