#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the total number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Print the rank and communicator group
    printf("Process %d of %d in communicator MPI_COMM_WORLD\n", world_rank, world_size);

    // Finalize the MPI environment
    MPI_Finalize();
}

 // mpirun -np 4 ./b
