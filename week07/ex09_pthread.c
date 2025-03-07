// ex 09 - using assert()
#include <stdio.h>
#include <assert.h>
#include <pthread.h>

void *mythread(void *arg) {
    printf("%s\n", (char *) arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p1, p2;
    int rc; 

    printf("main: begin\n");

    rc = pthread_create(&p1, NULL, mythread, "A"); 
    assert(rc == 0);

    rc = pthread_create(&p2, NULL, mythread, "B");
    assert(rc == 0);

    // join waits for the threads to finish
    rc = pthread_join(p1, NULL);
    assert(rc == 0);

    rc = pthread_join(p2, NULL);
    assert(rc == 0);

    printf("main: end\n");
    return 0;
}

/*
localhost:/home/alphapeeler/OsSp25/week07 # gcc ex09_pthread.c -o ex09_pthread.o -lpthread
localhost:/home/alphapeeler/OsSp25/week07 # ./ex09_pthread.o 
main: begin
A
B
main: end
localhost:/home/alphapeeler/OsSp25/week07 #
*/