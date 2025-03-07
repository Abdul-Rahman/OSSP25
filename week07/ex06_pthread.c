/*
Program Flow
============
1. Main thread starts.
2. Creates 5 threads that perform computations in parallel.
3. Each thread prints its ID and starts computation.
4. Main thread waits for all threads to finish.
5. Threads complete, print their results, and return their ID.
6. Main thread prints completion message and exits.
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_THREADS 5  // Define the number of threads

void *BusyWork(void *t) {
    int i;
    long tid;
    double result = 0.0;
    tid = (long)t;
    printf("Thread %ld starting...\n", tid); //3

    for (i = 0; i < 1000000; i++) {
        result = result + sin(i) * tan(i);
    }

    printf("Thread %ld done. Result = %e\n", tid, result);
    pthread_exit((void *) t);
}

int main(int argc, char *argv[]) { //1
    pthread_t thread[NUM_THREADS];
    pthread_attr_t attr;
    int rc;
    long t;
    void *status;

    // Initialize and set thread detached attribute
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (t = 0; t < NUM_THREADS; t++) {
        printf("Main: creating thread %ld\n", t); 
        rc = pthread_create(&thread[t], &attr, BusyWork, (void *)t); //2
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Free attribute and wait for the other threads
    pthread_attr_destroy(&attr);
    for (t = 0; t < NUM_THREADS; t++) { //4
        rc = pthread_join(thread[t], &status);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
        printf("Main: completed join with thread %ld having status %ld\n", t, (long)status); //5
    }

    printf("Main: program completed. Exiting.\n"); //6
    pthread_exit(NULL);
}

/*
gcc ex06_pthread.c -o ex06_pthread.o -lpthread –lm
-lm: Links the math library (sin(), tan()).


localhost:/home/alphapeeler/OsSp25/week07 # gcc ex06_pthread.c -o ex06_pthread.o -lpthread -lm
localhost:/home/alphapeeler/OsSp25/week07 # ./ex06_pthread.o 
Main: creating thread 0
Main: creating thread 1
Thread 0 starting...
Main: creating thread 2
Main: creating thread 3
Main: creating thread 4
Thread 2 starting...
Thread 3 starting...
Thread 4 starting...
Thread 1 starting...
Thread 2 done. Result = -3.153838e+06
Thread 1 done. Result = -3.153838e+06
Thread 4 done. Result = -3.153838e+06
Thread 0 done. Result = -3.153838e+06
Main: completed join with thread 0 having status 0
Main: completed join with thread 1 having status 1
Main: completed join with thread 2 having status 2
Thread 3 done. Result = -3.153838e+06
Main: completed join with thread 3 having status 3
Main: completed join with thread 4 having status 4
Main: program completed. Exiting.
localhost:/home/alphapeeler/OsSp25/week07 # 

*/