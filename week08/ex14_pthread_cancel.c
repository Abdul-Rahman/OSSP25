#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_t tid;  // Thread identifier

void *download_file(void *arg) {
    for (int i = 1; i <= 10; i++) {
        printf("Downloading... %d%%\n", i * 10);
        sleep(1); // Simulate time taken for downloading

        // Check if the thread is canceled
        pthread_testcancel();
    }
    printf("Download complete!\n");
    return NULL;
}

int main() {
    // Create the download thread
    pthread_create(&tid, NULL, download_file, NULL);

    // Simulate user waiting and then canceling download
    sleep(3);
    printf("User decides to cancel the download.\n");

    // Cancel the download thread
    pthread_cancel(tid);

    // Wait for the thread to terminate
    pthread_join(tid, NULL);

    printf("Download canceled successfully.\n");

    return 0;
}


/*
Explanation
The download_file function simulates a file download by printing progress in 10% increments.
The pthread_testcancel() function is called inside the loop to check if a cancellation request has been issued.
The main function creates a thread to run download_file.
After 3 seconds, the user decides to cancel the download, and pthread_cancel(tid); is called.
The program waits for the thread to terminate using pthread_join(tid, NULL);.
Finally, the program confirms that the download was canceled.
*/

/*
localhost:/home/alphapeeler/OsSp25/week08 # gcc ex14_pthread_cancel.c -o ex14_pthread_cancel.o
localhost:/home/alphapeeler/OsSp25/week08 # ./ex14_pthread_cancel.o 
Downloading... 10%
Downloading... 20%
Downloading... 30%
User decides to cancel the download.
Download canceled successfully.
localhost:/home/alphapeeler/OsSp25/week08 # ^C
localhost:/home/alphapeeler/OsSp25/week08 # 

*/