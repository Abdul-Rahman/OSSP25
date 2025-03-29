/* Here is the complete C implementation of the Readers-Writers Problem 
(First Variant: Readers Priority Approach) using semaphores. */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

// Declare semaphores
sem_t rw_mutex;   // Controls writer access
sem_t mutex;      // Protects read_count variable
int read_count = 0; // Number of active readers
int data = 0; // Shared data

// Reader function
void *reader(void *arg) {
    int id = *(int *)arg; // Get reader ID
    while (1) {
        // Entry Section
        sem_wait(&mutex); // Lock mutex before modifying read_count
        read_count++;
        if (read_count == 1) {
            sem_wait(&rw_mutex); // First reader locks writer
        }
        sem_post(&mutex); // Unlock mutex after modifying read_count

        // Reading Section
        printf("Reader %d is reading data: %d\n", id, data);
        sleep(1);  // Simulate reading time

        // Exit Section
        sem_wait(&mutex); // Lock mutex before modifying read_count
        read_count--;
        if (read_count == 0) {
            sem_post(&rw_mutex); // Last reader releases writer
        }
        sem_post(&mutex); // Unlock mutex after modifying read_count

        sleep(1); // Simulate delay before reading again
    }
}

// Writer function
void *writer(void *arg) {
    int id = *(int *)arg; // Get writer ID
    while (1) {
        sem_wait(&rw_mutex); // Lock access for writing

        // Writing Section
        data++; // Modify shared data
        printf("Writer %d is writing data: %d\n", id, data);
        sleep(1); // Simulate writing time

        sem_post(&rw_mutex); // Release access after writing

        sleep(2); // Simulate delay before writing again
    }
}

int main() {
    pthread_t r1, r2, w1; // Thread variables
    int id1 = 1, id2 = 2, id3 = 1;

    // Initialize semaphores
    sem_init(&rw_mutex, 0, 1); // Binary semaphore (1 means available)
    sem_init(&mutex, 0, 1);    // Binary semaphore for protecting read_count

    // Create threads
    pthread_create(&r1, NULL, reader, &id1);
    pthread_create(&r2, NULL, reader, &id2);
    pthread_create(&w1, NULL, writer, &id3);

    // Wait for threads to finish (infinite loop, so they won’t return)
    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w1, NULL);

    // Destroy semaphores (never reached in this case)
    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;
}


/*
Expected Output
The output will vary since threads execute concurrently, but a sample output might look like this:

localhost:/home/alphapeeler/OsSp25/week10 # gcc ex01_reader_writer_reader_pri.c -o ex01_reader_writer_reader_pri.o -lpthread
localhost:/home/alphapeeler/OsSp25/week10 # ./ex01_reader_writer_reader_pri.o
Reader 1 is reading data: 0
Reader 2 is reading data: 0
Writer 1 is writing data: 1
Reader 1 is reading data: 1
Reader 2 is reading data: 1
Reader 1 is reading data: 1
Reader 2 is reading data: 1
Writer 1 is writing data: 2
Reader 2 is reading data: 2
Reader 1 is reading data: 2
Writer 1 is writing data: 3
Reader 2 is reading data: 3
Reader 1 is reading data: 3
Reader 2 is reading data: 3
Reader 1 is reading data: 3
Writer 1 is writing data: 4
Reader 1 is reading data: 4
Reader 2 is reading data: 4
Reader 2 is reading data: 4
Reader 1 is reading data: 4
Writer 1 is writing data: 5
Reader 1 is reading data: 5
Reader 2 is reading data: 5
Writer 1 is writing data: 6
Reader 1 is reading data: 6
Reader 2 is reading data: 6
...
...
...

/*

/*
Explanation
1. Synchronization Mechanism:
rw_mutex: Ensures only one writer writes at a time.
mutex: Protects read_count updates.
read_count: Tracks the number of active readers.

2. Reader Execution:
When a reader starts, it locks mutex, increments read_count, and if it's the first reader, it locks rw_mutex (blocks writers).
The reader reads the shared data.
When it finishes, it decrements read_count. If it's the last reader, it unlocks rw_mutex.

3. Writer Execution:
The writer locks rw_mutex before writing (ensuring exclusive access).
It updates the shared data.
Once finished, it unlocks rw_mutex.

4. Fairness:
Readers have priority since multiple readers can read simultaneously while a writer must wait.
A writer can only proceed when no readers are reading.
This solution ensures mutual exclusion, progress, and bounded waiting while allowing multiple readers to access the shared resource simultaneously.
*/
