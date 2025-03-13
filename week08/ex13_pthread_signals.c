#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <stdio.h>

void signal_handler(int sig) {
    printf("\nReceived signal %d in thread %ld\n", sig, pthread_self());
}

void *worker_thread(void *arg) {
    printf("%s: Thread %ld running.\n", (char *)arg, pthread_self());
    sleep(10); // Simulating work
    return NULL;
}

int main() {
    pthread_t thread;
    signal(SIGINT, signal_handler); // Asynchronous signal handling
    printf("Main Thread %ld running.\n", pthread_self());

    pthread_create(&thread, NULL, worker_thread, "worker1");
    printf("Press Ctrl+C to send SIGINT signal.\n");

    pthread_join(thread, NULL);

    printf("\n..[press (e) to exit]..");
    char ch;
    ch = getchar();
    if (ch=='e') {
        exit(0);
        printf("Main thread exiting.\n");
    }


    return 0;
}

/*
localhost:/home/alphapeeler/OsSp25/week08 # gcc ex13_pthread_signals.c -o ex13_pthread_signals.o
localhost:/home/alphapeeler/OsSp25/week08 # ./ex13_pthread_signals.o 
Main Thread 140018247432000 running.
Press Ctrl+C to send SIGINT signal.
worker1: Thread 140018244908736 running.
^C
Received signal 2 in thread 140018247432000
^C
Received signal 2 in thread 140018247432000

..[press (e) to exit]..e
localhost:/home/alphapeeler/OsSp25/week08 # 

*/
