/*
 *Используя блокирующую операцию передачи сообщений (MPI_Send и MPI_Recv) выполнить пересылку данных одномерного массива,
 * из процесса с номером 1 на остальные процессы группы.На процессах получателях до выставления функции приема (MPI_Recv)
 * определить количество принятых данных (MPI_Probe). Выделить память под размер приемного буфера, после чего вызвать
 * функцию MPI_Recv. Полученное сообщение выдать на экран.
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

        int a[10] = { 0 };

        for (int i = 0; i < size(a); i++) {
            a[i] = rand();
            printf("%d\t", a[i]);
        }
        printf("\n");
        for (int i=1; i < numtasks; i++)
            MPI_Send(a, size(a), MPI_INT, i, 0, MPI_COMM_WORLD);
    }
    else {

        MPI_Status status;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);

        int a_size;

        MPI_Get_count(&status, MPI_INT, &a_size);

        int * a = new int [a_size];

        MPI_Recv(a, a_size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("recieved array :\n");
        for (int i = 0; i < a_size; i++) {
            printf("%d\t", a[i]);
        }
        printf("\n");
    }
    MPI_Finalize();
}