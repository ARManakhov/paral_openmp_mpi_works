/*
 * Написать программу, в которой объявить и присвоить начальные значения целочисленныммассивам a[10] и b[10], определить
 * параллельную область, количество нитей задать равным 2, выделить код для основной (номер 0) и нити с номером 1.
 * Основная нить должна выполнять поиск min значения элементов массива a, нить с номером 1 - поиск max значения элементов
 * массива b. Результат выдать на экран.
 */

#include <iostream>
#include <array>
#include <omp.h>

using namespace std;

int min(int arr[], int arr_size) {
    if (arr_size > 0) {
        int min = arr[0];
        for (int i = 0; i < arr_size; i++) {
            if (min > arr[i]) {
                min = arr[i];
            }
        }
        return min;
    }
    return 0;
}

int max(int arr[], int arr_size) {
    if (arr_size > 0) {
        int max = arr[0];
        for (int i = 0; i < arr_size; i++) {
            if (max < arr[i]) {
                max = arr[i];
            }
        }
        return max;
    }
    return 0;
}

int main()
{
    int a[10] = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int b[10] = { 1, 3, 5, 7, 9, 11, 13, 15, 17 , 19};

    omp_set_num_threads(2);
#pragma omp parallel
    switch (omp_get_thread_num()){
        case 0:
            printf("min of a is %d\n", min(a, size(a)));
            break;
        case 1:
            printf("max of b is %d\n", max(b, size(b)));
            break;
        default:
            printf("there is no code for thread %d\n", omp_get_thread_num());
    }

}
