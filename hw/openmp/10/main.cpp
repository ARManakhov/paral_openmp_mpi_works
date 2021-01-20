/*
 * Написать программу, в которой объявить и присвоить начальные значения массиву целых чисел a[30], для инициализации
 * значений использовать генератор случайных чисел. Используя конструкцию omp parallel for и omp atomic вычислить
 * количество элементов массива, числовые значения которых кратны 9. Количество нитей задать самостоятельно. Результат
 * выдать на экран.
 */
#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
    int a[30] = { 0 };

    for (int i = 0; i < size(a); i++) {
        a[i] = rand();
        printf("%d\t", a[i]);
    }

    printf("\n");

    int count = 0;

#pragma omp parallel for  num_threads(10)
    for (int i = 0; i < size(a); i++) {
        if (a[i] % 9 == 0) {
#pragma omp atomic
            count++;
        }
    }

    printf("count : %d", count);
}