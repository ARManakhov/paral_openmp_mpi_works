/*
 * Написать параллельную программу возведения числа 210 в квадрат без операции умножения. Пояснение: Квадрат натурального
 * числа N равен сумме первых N нечетных чисел. Например, 32 = 9  это  1 + 3 + 5 = 9; 52 = 25 это 1 + 3 + 5 + 7 + 9 = 25;
 */

#include <iostream>
#include <omp.h>

using namespace std;
int main()
{
    int n = 210;
    int r = 0;

    int j = 1;

#pragma omp parallel for num_threads(10)
    for (int i = 0; i < 210; i++) {
#pragma omp atomic
        r += j;
#pragma omp atomic
        j += 2;
    }
    cout << r;
}
