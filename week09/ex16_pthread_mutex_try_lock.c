#include <stdio.h>
#include <pthread.h>

static volatile int counter = 0; // Global variable shared between threads
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // Mutex lock

void *mythread(void *arg) {
    printf("%s: begin, (counter = %d)\n", (char *)arg, counter);
    int i;
    for (i = 0; i < 1e7; i++) { // Loop 10 million times
        if (pthread_mutex_trylock(&lock) == 0) {  // Try to lock
            counter = counter + 1;  // Critical section
            pthread_mutex_unlock(&lock);  // Unlock
        }
        // If mutex is already locked, skip incrementing
    }
    printf("%s: done, (counter = %d)\n", (char *)arg, counter);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p1, p2;
    pthread_mutex_init(&lock, NULL); // Initialize mutex
    printf("main: begin (counter = %d)\n", counter);

    // Creating two threads that run `mythread`
    pthread_create(&p1, NULL, mythread, "A");
    pthread_create(&p2, NULL, mythread, "B");

    // Waiting for both threads to finish
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("main: done with both (counter = %d)\n", counter);
    pthread_mutex_destroy(&lock); // Destroy mutex
    return 0;
}

/*
localhost:/home/alphapeeler/OsSp25/week09 # gcc ex16_pthread_mutex_try_lock.c -o ex16_pthread_mutex_try_lock.o -lpthread
localhost:/home/alphapeeler/OsSp25/week09 # ./ex16_pthread_mutex_try_lock.o 
main: begin (counter = 0)
A: begin, (counter = 0)
B: begin, (counter = 0)
A: done, (counter = 9987897)
B: done, (counter = 11154403)
main: done with both (counter = 11154403)
localhost:/home/alphapeeler/OsSp25/week09 # ./ex16_pthread_mutex_try_lock.o 
main: begin (counter = 0)
A: begin, (counter = 0)
B: begin, (counter = 0)
A: done, (counter = 9729401)
B: done, (counter = 11367541)
main: done with both (counter = 11367541)
localhost:/home/alphapeeler/OsSp25/week09 # 


*/

/*
Behavior of code:
Key Observations
* Each thread attempts to lock the mutex for every single iteration inside the loop.
* The pthread_mutex_trylock(&lock) call only locks if the mutex is available.
* If the mutex is already locked by the other thread, the increment operation is skipped for that iteration.
* Due to contention between two threads, many iterations are skipped, leading to an arbitrary counter value.

Why does code give an arbitrary counter value?
* Since pthread_mutex_trylock() does not block if the mutex is locked, many increments are lost.
* The final counter value depends on how many times each thread successfully acquires the lock.
* This depends on factors like CPU scheduling, context switching, and race conditions.
* Therefore, the final counter is less than 20 million and varies across runs.
*/