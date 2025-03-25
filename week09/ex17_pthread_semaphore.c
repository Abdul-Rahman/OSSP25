#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Declare a semaphore
sem_t sem;
int shared_data = 0;

void* thread_func(void* arg) {
    // Wait (decrement semaphore)
    sem_wait(&sem);
    printf("Thread %ld is in the critical section\n", pthread_self());
    shared_data++;
    printf("shared_data = %d\n", shared_data);
    sleep(1); // Simulate some work
    printf("Thread %ld is leaving the critical section\n", pthread_self());
    // Signal (increment semaphore)
    sem_post(&sem);
    return NULL;
}

int main() {
    // Initialize semaphore to 1 (acts like a mutex)
    sem_init(&sem, 0, 1); //pshared = 0 for thread synchronization

    pthread_t t1, t2;

    // Create two threads
    pthread_create(&t1, NULL, thread_func, NULL);
    pthread_create(&t2, NULL, thread_func, NULL);

    // Wait for both threads to complete
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy semaphore
    sem_destroy(&sem);

    return 0;
}

/*
localhost:/home/alphapeeler/OsSp25/week09 # gcc ex17_pthread_semaphore.c -o ex17_pthread_semaphore.o -lpthread
localhost:/home/alphapeeler/OsSp25/week09 # ./ex17_pthread_semaphore.o 
Thread 139755394164416 is in the critical section
shared_data = 1
Thread 139755394164416 is leaving the critical section
Thread 139755402557120 is in the critical section
shared_data = 2
Thread 139755402557120 is leaving the critical section
localhost:/home/alphapeeler/OsSp25/week09 # 
*/

/*
Explanation of the Code
1. Semaphore Initialization (sem_init)

A semaphore sem is initialized with a value of 1, meaning only one thread can enter the critical section at a time.

2. Thread Creation (pthread_create)

Two threads (t1 and t2) are created and both execute the thread_func.

3. Semaphore Wait (sem_wait)

When a thread enters thread_func, it calls sem_wait(&sem), which decrements the semaphore.

If the semaphore is already 0 (another thread is in the critical section), the thread will wait until it can proceed.

4. Critical Section Execution

The thread prints a message indicating it has entered the critical section.

It sleeps for 1 second to simulate processing time.

It prints another message before leaving.

5. Semaphore Signal (sem_post)

The thread calls sem_post(&sem), incrementing the semaphore and allowing another thread to proceed.

6. Thread Synchronization (pthread_join)

The main function waits for both threads to complete before destroying the semaphore.

7. Semaphore Cleanup (sem_destroy)

The semaphore is destroyed once both threads have finished.

*/