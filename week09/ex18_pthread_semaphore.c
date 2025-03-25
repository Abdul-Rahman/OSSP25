//Ordering Thread Execution - Ensure one thread executes before another.
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Declare a semaphore
sem_t sem;
int shared_data = 0;
void* thread1(void* arg) {
    printf("Thread1\n");
    shared_data--;
    printf("shared_data = %d\n", shared_data);
    sem_post(&sem); //Signal (increment semaphore)
    return NULL;
}
void* thread2(void* arg) {
    sem_wait(&sem); //wait for thread 1 (decrement semaphore)
    printf("Thread2\n");
    shared_data++;
    printf("shared_data = %d\n", shared_data);
    return NULL;
}

int main() {
    // Initialize semaphore to 0
    sem_init(&sem, 0, 0); //pshared = 0 for thread synchronization
    pthread_t t1, t2;

    // Create two threads
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    // Wait for both threads to complete
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy semaphore
    sem_destroy(&sem);

    return 0;
}

/*
localhost:/home/alphapeeler/OsSp25/week09 # gcc ex18_pthread_semaphore.c -o ex18_pthread_semaphore.o -lpthread
localhost:/home/alphapeeler/OsSp25/week09 # ./ex18_pthread_semaphore.o 
Thread1
shared_data = -1
Thread2
shared_data = 0
localhost:/home/alphapeeler/OsSp25/week09 # 
*/