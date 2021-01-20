/*
 * Написать программу, в которой объявить и присвоить начальные значения элементам двумерного массива d[6][8], для
 * инициализации значений использовать генератор случайных чисел. Используя  конструкцию  директивы sections...section
 * определить три секции для выполнения следующих операций:
 * - первая секция выполняет вычисление среднего арифметического значенияэлементов двумерного массива,
 * - втораясекция выполняет вычисление минимального и максимального значений элементов двумерного массива,
 * - третья секция выполняет вычисление количества элементов массива, числовые значения которых кратны 3.
 * В каждой секции определить и выдать на экран номер исполняющей нитии результат выполнения вычислений.
 */

#include <omp.h>
#include <iterator>

int main()
{

    int d[6][8];
    for (int i = 0; i < std::size(d); i++) {
        for (int j = 0; j < std::size(d[0]); j++) {
            d[i][j] = rand();
            printf("%d \t", d[i][j]);
        }
        printf("\n");
    }
    omp_set_num_threads(4);
#pragma omp parallel sections
    {
#pragma omp section
        {
            long sum = 0;
            for (int i = 0; i < std::size(d); i++) {
                for (int j = 0; j < std::size(d[0]); j++) {
                    sum += d[i][j];
                }
            }
            printf("thread num %d middle is %d\n", omp_get_thread_num(), sum / (std::size(d) + std::size(d[0])));
        }
#pragma omp section
        {
            long min = d[0][0];
            long max = d[0][0];
            for (int i = 0; i < std::size(d); i++) {
                for (int j = 0; j < std::size(d[0]); j++) {
                    if (min > d[i][j]) {
                        min = d[i][j];
                    }
                    if (max < d[i][j]) {
                        max = d[i][j];
                    }
                }
            }
            printf("thread num %d min is %d max is %d\n", omp_get_thread_num(), min, max);
        }
#pragma omp section
        {
            long counter = 0;
            for (int i = 0; i < std::size(d); i++) {
                for (int j = 0; j < std::size(d[0]); j++) {
                    if (d[i][j] % 3 == 0) {
                        counter++;
                    }
                }
            }
            printf("thread num %d count is %d\n", omp_get_thread_num(), counter);
        }
    }
}