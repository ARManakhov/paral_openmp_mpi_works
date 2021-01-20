/*
 * Написать программу, в которой определить две параллельные области, выполнение которых зависит от условного оператора
 * #pragma omp parallel if(...), если заданное значение числа нитей больше 1, параллельная область выполняется,
 * иначе не выполняется. Число нитей перед первой областью задать равным 3, перед второй – равным 1. Внутри
 * параллельных областей определить количество нитей и номер каждой нити, результат выдать на экран. Убедиться
 * в правильности работы программы.
 */

#include <iostream>
#include <omp.h>
#include <sstream>

using namespace std;

int main()
{
    omp_set_num_threads(3);
#pragma omp parallel
    if(omp_get_num_threads() > 1)
    {
        stringstream ss;
        ss << "total threads num : " << omp_get_num_threads() << " current thread num : " << omp_get_thread_num() << "\n";
        cout << ss.str();
    }

    omp_set_num_threads(1);
#pragma omp parallel
    if (omp_get_num_threads() > 1)
    {
        stringstream ss;
        ss << "total threads num : " << omp_get_num_threads() << " current thread num : " << omp_get_thread_num() << "\n";
        cout << ss.str();
    }
}