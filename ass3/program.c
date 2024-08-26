#include <stdio.h>
#include <omp.h>

void vector_scalar_addition_schedule(int *vector, int n, int scalar) {
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < n; i++) {
        vector[i] += scalar;
    }
}

void vector_scalar_addition_nowait(int *vector, int n, int scalar) {
    #pragma omp parallel
    {
        #pragma omp for nowait
        for (int i = 0; i < n; i++) {
            vector[i] += scalar;
        }
    }
}

void vector_scalar_addition_reduction(int *vector, int n, int scalar) {
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        vector[i] += scalar;
        sum += vector[i];
    }
    printf("Sum of elements after addition: %d\n", sum);
}

void vector_scalar_addition_ordered(int *vector, int n, int scalar) {
    #pragma omp parallel for ordered
    for (int i = 0; i < n; i++) {
        #pragma omp ordered
        {
            vector[i] += scalar;
        }
    }
}

void vector_scalar_addition_collapse(int *matrix, int rows, int cols, int scalar) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i * cols + j] += scalar;
        }
    }
}

int main() {
    int n = 1000000; // Size of the vector
    int scalar = 5;
    int vector[n];
    int rows = 1000, cols = 1000;
    int matrix[rows * cols];

    // Initialize the vector
    for (int i = 0; i < n; i++) {
        vector[i] = i;
    }

    // Initialize the matrix
    for (int i = 0; i < rows * cols; i++) {
        matrix[i] = i;
    }

    double start_time, end_time;

    // Schedule clause
    start_time = omp_get_wtime();
    vector_scalar_addition_schedule(vector, n, scalar);
    end_time = omp_get_wtime();
    printf("Schedule clause time taken: %f seconds\n", end_time - start_time);

    // Nowait clause
    start_time = omp_get_wtime();
    vector_scalar_addition_nowait(vector, n, scalar);
    end_time = omp_get_wtime();
    printf("Nowait clause time taken: %f seconds\n", end_time - start_time);

    // Reduction clause
    start_time = omp_get_wtime();
    vector_scalar_addition_reduction(vector, n, scalar);
    end_time = omp_get_wtime();
    printf("Reduction clause time taken: %f seconds\n", end_time - start_time);

    // Ordered clause
    start_time = omp_get_wtime();
    vector_scalar_addition_ordered(vector, n, scalar);
    end_time = omp_get_wtime();
    printf("Ordered clause time taken: %f seconds\n", end_time - start_time);

    // Collapse clause
    start_time = omp_get_wtime();
    vector_scalar_addition_collapse(matrix, rows, cols, scalar);
    end_time = omp_get_wtime();
    printf("Collapse clause time taken: %f seconds\n", end_time - start_time);

    return 0;
}
