#include <stdio.h>
#include <pthread.h>

static volatile int counter = 0; // Global variable shared between threads
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // Mutex lock

void *mythread(void *arg) {
    printf("%s: begin, (counter = %d)\n", (char *)arg, counter);
    int i;
    if (pthread_mutex_trylock(&lock) == 0) {  // Try to lock
        for (i = 0; i < 1e7; i++) { // Loop 10 million times
            counter = counter + 1;  // Critical section
        }
    }
    pthread_mutex_unlock(&lock);  // Unlock
    // If mutex is already locked, skip incrementing
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
localhost:/home/alphapeeler/OsSp25/week09 # gcc ex16b_pthread_mutex_try_lock.c -o ex16b_pthread_mutex_try_lock.o -lpthread
localhost:/home/alphapeeler/OsSp25/week09 # ./ex16b_pthread_mutex_try_lock.o 
main: begin (counter = 0)
B: begin, (counter = 0)
A: begin, (counter = 471735)
A: done, (counter = 471735)
B: done, (counter = 10000000)
main: done with both (counter = 10000000)
localhost:/home/alphapeeler/OsSp25/week09 # ./ex16b_pthread_mutex_try_lock.o 
main: begin (counter = 0)
A: begin, (counter = 0)
B: begin, (counter = 0)
B: done, (counter = 52258)
A: done, (counter = 10000000)
main: done with both (counter = 10000000)
localhost:/home/alphapeeler/OsSp25/week09 #
*/

/*
Behavior of code
Key Observations:
* 8Each thread calls pthread_mutex_trylock(&lock) once at the beginning.
* If the mutex is available, the thread locks it and executes the entire loop (increments counter 10 million times).
* If the mutex is already locked by the other thread, it skips the loop entirely.
* Since only one thread executes the loop, the final counter is exactly 10 million.

Why does code always give 10000000?
* One of the threads acquires the lock and executes the full loop (10 million increments).
* The other thread fails to acquire the lock and skips the loop entirely.
* Since only one thread completes 10 million increments, the final counter value is exactly 10 million every time.
*/