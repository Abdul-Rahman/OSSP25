/* To fix the race condition, we can use mutex
 * (pthread_mutex_t) to synchronize access.
 */
#include <stdio.h>
#include <pthread.h>

static volatile int counter = 0; // Global variable shared between threads
pthread_mutex_t lock; // Mutex lock

void *mythread(void *arg) {
    printf("%s: begin, (counter = %d)\n", (char *)arg, counter);
    int i;
    for (i = 0; i < 1e7; i++) { // Loop 10 million times
        pthread_mutex_lock(&lock);  // Lock before modifying counter
        counter = counter + 1;  // Atomic increment operation (race condition removed)
        pthread_mutex_unlock(&lock);  // Unlock after modification
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
localhost:/home/alphapeeler/OsSp25/week07 # gcc ex10b_pthread.c -o ex10b_pthread.o -lpthread
localhost:/home/alphapeeler/OsSp25/week07 # ./ex10b_pthread.o 
main: begin (counter = 0)
B: begin, (counter = 0)
A: begin, (counter = 0)
B: done, (counter = 19968528)
A: done, (counter = 20000000)
main: done with both (counter = 20000000)
localhost:/home/alphapeeler/OsSp25/week07 # 

localhost:/home/alphapeeler/OsSp25/week07 # ./ex10b_pthread.o 
main: begin (counter = 0)
A: begin, (counter = 0)
B: begin, (counter = 0)
B: done, (counter = 19769813)
A: done, (counter = 20000000)
main: done with both (counter = 20000000)
localhost:/home/alphapeeler/OsSp25/week07 # 


*/