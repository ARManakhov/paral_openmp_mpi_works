/*
 * На нулевом процессе задан массив целых чисел, который является двоичным представлением десятичного числа. Написать
 * параллельную программу вычисления десятичного числа из заданного двоичного представления.
 * int a[30] = {1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1};
 * Число x может быть представлено в системе с основанием p, как x = an * pn + a(n - 1) * p(n - 1) + a1 * p1 + a0 * p0,
 * где an ... a0 -цифры в представлении данного числа.
 */
#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
    int a[30] = { 1,0,1,1,0,1,0,0,0,1,1,1,0,1,0,1,0,0,0,1,0,1,1,1,0,0,0,1,0,1 };
    int x = 0;
    int n = size(a);

#pragma omp parallel for num_threads(10)
    for (int i = 0; i < n; i++) {
        int b = a[i];
        if (b == 1){
            for (int j = 0; j < n - i - 1; j++) {
                b *= 2;
            }
        }
#pragma omp atomic
        x += b;
    }
    cout << x;

}