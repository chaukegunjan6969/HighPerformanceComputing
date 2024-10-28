#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Define the size of the array n
    int n = 8;  // Array size
    int A[8] = {1, 2, 3, 4, 5, 6, 7, 8};  // Example array

    // Each process will calculate the sum of half of the array
    int local_sum = 0;
    int half = n / 2;

    // Process 0 computes the sum of the first half
    if (world_rank == 0) {
        for (int i = 0; i < half; i++) {
            local_sum += A[i];
        }
        printf("Process 0 partial sum: %d\n", local_sum);
    }
    // Process 1 computes the sum of the second half
    else if (world_rank == 1) {
        for (int i = half; i < n; i++) {
            local_sum += A[i];
        }
        printf("Process 1 partial sum: %d\n", local_sum);
    }

    // Gather and add the sums from both processes
    int total_sum = 0;
    if (world_rank == 0) {
        int other_sum = 0;
        MPI_Recv(&other_sum, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        total_sum = local_sum + other_sum;
        printf("Final sum calculated by Process 0: %d\n", total_sum);
    } else if (world_rank == 1) {
        MPI_Send(&local_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}

//mpirun -np 4 ./c
