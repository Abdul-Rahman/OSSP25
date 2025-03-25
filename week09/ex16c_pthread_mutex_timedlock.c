#include <stdio.h>
#include <pthread.h>
#include <time.h>

static volatile int counter = 0; // Global variable shared between threads
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // Mutex lock

void *mythread(void *arg) {
    printf("%s: begin, (counter = %d)\n", (char *)arg, counter);

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += 1;  // Set timeout for 1 second

    int i;
    for (i = 0; i < 1e7; i++) { // Loop 10 million times
        if (pthread_mutex_timedlock(&lock, &ts) == 0) { // Try to lock with timeout
            counter = counter + 1;  // Critical section
            pthread_mutex_unlock(&lock);  // Unlock
        }
        // If mutex is already locked and 1-second timeout is reached, skip incrementing
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
localhost:/home/alphapeeler/OsSp25/week09 # gcc ex16c_pthread_mutex_timedlock.c -o ex16c_pthread_mutex_timedlock.o -lpthread
localhost:/home/alphapeeler/OsSp25/week09 # ./ex16c_pthread_mutex_timedlock.o 
main: begin (counter = 0)
A: begin, (counter = 0)
B: begin, (counter = 0)
A: done, (counter = 19477486)
B: done, (counter = 19999524)
main: done with both (counter = 19999524)
localhost:/home/alphapeeler/OsSp25/week09 # ./ex16c_pthread_mutex_timedlock.o 
main: begin (counter = 0)
A: begin, (counter = 0)
B: begin, (counter = 0)
B: done, (counter = 18614610)
A: done, (counter = 19999671)
main: done with both (counter = 19999671)
localhost:/home/alphapeeler/OsSp25/week09 # 
*/

/*
Due to the timeout mechanism, threads may not always get the lock, 
so fewer increments occur compared to the original version. 
The counter value will be lower and inconsistent across runs.
*/