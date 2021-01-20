/*
 * Написать программу, вычисляющую элементы вектора z по формуле zi = A * x[i] + B * y[j]. Векторы х, у задаются на
 * нулевом процессе и равными блоками пересылаютс яостальным процессам, A, B -заданные числа. Пересылка данных,
 * осуществляется функцией MPI_Send. Все процессы по формуле вычисляют свои элементы массива z.Каждый процесс отправляет
 * на нулевой процесс подсчитанные элементы.
 */
#include <stdint.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "mpi.h"

using namespace std;

int main(int* argc, char** argv) {
    int numtasks, rank;
    MPI_Init(argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);


    if (rank == 0) {

        printf("vector x :\n");
        int x[10] = { 0 };

        for (int i = 0; i < size(x); i++) {
            x[i] = rand();
            printf("%d\t", x[i]);
        }
        printf("\n");

        printf("vector y :\n");
        int y[10] = { 0 };

        for (int i = 0; i < size(y); i++) {
            y[i] = rand();
            printf("%d\t", y[i]);
        }
        printf("\n");

        int a = 10;

        printf("argument a = %d\t", a);

        int b = 5;

        printf("argument b = %d\n", b);

        if (size(y) != size(x))
        {
            printf("vector sizes not equal. exiting");
            return 0;
        }

        int z[size(x)];

        printf("\n");

        int t_size = size(x) / (numtasks - 1) + 1;

        printf("%d", t_size);

        for (int i = 1; i < numtasks; i++)
        {
            int data_size = 0;
            if (i + 1 == numtasks)
                data_size = size(x) % t_size;
            else
                data_size = t_size;
            MPI_Send(&data_size, 1, MPI_INT, i, 2, MPI_COMM_WORLD);

            int c_t_size = t_size * i > size(x) ? size(x) : t_size * i;

            for (size_t j = t_size * (i-1); j < c_t_size; j++)
            {
                int data_send_array[5]; // {i,x,y,a,b}

                data_send_array[0] = j;
                data_send_array[1] = x[j];
                data_send_array[2] = y[j];
                data_send_array[3] = a;
                data_send_array[4] = b;


                MPI_Send(data_send_array, size(data_send_array), MPI_INT, i, 0, MPI_COMM_WORLD);
            }

            MPI_Send(0, 0, MPI_INT, i, 1, MPI_COMM_WORLD);
        }

        for (int i = 1; i < numtasks; i++)
        {
            int c_t_size = t_size * i > size(x) ? size(x) : t_size * i;

            for (size_t j = t_size * (i - 1); j < c_t_size; j++)
            {
                int data_recieve_array[2]; //{1,z}
                MPI_Recv(data_recieve_array, 2, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                z[data_recieve_array[0]] = data_recieve_array[1];
            }
        }

        printf("vector z :\n");

        for (size_t i = 0; i < size(z); i++)
        {
            printf("%d\t", z[i]);
        }

    } else {

        int** data;
        int data_iterator = 0;

        int size;
        MPI_Recv(&size, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        data = new int* [size];
        for (;;) {
            MPI_Status status;

            int flag_end;

            MPI_Iprobe(0, 1, MPI_COMM_WORLD, &flag_end, &status);

            if (flag_end)
            {
                MPI_Recv(0,0, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                break;
            }

            int flag_data;

            MPI_Iprobe(0, 0, MPI_COMM_WORLD, &flag_data, &status);

            if (flag_data) {
                int data_size;
                MPI_Get_count(&status, MPI_INT, &data_size);

                int* data_recieve_array = new int[data_size];
                MPI_Recv(data_recieve_array, data_size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                data[data_iterator++] = data_recieve_array;
            }

        }

        for (int i = 0; i < data_iterator; i++) {
            int data_send_array[2] = { data[i][0], data[i][1] * data[i][3] + data[i][2] * data[i][4] };// {i.z}
            // printf("%d\t%d\t%d\n", data_send_array[0], data_send_array[1],rank);
            MPI_Send(data_send_array, 2, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
}