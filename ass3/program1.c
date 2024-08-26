#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Comparator function for ascending order
int compare_asc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Comparator function for descending order
int compare_desc(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

// Function to find the minimum scalar product of two vectors
int min_scalar_product(int *vector1, int *vector2, int n) {
    // Sort vector1 in ascending order
    qsort(vector1, n, sizeof(int), compare_asc);
    // Sort vector2 in descending order
    qsort(vector2, n, sizeof(int), compare_desc);

    int min_product = 0;

    #pragma omp parallel for reduction(+:min_product)
    for (int i = 0; i < n; i++) {
        min_product += vector1[i] * vector2[i];
    }

    return min_product;
}

int main() {
    int n = 1000000; // Size of the vectors

    // Allocate memory for the vectors
    int *vector1 = (int *)malloc(n * sizeof(int));
    int *vector2 = (int *)malloc(n * sizeof(int));

    // Initialize the vectors with random values
    for (int i = 0; i < n; i++) {
        vector1[i] = rand() % 1000;
        vector2[i] = rand() % 1000;
    }

    double start_time = omp_get_wtime();

    int result = min_scalar_product(vector1, vector2, n);

    double end_time = omp_get_wtime();

    printf("Minimum Scalar Product: %d\n", result);
    printf("Time taken: %f seconds\n", end_time - start_time);

    // Free allocated memory
    free(vector1);
    free(vector2);

    return 0;
}
