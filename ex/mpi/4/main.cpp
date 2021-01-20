/*
 * Написать программу вычисления нормы ||𝑥||=|𝑥1|+|𝑥2|+⋯+|𝑥𝑛| вектора 𝑥. Для распределения элементов вектора 𝑥 по
 * процессам использовать функцию MPI_Scatter. Для получения итоговой суммы на нулевом процессе использовать функцию
 * MPI_Reduce с операцией MPI_Sum.
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

const int root = 0;

int main(int argc, char **argv) {
    int i;
    int n = 16;
    int rank;
    int size;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int x[n];

    if (rank == root) {
        printf("root = %i x=\n", rank);
        for (i = 0; i < n; i++) {
            x[i] = i + 1;
        }
    }

    int m = n / size;
    int y[m];

    MPI_Scatter(x, m, MPI_INT, y, m, MPI_INT, root, MPI_COMM_WORLD);

    int sum_part = 0;
    for (i = 0; i < m; i++) {
        sum_part += abs(y[i]);
    }
    printf("\n");

    int sum = 0;
    MPI_Reduce(&sum_part, &sum, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);

    if (rank == root) {
        printf("sum= %d\n", rank, sum);
    }

    MPI_Finalize();
    return 0;
}