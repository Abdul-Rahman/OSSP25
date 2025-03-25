//Barrier Synchronization - Wait for all threads to reach a point before proceeding.
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 3

sem_t barrier;
int count = 0;
pthread_mutex_t mutex;

void* thread_func(void* arg) {
    printf("Thread %ld reached barrier\n", (long)arg);

    pthread_mutex_lock(&mutex);
    count++;
    if (count == NUM_THREADS) {
        for (int i = 0; i < NUM_THREADS; i++) {
            sem_post(&barrier); // Release all waiting threads
        }
    }
    pthread_mutex_unlock(&mutex);

    sem_wait(&barrier); // Wait for all threads to reach the barrier

    printf("Thread %ld passed barrier\n", (long)arg);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    sem_init(&barrier, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_func, (void*)i);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&barrier);
    pthread_mutex_destroy(&mutex);

    return 0;
}


/*
localhost:/home/alphapeeler/OsSp25/week09 # gcc ex20_pthread_semaphore.c -o ex20_pthread_semaphore.o -lpthread
localhost:/home/alphapeeler/OsSp25/week09 # ./ex20_pthread_semaphore.o 
Thread 0 reached barrier
Thread 0 passed barrier
Thread 2 reached barrier
Thread 2 passed barrier
Thread 1 reached barrier
Thread 1 passed barrier
localhost:/home/alphapeeler/OsSp25/week09 # 

Explanation of the Fixed Code
1. Each thread reaches the barrier and increments count.
2. When all NUM_THREADS have reached the barrier, sem_post is called NUM_THREADS times, 
releasing all waiting threads.
3. Each thread then calls sem_wait to wait until all other threads reach the barrier 
before continuing.
4. After passing the barrier, threads print the "passed barrier" message.
5. Finally, all resources (semaphore and mutex) are destroyed.
*/