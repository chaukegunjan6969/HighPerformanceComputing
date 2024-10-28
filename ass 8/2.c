#include <mpi.h>
#include <stdio.h>
#include <string.h>  

int main(int argc, char **argv)
{
    int rank, size;
    char send_data[100];  
    char recv_data[100];  
    int dest, source;

   
    MPI_Init(&argc, &argv);


    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    dest = (rank + 1) % size;             // nExt process (Jisko Send Karrha hu)
    source = (rank - 1 + size) % size;    // prev Process (Jisse bhej raha hu)      (MODULUS To point last process to first)


    // Sprintf Simiar to printf par stores string instead of printing
    sprintf(send_data, "Hello %d", dest);  

    

    MPI_Send(send_data, strlen(send_data) + 1, MPI_CHAR, dest, 0, MPI_COMM_WORLD);


    MPI_Recv(recv_data, 100, MPI_CHAR, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);



    printf("Process %d sent '%s' to process %d and received '%s' from process %d\n", 
           rank, send_data, dest, recv_data, source);



    MPI_Finalize();
    return 0;
}

// mpirun -np 4 ./b
