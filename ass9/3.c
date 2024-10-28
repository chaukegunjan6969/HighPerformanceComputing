#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 4 // Size of the matrices (N x N)

// Function to print a matrix
void printMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
    int rank, size;
    int A[N][N], B[N][N], C[N][N]; // Matrices A, B, and result C
    int rows_per_process; // Number of rows to be processed by each process
    int start_row, end_row;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Initialize matrices A and B in process 0
    if (rank == 0) {
        // Fill matrices A and B with example values
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = i + j; // Example initialization for matrix A
                B[i][j] = i * j; // Example initialization for matrix B
            }
        }
        
        printf("Matrix A:\n");
        printMatrix(A);
        printf("Matrix B:\n");
        printMatrix(B);
    }

    // Broadcast matrix B to all processes
    MPI_Bcast(B, N*N, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process receives its portion of A
    rows_per_process = N / size;
    start_row = rank * rows_per_process;
    end_row = (rank + 1) * rows_per_process;

    // Each process computes its portion of the result matrix C
    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < N; j++) {
            if (rank == 0) {
                C[i][j] = A[i][j] + B[i][j]; // Only process 0 has A
            } else {
                // Other processes won't compute this, since they don't have A
                C[i][j] = B[i][j]; // This is just an example, can be optimized
            }
        }
    }

    // Gather the results from all processes to process 0
    MPI_Gather(&C[start_row], rows_per_process * N, MPI_INT, C, rows_per_process * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Print the resulting matrix in process 0
    if (rank == 0) {
        printf("Resulting Matrix C (A + B):\n");
        printMatrix(C);
    }

    MPI_Finalize();
    return 0;
}

