//Ex07 - pthread_cancel()
/*
Scenario: Imagine a bank system where an employee is performing a long-running 
audit on transactions. However, if a high-priority fraud detection system 
identifies suspicious activity, the audit should be canceled immediately to 
allocate resources elsewhere.
*/
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// Function that simulates a long-running audit
void* perform_audit(void* arg) {
    int i = 0;
    while (1) {  // Infinite loop to simulate a long-running process
        printf("Performing audit step %d...\n", ++i);
        sleep(1);  // Simulate time-consuming work
        // Cancellation point: pthread_testcancel() can be used for fine control
        pthread_testcancel();
    }
    return NULL;
}

int main() {
    pthread_t audit_thread;
    
    // Start the audit process
    printf("Starting transaction audit...\n");
    pthread_create(&audit_thread, NULL, perform_audit, NULL);

    // Simulating fraud detection after 5 seconds
    sleep(5);
    printf("Fraud detected! Cancelling audit process...\n");

    // Request to cancel the audit thread
    pthread_cancel(audit_thread);

    // Ensure thread cleanup
    pthread_join(audit_thread, NULL);

    printf("Audit process terminated. Redirecting resources to fraud investigation.\n");

    return 0;
}

/*
localhost:/home/alphapeeler/OsSp25/week07 # gcc ex07_pthread.c -o ex07_pthread.o -lpthread
localhost:/home/alphapeeler/OsSp25/week07 # ./ex07_pthread.o 
Starting transaction audit...
Performing audit step 1...
Performing audit step 2...
Performing audit step 3...
Performing audit step 4...
Performing audit step 5...
Fraud detected! Cancelling audit process...
Audit process terminated. Redirecting resources to fraud investigation.
localhost:/home/alphapeeler/OsSp25/week07 # 
*/
/*
Explanation:
1. A separate thread is created to perform a long-running audit.
2. The thread continuously runs in an infinite loop, simulating audit steps.
3. If fraud is detected (simulated by sleep(5)), the audit process is canceled using pthread_cancel.
4. pthread_join ensures proper cleanup after termination.
5. The program exits after redirecting resources.

Key Learning:
* pthread_cancel requests thread termination but does not forcefully kill it immediately.
* The thread should check for cancellation using pthread_testcancel().
* Use case: Canceling background tasks like audits, downloads, or data processing when higher priority events occur.
*/