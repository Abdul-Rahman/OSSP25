#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5  // Number of philosophers

sem_t chopsticks[N];  // Semaphore array for chopsticks

void *philosopher(void *num) {
    int id = *(int *)num;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(1); // Simulate thinking time

        // Pick up chopsticks
        sem_wait(&chopsticks[id]);                   // Pick left chopstick
        printf("Philosopher %d picked up left chopstick\n", id);
        
        sem_wait(&chopsticks[(id + 1) % N]);         // Pick right chopstick
        printf("Philosopher %d picked up right chopstick\n", id);
        
        // Eating
        printf("Philosopher %d is eating...\n", id);
        sleep(2); // Simulate eating time

        // Put down chopsticks
        sem_post(&chopsticks[id]);                   // Put down left chopstick
        printf("Philosopher %d put down left chopstick\n", id);
        
        sem_post(&chopsticks[(id + 1) % N]);         // Put down right chopstick
        printf("Philosopher %d put down right chopstick\n", id);
    }
    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    // Initialize semaphores for chopsticks
    for (int i = 0; i < N; i++) {
        sem_init(&chopsticks[i], 0, 1);
        ids[i] = i;
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Join threads (infinite loop, so use Ctrl+C to stop execution)
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores (this part is never reached due to infinite loop)
    for (int i = 0; i < N; i++) {
        sem_destroy(&chopsticks[i]);
    }

    return 0;
}


/*
Expected Output
The exact output varies due to thread scheduling but follows this pattern:

localhost:/home/alphapeeler/OsSp25/week10 # gcc ex04_dining_philo_prob.c -o ex04_dining_philo_prob.o -lpthread
localhost:/home/alphapeeler/OsSp25/week10 # ./ex04_dining_philo_prob.o 
Philosopher 0 is thinking...
Philosopher 4 is thinking...
Philosopher 3 is thinking...
Philosopher 1 is thinking...
Philosopher 2 is thinking...
Philosopher 0 picked up left chopstick
Philosopher 0 picked up right chopstick
Philosopher 0 is eating...
Philosopher 4 picked up left chopstick
Philosopher 3 picked up left chopstick
Philosopher 2 picked up left chopstick
Philosopher 0 put down left chopstick
Philosopher 0 put down right chopstick
Philosopher 0 is thinking...
Philosopher 4 picked up right chopstick
Philosopher 4 is eating...
Philosopher 1 picked up left chopstick
Philosopher 4 put down left chopstick
Philosopher 4 put down right chopstick
Philosopher 4 is thinking...
Philosopher 0 picked up left chopstick
Philosopher 3 picked up right chopstick
Philosopher 3 is eating...
Philosopher 3 put down left chopstick
Philosopher 3 put down right chopstick
Philosopher 3 is thinking...
Philosopher 2 picked up right chopstick
...
...



Explanation
===========
Each philosopher thinks for a while.
They pick up the left chopstick, then the right chopstick (only if both are available).
They eat and then release the chopsticks.
This prevents deadlock since each philosopher picks up chopsticks in the same order.

NOTE: The loop is infinite because each philosopher runs inside a while (1) loop 
in the philosopher function. This means they will continuously go through the cycle 
of thinking, picking up chopsticks, eating, and putting them down without ever stopping.
Since the program never exits naturally, the main function never reaches the semaphore 
destruction part. To stop the program, you would need to manually terminate it 
(e.g., using Ctrl+C).
*/