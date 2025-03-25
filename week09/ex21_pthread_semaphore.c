//Pthread C code for Deadlock

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem1, sem2;

void* thread1(void* arg) {
    sem_wait(&sem1); // Lock sem1
    sleep(1);        // Ensure thread2 gets a chance to execute and acquire sem2
    sem_wait(&sem2); // Now try to lock sem2 (deadlock occurs if thread2 has it)
    printf("Thread 1\n");
    sem_post(&sem2);
    sem_post(&sem1);
    return NULL;
}

void* thread2(void* arg) {
    sem_wait(&sem2); // Lock sem2
    sleep(1);        // Ensure thread1 gets a chance to execute and acquire sem1
    sem_wait(&sem1); // Now try to lock sem1 (deadlock occurs if thread1 has it)
    printf("Thread 2\n");
    sem_post(&sem1);
    sem_post(&sem2);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Initialize semaphores
    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 1);

    // Create threads
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    // Wait for threads to complete
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy semaphores
    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}



/*
localhost:/home/alphapeeler/OsSp25/week09 # gcc ex21_pthread_semaphore.c -o ex21_pthread_semaphore.o -lpthread
localhost:/home/alphapeeler/OsSp25/week09 # ./ex21_pthread_semaphore.o


*/

/*
Expected Output:
No output (or program freezing) because the threads are stuck in a deadlock.

Explanation:
thread1() locks sem1 first and then tries to lock sem2.
thread2() locks sem2 first and then tries to lock sem1.
If both threads execute simultaneously, thread1 locks sem1 while thread2 locks sem2. Now:
thread1 is waiting for sem2 (held by thread2).
thread2 is waiting for sem1 (held by thread1).
Since neither thread can proceed, a deadlock occurs, and both threads are stuck indefinitely.

How to Fix the Deadlock?
A common approach to avoid deadlocks is to ensure that all threads acquire resources (semaphores) in the same order. For example:
Modify thread2() to acquire sem1 first and then sem2, just like thread1().
*/
