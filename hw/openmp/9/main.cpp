/*
 * Написать программу, в которой объявить иприсвоить начальные значения элементам двумерного массива d[6][8], для
 * инициализации значений использовать генератор случайных чисел. Используя конструкцию директивы omp parallel for и
 * omp critical определить минимальное и максимальное значения элементов двумерного массива. Количество нитей задать
 * самостоятельно. Результат выдать на экран.
 */

#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
    int d[6][8] = { 0 };
    for (int i = 0; i < size(d); i++) {
        for (int j = 0; j < size(d[0]); j++) {
            d[i][j] = rand();
            printf("%d\t", d[i][j]);
        }
        printf("\n");
    }

    int max = d[0][0];

#pragma omp parallel for num_threads(10)
    for (int i = 0; i < size(d); i++) {
        for (int j = 0; j < size(d[0]); j++) {
#pragma omp critical
            {
                if (max < d[i][j]) {
                    max = d[i][j];
                }
            }
        }
    }

    int min = d[0][0];

#pragma omp parallel for num_threads(10)
    for (int i = 0; i < size(d); i++) {
        for (int j = 0; j < size(d[0]); j++) {
#pragma omp critical
            {
                if (min > d[i][j]) {
                    min = d[i][j];
                }
            }
        }
    }

    printf("max is %d\n", max);
    printf("min is %d\n", min);

}