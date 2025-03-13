/*
Real-Life Scenario: Banking System With fork() Issue
1. The bank system has multiple threads:
    a. One thread processes transactions.
    b. Another thread handles balance inquiries.
2. If one thread calls fork(), the new child process only inherits the calling thread,
causing loss of other threads and leading to inconsistencies.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int account_balance = 1000;  // Shared resource (account balance)
pthread_mutex_t lock;        // Mutex for synchronization

void *transaction_thread(void *arg) {
    sleep(5); // Simulating a delay
    pthread_mutex_lock(&lock);
    printf("Transaction Thread: Processing transaction...\n");
    account_balance -= 100; // Withdraw $100
    printf("Transaction Thread: Updated Balance: $%d\n", account_balance);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *balance_inquiry_thread(void *arg) {
    sleep(3); // Simulating a delay
    pthread_mutex_lock(&lock);
    printf("Balance Inquiry Thread: Checking balance...\n");
    printf("Balance Inquiry Thread: Account Balance: $%d\n", account_balance);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Initialize the mutex
    pthread_mutex_init(&lock, NULL);

    // Create multiple threads handling different tasks
    pthread_create(&t1, NULL, transaction_thread, NULL);
    pthread_create(&t2, NULL, balance_inquiry_thread, NULL);

    sleep(1); // Ensure both threads start before fork()

    pid_t pid = fork();
    if (pid == 0) { // Child process
        printf("Child Process Created! (PID: %d)\n", getpid());
        printf("Child Process: Account Balance: $%d\n", account_balance);
        // The child does not inherit other threads, so account updates might be lost.
        exit(0);
    }

    // Wait for threads to finish in parent process
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Parent Process: Final Account Balance: $%d\n", account_balance);

    // Destroy mutex
    pthread_mutex_destroy(&lock);

    return 0;
}


/*
output:
localhost:/home/alphapeeler/OsSp25/week08 # gcc ex12_pthread.c -o ex12_pthread.o -lpthread
localhost:/home/alphapeeler/OsSp25/week08 # ./ex12_pthread.o
Child Process Created! (PID: 1852)
Child Process: Account Balance: $1000
Balance Inquiry Thread: Checking balance...
Balance Inquiry Thread: Account Balance: $1000
Transaction Thread: Processing transaction...
Transaction Thread: Updated Balance: $900
Parent Process: Final Account Balance: $900
localhost:/home/alphapeeler/OsSp25/week08 #
*/


/*
Key Issue Demonstrated:
1. The parent process creates multiple threads.
2. fork() is called inside the main process, but only the calling thread is duplicated in the child.
3. The child process sees an inconsistent state:
    a. The transaction_thread might not have completed before the fork.
    b. The balance_inquiry_thread is missing in the child.
    c. The child gets an incomplete snapshot of account balance.
4. The child process is unaware of any ongoing updates in the parent process.

Solution to Fix This Issue
1. Instead of using fork() in a multithreaded program, use pthread_create() for concurrency.
2. If fork() must be used, ensure it is called before creating threads or use pthread_atfork() to handle the issue properly.
 */
