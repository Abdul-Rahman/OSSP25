/* Here's a complete C program implementing the Bounded Buffer Problem
using POSIX threads and semaphores. The program creates a producer
and consumer that share a bounded buffer. It synchronizes them using
semaphores to prevent race conditions. The expected output will show
how items are produced and consumed in order.
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Number of buffers
#define NUM_ITEMS 10   // Number of items to produce/consume

int buffer[BUFFER_SIZE]; // Shared buffer
int in = 0, out = 0;     // Buffer index pointers

sem_t mutex;  // Controls access to the buffer (Binary Semaphore)
sem_t empty;  // Counts empty slots in the buffer
sem_t full;   // Counts full slots in the buffer

// Producer function
void *producer(void *arg) {
    for (int i = 1; i <= NUM_ITEMS; i++) {
        sleep(rand() % 2); // Simulate production time
        sem_wait(&empty);  // Wait if buffer is full
        sem_wait(&mutex);  // Lock buffer access
        
        // Critical Section: Add item to buffer
        buffer[in] = i;
        printf("Producer produced: %d\n", i);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex); // Unlock buffer
        sem_post(&full);  // Signal that buffer has an item
    }
    return NULL;
}

// Consumer function
void *consumer(void *arg) {
    for (int i = 1; i <= NUM_ITEMS; i++) {
        sem_wait(&full);  // Wait if buffer is empty
        sem_wait(&mutex); // Lock buffer access

        // Critical Section: Remove item from buffer
        int item = buffer[out];
        printf("\tConsumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex); // Unlock buffer
        sem_post(&empty); // Signal that buffer has space
        sleep(rand() % 2); // Simulate consumption time
    }
    return NULL;
}

int main() {
    pthread_t producerThread, consumerThread;
    
    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    // Create producer and consumer threads
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}


/*
Output:

localhost:/home/alphapeeler/OsSp25/week10 # gcc ex03_bounded_buffer_prob.c -o ex03_bounded_buffer_prob.o
localhost:/home/alphapeeler/OsSp25/week10 # ./ex03_bounded_buffer_prob.o 
Producer produced: 1
Producer produced: 2
        Consumer consumed: 1
Producer produced: 3
        Consumer consumed: 2
Producer produced: 4
        Consumer consumed: 3
        Consumer consumed: 4
Producer produced: 5
Producer produced: 6
        Consumer consumed: 5
Producer produced: 7
Producer produced: 8
Producer produced: 9
        Consumer consumed: 6
        Consumer consumed: 7
        Consumer consumed: 8
        Consumer consumed: 9
Producer produced: 10
        Consumer consumed: 10
localhost:/home/alphapeeler/OsSp25/week10 # 


Explanation:
1.The producer generates items and places them into the buffer.
2. The consumer removes items from the buffer and processes them.
3. Semaphores ensure:
    * Mutual exclusion (mutex).
    * Prevent overfilling (empty).
    * Prevent underflow (full).
This implementation guarantees correct synchronization between producer and consumer in a multi-threaded environment. 
*/