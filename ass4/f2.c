#include <stdio.h>
#include <omp.h>
#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0;

void produce(int item) {
    #pragma omp critical
    {
        buffer[count] = item;
        count++;
        printf("Produced: %d\n", item);
    }
}

int consume() {
    int item;
    #pragma omp critical
    {
        count--;
        item = buffer[count];
        printf("Consumed: %d\n", item);
    }
    return item;
}

int main() {
    int i;
    int n_items = 20; 

    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                
                for (i = 0; i < n_items; i++) {
                    while (count == BUFFER_SIZE);
                    produce(i);
                }
            }

            #pragma omp section
            {
                
                for (i = 0; i < n_items; i++) {
                    while (count == 0);  
                    consume();
                }
            }
        }
    }

    return 0;
}
