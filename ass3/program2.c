#include <omp.h>
#include <stdio.h>

#define VECTOR_SIZE 200

void scalar_add_static(double* vec, double scalar, int chunk_size) {
    #pragma omp parallel for schedule(static, chunk_size)
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vec[i] += scalar;
    }
}

void scalar_add_dynamic(double* vec, double scalar, int chunk_size) {
    #pragma omp parallel for schedule(dynamic, chunk_size)
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vec[i] += scalar;
    }
}

void scalar_add_nowait(double* vec, double scalar, int chunk_size) {
    #pragma omp parallel
    {
        #pragma omp for schedule(static, chunk_size) nowait
        for (int i = 0; i < VECTOR_SIZE; i++) {
            vec[i] += scalar;
        }
        // Some other parallel work can be done here without waiting for the for loop to finish
        #pragma omp for schedule(dynamic, chunk_size) nowait
        for (int i = 0; i < VECTOR_SIZE; i++) {
            vec[i] *= scalar;
        }
    }
}

int main() {
    double vector[VECTOR_SIZE];
    double scalar = 2.0;
    
    // Initialize vector
    for (int i = 0; i < VECTOR_SIZE; i++) {
        vector[i] = i * 1.0;
    }

    int chunk_sizes[] = {1, 10, 20, 50};
    int num_chunks = sizeof(chunk_sizes) / sizeof(chunk_sizes[0]);

    // Analyzing speedup with STATIC schedule
    for (int i = 0; i < num_chunks; i++) {
        double start_time = omp_get_wtime();
        scalar_add_static(vector, scalar, chunk_sizes[i]);
        double end_time = omp_get_wtime();
        printf("STATIC schedule, chunk size = %d, time taken = %f seconds\n", chunk_sizes[i], end_time - start_time);
    }

    // Analyzing speedup with DYNAMIC schedule
    for (int i = 0; i < num_chunks; i++) {
        double start_time = omp_get_wtime();
        scalar_add_dynamic(vector, scalar, chunk_sizes[i]);
        double end_time = omp_get_wtime();
        printf("DYNAMIC schedule, chunk size = %d, time taken = %f seconds\n", chunk_sizes[i], end_time - start_time);
    }

    // Demonstrating the use of nowait clause
    double start_time = omp_get_wtime();
    scalar_add_nowait(vector, scalar, 10);
    double end_time = omp_get_wtime();
    printf("NOWAIT clause, time taken = %f seconds\n", end_time - start_time);

    return 0;
}
