//Ex08 - pthread_detach()
// Detaches the thread using pthread_detach(), allowing it to clean up automatically 
// when it finishes execution.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Function to be executed by the thread
void* threadFunction(void* arg) {
    printf("Thread is running...\n");
    // Simulate some work with sleep
    sleep(2);
    printf("Thread is finishing...\n");
    return NULL;
}

int main() {
    pthread_t thread;
    int result;

    // Create a new thread
    result = pthread_create(&thread, NULL, threadFunction, NULL);
    if (result != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    // Detach the thread
    result = pthread_detach(thread);
    if (result != 0) {
        fprintf(stderr, "Error detaching thread\n");
        return 1;
    }

    // Main thread continues to run
    printf("Main thread is continuing...\n");
    // Simulate some work in the main thread
    sleep(3);
    printf("Main thread is finishing...\n");

    return 0;
}

/*
localhost:/home/alphapeeler/OsSp25/week07 # gcc ex08_pthread.c -o ex08_pthread.o -lpthread
localhost:/home/alphapeeler/OsSp25/week07 # ./ex08_pthread.o 
Main thread is continuing...
Thread is running...
Thread is finishing...
Main thread is finishing...
localhost:/home/alphapeeler/OsSp25/week07 # 
*/

/*
Explanation:
Thread Function (threadFunction):
1. Prints a message when it starts.
2. Sleeps for 2 seconds to simulate work.
3. Prints a message when it finishes.

Main Function (main):
1. Creates a thread using pthread_create().
2. hecks for errors while creating the thread.
3. Detaches the thread using pthread_detach(), allowing it to clean up automatically when it finishes execution.
4. Prints messages and simulates work in the main thread using sleep(3).
5. Returns 0 to indicate successful execution.
*/