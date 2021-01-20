/*
 * В массиве вещественных чисел вычислить минимальное значение и глобальный индекс минимального элемента. Использовать
 * функции MPI_Scatter и MPI_Reduce с операцией MPI_MINLOC.
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

const int root = 0;

int main(int argc, char **argv) {
    int i;
    int in_size = 16;
    int rank;
    int size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    float in[in_size];

    if (rank == root) {
        for (i = 0; i < in_size; i++) {
            in[i] = rand();
            printf("in[%d]= %f\n",i, in[i]);
        }
    }

    int m = in_size / size;
    float recv_data[m];

    MPI_Scatter(in, m, MPI_INT, recv_data, m, MPI_INT, root, MPI_COMM_WORLD);

    struct {
        float value;
        int   index;
    } local_min, global_min;

    local_min.value = recv_data[0];
    local_min.index = 0;
    for (i=1; i < m; i++){
        if (local_min.value > recv_data[i]) {
            local_min.value = recv_data[i];
            local_min.index = i;
        }
    }
    printf("rank %d, local_min = %f\n", rank, local_min.value);
    local_min.index = rank * in_size + local_min.index;

    MPI_Reduce(&local_min, &global_min, 1, MPI_FLOAT_INT, MPI_MINLOC, root, MPI_COMM_WORLD );

    if (rank == root) {
        printf("global min = %f, with index = %d, from %d\n", global_min.value, global_min.index % in_size, global_min.index / in_size);
    }
}