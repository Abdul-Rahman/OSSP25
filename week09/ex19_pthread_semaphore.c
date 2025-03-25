//Limiting Concurrent Access - Limit the number of threads accessing a resource simultaneously.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_THREADS 3  // Maximum number of threads allowed concurrently
#define TOTAL_THREADS 6  // Total number of threads to create

sem_t sem;  // Semaphore declaration

void* thread_func(void* arg) {
    sem_wait(&sem); // Acquire semaphore (decrease count)
    
    printf("Thread %ld accessing resource\n", (long)arg);
    sleep(1); // Simulating work by sleeping for 1 second
    
    sem_post(&sem); // Release semaphore (increase count)
    
    return NULL;
}

int main() {
    sem_init(&sem, 0, MAX_THREADS); // Initialize semaphore with max concurrent threads
    
    pthread_t threads[TOTAL_THREADS];

    // Create threads
    for (long i = 0; i < TOTAL_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_func, (void*)i);
    }

    // Wait for all threads to complete
    for (int i = 0; i < TOTAL_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&sem); // Cleanup semaphore
    
    return 0;
}

/*
localhost:/home/alphapeeler/OsSp25/week09 # gcc ex19_pthread_semaphore.c -o ex19_pthread_semaphore.o -lpthread
localhost:/home/alphapeeler/OsSp25/week09 # ./ex19_pthread_semaphore.o 
Thread 0 accessing resource
Thread 2 accessing resource
Thread 1 accessing resource
Thread 3 accessing resource
Thread 4 accessing resource
Thread 5 accessing resource
localhost:/home/alphapeeler/OsSp25/week09 # 
*/

/*
The first 3 threads (0, 1, 2) start execution.
After sleep(1), they complete, and then the next batch (3, 4, 5) runs.
This ensures that only MAX_THREADS = 3 threads are working at the same time.
*/