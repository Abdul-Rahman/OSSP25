#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

/* Define a struct to pass multiple arguments to thread function */
typedef struct {
    int thread_no;
    char message[50];
} thdata;

/* Function to be executed by threads */
void *print_message_function(void *arg) {
    thdata *data = (thdata *) arg; // Cast the argument to the correct type
    printf("Thread %d says: %s\n", data->thread_no, data->message);
    pthread_exit(NULL); // Proper thread termination
}

int main() {
    pthread_t thread1, thread2;  /* Thread variables */
    thdata data1, data2;         /* Structs to be passed to threads */
    
    /* Initialize data to pass to thread 1 */
    data1.thread_no = 1;
    strcpy(data1.message, "Hello!");

    /* Initialize data to pass to thread 2 */
    data2.thread_no = 2;
    strcpy(data2.message, "Hi!");

    /* Create threads 1 and 2 */
    pthread_create(&thread1, NULL, print_message_function, (void *) &data1);
    pthread_create(&thread2, NULL, print_message_function, (void *) &data2);

    /* Main block now waits for both threads to terminate */
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Both threads have finished execution.\n");

    return 0;
}

/*
Output is in non deterministic order, see both runs outputs:

localhost:/home/alphapeeler/OsSp25/week07 # gcc ex04_pthread.c -o ex04_pthread.o -lpthread
localhost:/home/alphapeeler/OsSp25/week07 # ./ex04_pthread.o 
Thread 1 says: Hello!
Thread 2 says: Hi!
Both threads have finished execution.
localhost:/home/alphapeeler/OsSp25/week07 # 

localhost:/home/alphapeeler/OsSp25/week07 # ./ex04_pthread.o 
Thread 2 says: Hi!
Thread 1 says: Hello!
Both threads have finished execution.
localhost:/home/alphapeeler/OsSp25/week07 # 

*/