#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    long num_points = 1000000;
    long points_in_circle = 0;

    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        unsigned int seed = omp_get_thread_num();
        #pragma omp for reduction(+:points_in_circle)
        for (long i = 0; i < num_points; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;
            if (x * x + y * y <= 1.0) {
                points_in_circle++;
            }
        }
    }

    double end_time = omp_get_wtime();
    double pi = 4.0 * points_in_circle / num_points;

    printf("Estimated Pi: %f\n", pi);
    printf("Time taken: %f seconds\n", end_time - start_time);

    return 0;
}
