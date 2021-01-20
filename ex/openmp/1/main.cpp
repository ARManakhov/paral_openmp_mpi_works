/*
 * Написать программу где каждый поток печатает свой идентификатор, количество потоков всего и строчку «Hello World».
 * Запустить программу с 8 потоками. Всегда ли вывод идентичен? Почему?
 */

#include <iostream>
#include <omp.h>
#include <sstream>

using namespace std;

int main()
{
    omp_set_num_threads(8);
#pragma omp parallel
    {
        stringstream ss;
        ss << "total threads num : " << omp_get_num_threads() << " current thread num : " << omp_get_thread_num() << " Hello World!\n";
        cout << ss.str();
    }
}
