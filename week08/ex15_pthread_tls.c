#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// Thread Local Storage variable for session ID
__thread int session_id;

void* handle_request(void* arg) {
    // Assign a unique session ID for each thread's request
    session_id = rand() % 1000 + 1; // Simulating a session ID
    printf("Thread ID: %ld, Handling request with Session ID: %d\n", pthread_self(), session_id);

    // Simulate some processing time
    sleep(1);

    // Print session ID again to verify thread-local storage
    printf("Thread ID: %ld, Session ID still: %d\n", pthread_self(), session_id);

    return NULL;
}

int main() {
    pthread_t threads[5];

    // Seed random number generator
    srand(time(NULL));

    // Create multiple threads to simulate multiple requests
    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, handle_request, NULL);
    }

    // Join all threads
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}


/*
localhost:/home/alphapeeler/OsSp25/week08 # gcc ex15_pthread_tls.c -o ex15_pthread_tls.o
localhost:/home/alphapeeler/OsSp25/week08 # ./ex15_pthread_tls.o 
Thread ID: 140552257402560, Handling request with Session ID: 91
Thread ID: 140552249009856, Handling request with Session ID: 489
Thread ID: 140552240617152, Handling request with Session ID: 276
Thread ID: 140552232224448, Handling request with Session ID: 336
Thread ID: 140552223831744, Handling request with Session ID: 162
Thread ID: 140552257402560, Session ID still: 91
Thread ID: 140552249009856, Session ID still: 489
Thread ID: 140552240617152, Session ID still: 276
Thread ID: 140552232224448, Session ID still: 336
Thread ID: 140552223831744, Session ID still: 162
localhost:/home/alphapeeler/OsSp25/week08 # 
*/