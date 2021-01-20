/*
 * Написать программу, запустить ее на 2х процессах. На нулевом процессе задать массив а из 10 элементов, значения
 * сгенерировать случайным образом. Переслать этот массив целиком первому процессу с помощью функции MPI_Send.
 * Распечатать на первом процессе принятый массив.
 */
#include <stdint.h>
#include <stdio.h>
#include <cstdlib>
#include "mpi.h"

using namespace std;

int main(int* argc, char** argv) {
    int numtasks, rank;
    MPI_Init(argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    int a[10] = { 0 };

    if (rank == 0) {
        printf("new array :\n");
        for (int i = 0; i < 10; i++) {
            a[i] = rand();
            printf("%d\t", a[i]);
        }
        printf("\n");

        MPI_Send(a, 10, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else if (rank == 1) {

        MPI_Recv(a, 10, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("recieved array :\n");
        for (int i = 0; i < 10; i++) {
            printf("%d\t", a[i]);
        }
        printf("\n");
    }
    MPI_Finalize();
}