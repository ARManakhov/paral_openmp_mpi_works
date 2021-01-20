/*
 * Модифицируйте задачу 1 так, что бы потоки распечатывали свои идентификаторы в обратном порядке. Существует как
 * минимум 5 способов решения. Постарайтесь найти как можно больше.
 */
#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
    omp_set_num_threads(8);
    printf("method 1\n");
#pragma omp parallel
    {
        //Sleep(100 * (omp_get_num_threads() - omp_get_thread_num()));
        printf("total threads num : %d current thread num : %d Hello World!\n", omp_get_num_threads(),omp_get_thread_num());
    }

    omp_set_num_threads(8);
    printf("method 2\n");
    int i = 8-1;
#pragma omp parallel
    {
        for (;;) {
            if (i == omp_get_thread_num()) {
#pragma omp critical
                {
                    i--;
                    printf("total threads num : %d current thread num : %d Hello World!\n", omp_get_num_threads(), omp_get_thread_num());
                }
                break;
            }
        }
    }

}