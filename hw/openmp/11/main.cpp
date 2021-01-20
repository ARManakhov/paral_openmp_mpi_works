/*
 * Написать программу, в которой, объявить и заполнить случайными значениями массив целых чисел. Используя возможности
 * OpenMP найти максимальное числовое значение элементов массива, кратное 7. Длину массива и количество потоков
 * определить самостоятельно. Результат выдать на экран. Для синхронизации числовых значений максимума используется
 * механизм критических секций.
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

    int maxElem = a[0];

#pragma omp parallel for  num_threads(10)
    for (int i = 0; i < size(a); i++) {
        if (a[i] % 7 == 0) {
#pragma omp critical
            if (maxElem < a[i]) {
                maxElem = a[i];
            }
        }
    }

    printf("max elem : %d", maxElem);



}