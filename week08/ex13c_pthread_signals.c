#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>  // Include this for strcmp

volatile sig_atomic_t stop = 0; // Flag to indicate termination

void signal_handler(int sig) {
    printf("\nReceived signal %d in thread %ld\n", sig, pthread_self());
    if (sig == SIGINT) { // Ctrl+C
        stop = 1; // Set termination flag
    }
}

void *worker_thread(void *arg) {
    signal(SIGUSR1, signal_handler);
    printf("%s: Thread %ld running.\n", (char *)arg, pthread_self());
    while (!stop) sleep(1); // Check termination flag periodically
    printf("%s: Thread %ld exiting.\n", (char *)arg, pthread_self());
    return NULL;
}

void *sigterm_handler_thread(void *arg) {
    signal(SIGTERM, signal_handler);
    printf("%s: Thread %ld waiting for SIGTERM.\n", (char *)arg, pthread_self());
    while (!stop) sleep(1);
    printf("%s: Thread %ld exiting.\n", (char *)arg, pthread_self());
    return NULL;
}

void *sigtstp_handler_thread(void *arg) {
    signal(SIGTSTP, signal_handler);
    printf("%s: Thread %ld running.\n", (char *)arg, pthread_self());
    while (!stop) sleep(1);
    printf("%s: Thread %ld exiting.\n", (char *)arg, pthread_self());
    return NULL;
}

void *sigquit_handler_thread(void *arg) {
    signal(SIGQUIT, signal_handler);
    printf("%s: Thread %ld running.\n", (char *)arg, pthread_self());
    while (!stop) sleep(1);
    printf("%s: Thread %ld exiting.\n", (char *)arg, pthread_self());
    return NULL;
}

void *sigchld_handler_thread(void *arg) {
    signal(SIGCHLD, signal_handler);
    printf("%s: Thread %ld running.\n", (char *)arg, pthread_self());
    while (!stop) sleep(1);
    printf("%s: Thread %ld exiting.\n", (char *)arg, pthread_self());
    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3, thread4, thread5;

    signal(SIGINT, signal_handler); // Handle Ctrl+C in main thread
    printf("Main Thread %ld running.\n", pthread_self());

    pthread_create(&thread1, NULL, worker_thread, "worker1");
    pthread_create(&thread2, NULL, sigterm_handler_thread, "sigterm_handler");
    pthread_create(&thread3, NULL, sigtstp_handler_thread, "sigtstp_handler");
    pthread_create(&thread4, NULL, sigquit_handler_thread, "sigquit_handler");
    pthread_create(&thread5, NULL, sigchld_handler_thread, "sigchld_handler");

    printf("Press Ctrl+C to terminate the program.\n");

    // User prompt to exit
    while (!stop) {
        char input[10];
        printf("Type 'exit' to terminate: ");
        if (scanf("%9s", input) == 1 && strcmp(input, "exit") == 0) {
            stop = 1; // Set termination flag
        }
        sleep(1); // Avoid busy looping
    }

    printf("\nTerminating all threads...\n");

    // Wait for threads to exit
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL);

    printf("Main thread exiting.\n");

    return 0;
}


/*
localhost:/home/alphapeeler/OsSp25/week08 # ./ex13c_pthread_signals.o 
Main Thread 140361667192640 running.
worker1: Thread 140361664034496 running.
sigchld_handler: Thread 140361630463680 running.
sigtstp_handler: Thread 140361647249088 running.
sigterm_handler: Thread 140361655641792 waiting for SIGTERM.
Press Ctrl+C to terminate the program.
Type 'exit' to terminate: sigquit_handler: Thread 140361638856384 running.

Received signal 10 in thread 140361667192640
        
Received signal 15 in thread 140361667192640

Received signal 20 in thread 140361667192640

Received signal 3 in thread 140361667192640

Received signal 17 in thread 140361667192640
^C
Received signal 2 in thread 140361667192640
sigterm_handler: Thread 140361655641792 exiting.
sigtstp_handler: Thread 140361647249088 exiting.
worker1: Thread 140361664034496 exiting.
sigquit_handler: Thread 140361638856384 exiting.
sigchld_handler: Thread 140361630463680 exiting.
^Z
Received signal 20 in thread 140361667192640
exit

Terminating all threads...
Main thread exiting.
localhost:/home/alphapeeler/OsSp25/week08 # 
/*


/*
Issue commands from another terminal:

localhost:/home/alphapeeler/OsSp25 # ps -ax | grep ex13c*
 2016 ?        Sl     4:49 /usr/bin/kate -b /home/alphapeeler/OsSp25/week08/ex13_pthread_signals.c
 2499 ?        Sl     0:02 /usr/bin/kate -b /home/alphapeeler/OsSp25/week08/ex13c_pthread_signals.c
 3833 pts/6    Sl+    0:00 ./ex13c_pthread_signals.o
 3845 pts/2    S+     0:00 grep --color=auto ex13c*
localhost:/home/alphapeeler/OsSp25 # kill -SIGUSR1 3833
localhost:/home/alphapeeler/OsSp25 # kill -SIGTERM 3833
localhost:/home/alphapeeler/OsSp25 # kill -SIGTERM 3833
localhost:/home/alphapeeler/OsSp25 # kill -SIGTSTP 3833
localhost:/home/alphapeeler/OsSp25 # kill -SIGQUIT 3833
localhost:/home/alphapeeler/OsSp25 # KILL -SIGCHLD 3833
bash: KILL: command not found
localhost:/home/alphapeeler/OsSp25 # 
localhost:/home/alphapeeler/OsSp25 # kill -SIGCHLD 3833
localhost:/home/alphapeeler/OsSp25 # 
*/