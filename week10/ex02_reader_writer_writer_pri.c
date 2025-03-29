#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

// Semaphore declarations
sem_t rw_mutex;    // Controls access to shared data (for writers)
sem_t mutex;       // Protects read_count (reader counter)
sem_t writer_queue; // Ensures writer priority (blocks new readers)

int read_count = 0; // Number of active readers
int data = 0;       // Shared data (resource)

// Reader function
void *reader(void *arg) {
    int id = *(int *)arg; // Get reader ID
    while (1) {
        sem_wait(&writer_queue);  // Prevents new readers if a writer is waiting
        sem_wait(&mutex); // Lock before modifying read_count
        read_count++;
        if (read_count == 1) {
            sem_wait(&rw_mutex); // First reader locks the writer
        }
        sem_post(&mutex); // Unlock after modifying read_count
        sem_post(&writer_queue); // Allow other readers to proceed

        // Reading section
        printf("Reader %d is reading data: %d\n", id, data);
        sleep(1); // Simulate reading time

        // Exit section
        sem_wait(&mutex); // Lock before modifying read_count
        read_count--;
        if (read_count == 0) {
            sem_post(&rw_mutex); // Last reader unlocks the writer
        }
        sem_post(&mutex); // Unlock after modifying read_count

        sleep(1); // Simulate delay before next read
    }
}

// Writer function
void *writer(void *arg) {
    int id = *(int *)arg; // Get writer ID
    while (1) {
        sem_wait(&writer_queue); // Blocks new readers while waiting
        sem_wait(&rw_mutex); // Lock for writing

        // Writing section
        data++; // Modify shared data
        printf("Writer %d is writing data: %d\n", id, data);
        sleep(1); // Simulate writing time

        sem_post(&rw_mutex); // Release access after writing
        sem_post(&writer_queue); // Allow next waiting process (reader/writer)

        sleep(2); // Simulate delay before next write
    }
}

int main() {
    pthread_t r1, r2, w1, w2; // Thread variables
    int id1 = 1, id2 = 2, id3 = 1, id4 = 2;

    // Initialize semaphores
    sem_init(&rw_mutex, 0, 1); // Binary semaphore (1 means available)
    sem_init(&mutex, 0, 1);    // Binary semaphore for protecting read_count
    sem_init(&writer_queue, 0, 1); // Ensures writer priority

    // Create reader and writer threads
    pthread_create(&r1, NULL, reader, &id1);
    pthread_create(&r2, NULL, reader, &id2);
    pthread_create(&w1, NULL, writer, &id3);
    pthread_create(&w2, NULL, writer, &id4);

    // Wait for threads (never-ending loops, so these won't return)
    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w1, NULL);
    pthread_join(w2, NULL);

    // Destroy semaphores (this won't be reached in this case)
    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);
    sem_destroy(&writer_queue);

    return 0;
}


/*
Expected Output
Since threads run concurrently, the output will vary, but a possible scenario looks like this:

localhost:/home/alphapeeler/OsSp25/week10 # gcc ex02_reader_writer_writer_pri.c -o ex02_reader_writer_writer_pri.o -lpthread
localhost:/home/alphapeeler/OsSp25/week10 # ./ex02_reader_writer_writer_pri.o 
Reader 1 is reading data: 0
Writer 1 is writing data: 1
Reader 1 is reading data: 1
Reader 2 is reading data: 1
Writer 2 is writing data: 2
Writer 1 is writing data: 3
Reader 1 is reading data: 3
Reader 2 is reading data: 3
Writer 2 is writing data: 4
Writer 1 is writing data: 5
Reader 1 is reading data: 5
Reader 2 is reading data: 5
Writer 2 is writing data: 6
...
...



Explanation
1. Synchronization Mechanism:
rw_mutex: Ensures exclusive access for writers.
mutex: Protects read_count to manage multiple readers.
writer_queue: Gives priority to writers by blocking new readers while a writer is waiting.

2. How Writers Get Priority:
When a writer arrives, it locks writer_queue, preventing new readers from entering.
It then locks rw_mutex, writes, and releases both semaphores.

3. How Readers Work:
A reader must first check writer_queue. If a writer is waiting, the reader is blocked.
The first reader locks rw_mutex (preventing writers).
The last reader unlocks rw_mutex.

4. Advantages:
No writer starvation (since readers must wait if a writer is waiting).
Efficient reading (multiple readers can read simultaneously).

5. Disadvantage:
Reader starvation: If many writers keep arriving, readers may be delayed indefinitely.
*/