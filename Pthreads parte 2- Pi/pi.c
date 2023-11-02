#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define n 100000
#define thread_count 25
double sum = 0;

void* Thread_sum(void* rank) {
    long my_rank = (long) rank;
    double factor;
    long long i;
    long long my_n = n/thread_count;
    long long my_first_i = my_n*my_rank;
    long long my_last_i = my_first_i + my_n;
    
    
    if (my_first_i % 2 == 0) {
        factor = 1.0;
    }
    else {
        factor = -1.0;
    }
    for (i = my_first_i; i < my_last_i; i++, factor = -factor) {
        sum += factor/(2*i+1);
    }
    return NULL;
}

int main()
{   
    printf("==Pi utilizando Pthreads (sem Mutex)==\n");
    pthread_t* thread_handles;
    thread_handles = malloc(thread_count * sizeof(pthread_t));

    for (long thread = 0; thread < thread_count; thread++) {
        pthread_create(&thread_handles[thread], NULL, Thread_sum, (void*) thread);
    }
    
    for (long thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }
    sum *= 4;
    printf("Resultado final: %f", sum);
}
