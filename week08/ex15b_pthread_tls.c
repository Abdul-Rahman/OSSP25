//Ex07 - pthread_cancel()
/*
Scenario: Imagine a bank system where an employee is performing a long-running 
audit on transactions. However, if a high-priority fraud detection system 
identifies suspicious activity, the audit should be canceled immediately to 
allocate resources elsewhere.
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
__thread int thread_local_var = 0; // TLS variable
void *worker_thread(void *arg) {
    int id = *(int *)arg;
    thread_local_var = id;
    printf("Thread %d: thread_local_var = %d\n", id, thread_local_var);
    return NULL;
}
int main() {
    pthread_t threads[3];
    int ids[3] = {1, 2, 3};
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, worker_thread, &ids[i]);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Main thread exiting.\n");
    return 0;
}

/*
localhost:/home/alphapeeler/OsSp25/week08 # gcc ex015b_pthread.c -o ex015b_pthread.o
localhost:/home/alphapeeler/OsSp25/week08 # ./ex015b_pthread.o 
Thread 1: thread_local_var = 1
Thread 2: thread_local_var = 2
Thread 3: thread_local_var = 3
Main thread exiting.
localhost:/home/alphapeeler/OsSp25/week08 # 
*/