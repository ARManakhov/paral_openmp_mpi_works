/*
 * Написать программу, печатающую номер процесса и общее количество процессов в коммуникаторе MPI_COMM_WORLD.
 */

#include <stdint.h>
#include <stdio.h>
#include "mpi.h"

using namespace std;

int main(int* argc, char** argv) {
    int numtasks, rank;
    MPI_Init(argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    printf("Hello world from process %d, num of processes : %d\n", rank, numtasks);

    MPI_Finalize();
}