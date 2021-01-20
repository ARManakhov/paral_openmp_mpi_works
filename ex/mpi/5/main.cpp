/*
 * Написать программу вычисления скалярного произведения двух векторов. Для распределения элементов вектора x по
 * процессам использовать функцию MPI_Scatter. Для получения итоговой суммы на нулевом процессе использовать функцию
 * MPI_Reduce с операцией MPI_Sum.
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

const int root = 0;

int main(int argc, char **argv) {
    int i;
    int n = 4;
    int rank;
    int size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int a[n];
    int b[n];

    int send_arr[n * 2];

    if (rank == root) {
        for (i = 0; i < n; i++) {
            a[i] = i * 2;
            b[i] = i * 3;
            printf("i = %d, a = %d, b=%d\n", i, a[i], b[i]);
        }
        for (int j = 0; j < n; ++j) {
            send_arr[j * 2] = a[j];
            send_arr[j * 2 + 1] = b[j];
        }
    }

    int m = n / size;
    int recv_arr[m * 2];

    MPI_Scatter(send_arr, m * 2, MPI_INT, recv_arr, m * 2, MPI_INT, root, MPI_COMM_WORLD);

    int scolar_comp_part = 0;
    for (i = 0; i < m; i++) {
        scolar_comp_part += recv_arr[i * 2] * recv_arr[i * 2 + 1];
    }

    int sum = 0;
    MPI_Reduce(&scolar_comp_part, &sum, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);

    if (rank == root) {
        printf("scolar composition = %d\n", sum);
    }

    MPI_Finalize();
    return 0;
}