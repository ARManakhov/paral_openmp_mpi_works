/*
 * Написать программу, в которой объявить и присвоить начальные значения целочисленным переменным: a и b, определить две
 * параллельные области, первая – с числом нитей 2, вторая – с числом нитей 4. Для первой области переменные a и b
 * объявить защищенными, с режимом доступа  private и first private соответственно, внутри области определить номер нити
 * и выполнить увеличение значения переменных на это величину. Выдать на экран значения переменных до входа в
 * параллельную область, внутри параллельной области и после выхода из параллельной области. Для второй области
 * переменную a объявить общей, переменную b объявить защищенной, с режимом доступа private, определить номер нити
 * и выполнить уменьшение значения переменных на это величину. Выдать на экран значения переменных до входа в
 * параллельную область, внутри параллельной области и после выхода из параллельной области.
 */


#include <iostream>
#include <omp.h>
#include <sstream>

using namespace std;

int main()
{
    int a = 69;
    int b = 42;
    cout << "init values : a = " << a << " b = " << b <<"\n";
    cout << "range 0\n";
    omp_set_num_threads(2);
#pragma omp parallel private(a) firstprivate(b)
    {
        int a = 69;
        int thread_num = omp_get_thread_num();
        a += thread_num;
        b += thread_num;

        stringstream ss;
        ss << "in thread "<< thread_num << " values : a = " << a << "b = " << b << "\n";
        cout << ss.str();
    }
    cout << "range 1\n";
    omp_set_num_threads(4);
#pragma omp parallel shared(a) private(b)
    {
        b = 42;
        int thread_num = omp_get_thread_num();
        a -= thread_num;
        b -= thread_num;

        stringstream ss;
        ss << "in thread " << thread_num << " values : a = " << a << "b = " << b << "\n";
        cout<<ss.str();
    }
}
