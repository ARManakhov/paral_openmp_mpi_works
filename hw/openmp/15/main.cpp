/*
 * Написать программу, в которой, используя возможности OpenMP найти все простые числа в заданном с клавиатуры диапазоне.
 * Количество потоков определить самостоятельно. Результат выдать на экран.
 */
#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
    cout << "write start of range!\n";
    int start = 0;
    cin >> start;
    cout << "write end of range!\n";
    int end;
    cin >> end;

    cout << "simple numbers : ";
#pragma omp parallel for num_threads(10)
    for (int i = start; i <= end; i++) {
        bool isSimple = true;
        for (int j = 2; j < i; j ++) {
            if (i % j == 0) {
                isSimple = false;
                break;
            }
        }
        if (isSimple){
            printf("\t%i",i);
        }
    }

}