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

    if (pthread_mutex_timedlock(&lock, &ts) == 0) {  // Try to lock with timeout
        for (int i = 0; i < 1e7; i++) { // Loop 10 million times
            counter = counter + 1;  // Critical section
        }
        pthread_mutex_unlock(&lock);  // Unlock
    } else {
        printf("%s: timeout, could not acquire lock\n", (char *)arg);
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
localhost:/home/alphapeeler/OsSp25/week09 # gcc ex16d_pthread_mutex_timedlock.c -o ex16d_pthread_mutex_timedlock.o -lpthread
localhost:/home/alphapeeler/OsSp25/week09 # ./ex16d_pthread_mutex_timedlock.o 
main: begin (counter = 0)
A: begin, (counter = 0)
B: begin, (counter = 0)
A: done, (counter = 14458610)
B: done, (counter = 20000000)
main: done with both (counter = 20000000)
localhost:/home/alphapeeler/OsSp25/week09 # ./ex16d_pthread_mutex_timedlock.o 
main: begin (counter = 0)
A: begin, (counter = 0)
B: begin, (counter = 0)
A: done, (counter = 10201334)
B: done, (counter = 20000000)
main: done with both (counter = 20000000)

*/

/*
Expected Output
* Since only one thread will acquire the lock, the other thread may time out and not 
execute the loop.
* The final counter will be either 10 million or 20 million, depending on whether 
both threads succeed in acquiring the lock.
*/