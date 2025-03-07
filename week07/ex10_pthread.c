#include <stdio.h>
#include <pthread.h>

static volatile int counter = 0; // Global variable shared between threads

void *mythread(void *arg) {
    printf("%s: begin, (counter = %d)\n", (char *)arg, counter);
    int i;
    for (i = 0; i < 1e7; i++) { // Loop 10 million times
        counter = counter + 1;  // Non-atomic increment operation (race condition)
    }
    printf("%s: done, (counter = %d)\n", (char *)arg, counter);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p1, p2;
    printf("main: begin (counter = %d)\n", counter);

    // Creating two threads that run `mythread`
    pthread_create(&p1, NULL, mythread, "A");
    pthread_create(&p2, NULL, mythread, "B");

    // Waiting for both threads to finish
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("main: done with both (counter = %d)\n", counter);
    return 0;
}



/*
localhost:/home/alphapeeler/OsSp25/week07 # gcc ex10_pthread.c -o ex10_pthread.o -lpthread
localhost:/home/alphapeeler/OsSp25/week07 # ./ex10_pthread.o 
main: begin (counter = 0)
A: begin, (counter = 0)
B: begin, (counter = 0)
A: done, (counter = 13771006)
B: done, (counter = 14816826)
main: done with both (counter = 14816826)
localhost:/home/alphapeeler/OsSp25/week07 #

localhost:/home/alphapeeler/OsSp25/week07 # ./ex10_pthread.o 
main: begin (counter = 0)
B: begin, (counter = 0)
A: begin, (counter = 40089)
B: done, (counter = 10270181)
A: done, (counter = 15886948)
main: done with both (counter = 15886948)
localhost:/home/alphapeeler/OsSp25/week07 #

localhost:/home/alphapeeler/OsSp25/week07 # ./ex10_pthread.o 
main: begin (counter = 0)
A: begin, (counter = 0)
B: begin, (counter = 37760)
B: done, (counter = 12191466)
A: done, (counter = 12292435)
main: done with both (counter = 12292435)
localhost:/home/alphapeeler/OsSp25/week07 #

*/