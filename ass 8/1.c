#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int message;

    if (world_rank == 0) {
        // Process 0 attempts to receive a message from Process 1 first
        message = 100;
        MPI_Send(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent message %d to Process 1\n", message);
        
        // Process 0 attempts to send a message to Process 1
        
        message = 100;
        PI_Recv(&message, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 0 received message %d from Process 1\n", message);
    } 
    else if (world_rank == 1) {
        // Process 1 attempts to receive a message from Process 0 first
        message = 200;
        MPI_Send(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        printf("Process 1 sent message %d to Process 0\n", message);
        
        // Process 1 attempts to send a message to Process 0
        
        message = 200;
        MPI_Recv(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received message %d from Process 0\n", message);
        
    }

    MPI_Finalize();
    return 0;
}

