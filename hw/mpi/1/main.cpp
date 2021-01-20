/*
 * Написать mpi программу, печатающую "Hello,World!". Запустить программу на 4 процессах.
 */
#include <stdint.h>
#include <stdio.h>
#include <cstdlib>
#include <mpi.h>

using namespace std;

int main(int* argc, char** argv) {
    int numtasks, rank;
    MPI_Init(argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

    printf("Hello, World!\n");

    MPI_Finalize();
}