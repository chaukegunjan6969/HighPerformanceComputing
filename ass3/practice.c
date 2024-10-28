#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    int n = 1000000; 
    int *arr = (int *)malloc(n * sizeof(int));
    long long seq_sum = 0, omp_sum = 0;
    double seq_time, omp_time;
    
    
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    
    clock_t start_seq = clock();
    for (int i = 0; i < n; i++) {
        seq_sum += arr[i];
    }
    clock_t end_seq = clock();
    seq_time = (double)(end_seq - start_seq) / CLOCKS_PER_SEC;

   
    double start_omp = omp_get_wtime();
    #pragma omp parallel for reduction(+:omp_sum)
    for (int i = 0; i < n; i++) {
        omp_sum += arr[i];
    }
    double end_omp = omp_get_wtime();
    omp_time = end_omp - start_omp;

    
    printf(" Time taken: %f seconds\n",  seq_time);
    printf("Time taken: %f seconds\n",  omp_time);
    printf("Speed Up: %f\n", (seq_time)/(omp_time));
    free(arr);

    return 0;
}
