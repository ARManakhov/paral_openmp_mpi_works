/*
 * Написать программу и запустить ее на p (= 2, 3, 4, 6, 8) процессах. На нулевом процессе объявить и задать массив из
 * 12 элементов. С помощью функции MPI_Send разослать блоки массива на остальные процессы. Размер блока массива
 * (12 / p) + 1. В результате на нулевом процессе должны быть элементы массива с 0 до 12 / p, на первом процессе с
 * 12 / p + 1 до 2 × ( 12 / p ), на 3-м процессес 2 × ( 12 / p ) + 1 до 3 × ( 12 / p ) и т.д. Вывести элементы массива
 * на экран на каждом процессе. Обратите внимание, что не на все процессы хватит элементов.
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

        printf("new array :\n");

        int a[12] = { 0 };

        for (int i = 0; i < size(a); i++) {
            a[i] = rand();
            printf("%d\t", a[i]);
        }
        printf("\n");
        for (int i = 1; i < numtasks; i++) {
            int arr_to_send_size = size(a) / numtasks + 1;
            int* arr_to_send = NULL;
            arr_to_send = new int[arr_to_send_size];

            for (int j = 0; j < arr_to_send_size; j++) {
                arr_to_send[j] = a[j + (i-1) * arr_to_send_size];

            }
            //printf("stock arr part : \n");
            MPI_Send(&arr_to_send_size, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            for (int j = 0; j < arr_to_send_size; j++) {
                int arr_elem = arr_to_send[j];
                MPI_Send(&arr_elem, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                //printf("%d\t", arr_elem);
            }
            //printf("\n");
        }

    }
    else {

        int a_size;
        MPI_Recv(&a_size,1,MPI_INT,0,0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        int* a = new int[a_size];

        for (int j = 0; j < a_size; j++) {
            int a_elem;
            MPI_Recv(&a_elem, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            a[j] = a_elem;
        }


        printf("recieved array :\n");
        for (int i = 0; i < a_size; i++) {
            printf("%d\t", a[i]);
        }
        printf("\n");
    }
    MPI_Finalize();
}
