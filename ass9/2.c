#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int n = 4;  // Size of matrices
    int A[4][4] = { 
        {1, 2, 3, 4}, 
        {5, 6, 7, 8}, 
        {9, 10, 11, 12}, 
        {13, 14, 15, 16} 
    };
    int B[4][4] = {
        {1, 2, 3, 4}, 
        {5, 6, 7, 8}, 
        {9, 10, 11, 12}, 
        {13, 14, 15, 16}
    };

    int local_rows = n / world_size;  // Number of rows handled by each process
    int local_A[local_rows][n];
    int local_B[n][n];
    int local_C[local_rows][n];

    // Scatter rows of the matrix A to each process
    MPI_Scatter(A, local_rows * n, MPI_INT, local_A, local_rows * n, MPI_INT, 0, MPI_COMM_WORLD);

    // Broadcast matrix B to all processes
    MPI_Bcast(B, n * n, MPI_INT, 0, MPI_COMM_WORLD);

    // Perform local matrix multiplication
    for (int i = 0; i < local_rows; i++) {
        for (int j = 0; j < n; j++) {
            local_C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                local_C[i][j] += local_A[i][k] * B[k][j];
            }
        }
    }

    // Gather the local matrices from all processes
    int C[n][n];
    MPI_Gather(local_C, local_rows * n, MPI_INT, C, local_rows * n, MPI_INT, 0, MPI_COMM_WORLD);

    // Process 0 prints the result matrix C
    if (world_rank == 0) {
        printf("Resulting matrix C:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", C[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}

//mpirun -np 4 ./b
