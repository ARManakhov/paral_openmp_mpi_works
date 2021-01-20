/*
 * Используя возможности OpenMP, написать программу умножения матрицы на вектор. Сравнить время выполнения
 * последовательной и параллельных программ.
 */
#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
    int a[16][16];
    int b[16];

    bool randomize = true;

    printf("matrix:\n");

    for (int i = 0; i < size(a); i++) {
        for (int j = 0; j < size(a[i]); j++) {
            if (randomize) a[i][j] = rand();
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }


    printf("vector:\n");

    for (int i = 0; i < size(b); i++) {
        if (randomize) b[i] = rand();
        printf("%d\t", b[i]);
    }

    if (size(a[0]) == size(b)) {

        int c[size(a)] = { 0 };
        int maxi = size(c);
        int maxk = size(b);
        double time1 = omp_get_wtime();

        for (int i = 0; i < maxi; i++) {
            for (int k = 0; k < maxk; k++)
                c[i] += a[i][k] * b[k];
        }

        double time2 = omp_get_wtime();

        int d[size(a)] = { 0 };

        double time3 = omp_get_wtime();

        for (int i = 0; i < maxi; i++) {
#pragma omp parallel for schedule(static) num_threads(10)
            for (int k = 0; k < maxk; k++)
                d[i] += a[i][k] * b[k];
        }

        double time4 = omp_get_wtime();

        printf("answer vector in standard:\n");

        for (int i = 0; i < size(c); i++) {
            printf("%d\t", c[i]);
        }
        printf("\n");

        printf("answer vector in parallel:\n");

        for (int i = 0; i < size(d); i++) {
            printf("%d\t", d[i]);
        }
        printf("\n");

        cout<<"standard exec time is "<<time2 - time1<<"\nparalel exec time is "<<time4 - time3<<"\n";
    }
    else {
        printf("size of arrays not fit");
    }

}