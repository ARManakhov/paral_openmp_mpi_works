/*
 * Написать программу, в которой объявить и присвоить начальные значения целочисленным массивам a[10] и b[10]. Используя
 * конструкцию parallel for и reduction вычислить средние арифметические значения элементов массивов a и b,сравнить
 * полученные значения, результат выдать на экран.
 */

#include <iostream>
#include <omp.h>

int main()
{
    int a[10] = { 0 };
    int b[10] = { 0 };

    int sumA = 0;
    int sumB = 0;

    printf("i\ta\tb\n");
    for (int i = 0; i < 10; i++) {
        a[i] = rand();
        b[i] = rand();
        printf("%d\t%d\t%d\n", i, a[i], b[i]);
    }

    omp_set_num_threads(2);
#pragma omp parallel for reduction(+ : sumA) reduction(+ : sumB)
    for (int i = 0; i < 10;i++) {
        sumA += a[i];
        sumB += b[i];
    }
    printf("mid a = %d, mid b = %d", sumA / 10, sumB / 10);
}