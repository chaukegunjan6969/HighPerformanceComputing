#include<stdio.h>
#include<omp.h>

int main(){

int n = 1000000;
int scalar = 5;
int vector[n];

for(int i = 0; i < n; i++)
{
   vector[i]=i;
}

 double start_time = omp_get_wtime();
 
 #pragma omp parallel for 
 for(int i = 0 ; i < n; i++)
{
  vector[i] += scalar;
}

double end_time = omp_get_wtime();
printf("Time Taken: %f seconds\n", end_time - start_time);

return 0;

}
