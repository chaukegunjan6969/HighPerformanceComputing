#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int n = 4;  // Size of matrix and vector
    int A[4][4] = { 
        {1, 2, 3, 4}, 
        {5, 6, 7, 8}, 
        {9, 10, 11, 12}, 
        {13, 14, 15, 16} 
    };
    int x[4] = {1, 1, 1, 1};  // Vector
    int local_rows = n / world_size;  // Number of rows handled by each process
    int local_result[local_rows];

    // Scatter rows of the matrix to each process
    int local_A[local_rows][n];
    MPI_Scatter(A, local_rows * n, MPI_INT, local_A, local_rows * n, MPI_INT, 0, MPI_COMM_WORLD);

    // Broadcast the vector to all processes
    MPI_Bcast(x, n, MPI_INT, 0, MPI_COMM_WORLD);

    // Compute the local result for the portion of the matrix
    for (int i = 0; i < local_rows; i++) {
        local_result[i] = 0;
        for (int j = 0; j < n; j++) {
            local_result[i] += local_A[i][j] * x[j];
        }
    }

    // Gather the results from all processes
    int final_result[n];
    MPI_Gather(local_result, local_rows, MPI_INT, final_result, local_rows, MPI_INT, 0, MPI_COMM_WORLD);

    // Process 0 prints the result
    if (world_rank == 0) {
        printf("Resulting vector: \n");
        for (int i = 0; i < n; i++) {
            printf("%d\n", final_result[i]);
        }
    }

    MPI_Finalize();
    return 0;
}

// mpirun -np 4 ./a
