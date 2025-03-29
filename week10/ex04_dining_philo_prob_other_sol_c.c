/* Code for Possibility C, where we use an asymmetric solution to prevent deadlock.
Odd-numbered philosophers pick up their left chopstick first, then their right chopstick.
Even-numbered philosophers pick up their right chopstick first, then their left chopstick.
This breaks the circular wait condition that causes deadlock. */

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

        if (id % 2 == 0) {
            // Even-numbered philosophers pick up the right chopstick first
            sem_wait(&chopsticks[(id + 1) % N]);  // Pick right chopstick
            printf("Philosopher %d picked up right chopstick\n", id);

            sem_wait(&chopsticks[id]);  // Pick left chopstick
            printf("Philosopher %d picked up left chopstick\n", id);
        } else {
            // Odd-numbered philosophers pick up the left chopstick first
            sem_wait(&chopsticks[id]);  // Pick left chopstick
            printf("Philosopher %d picked up left chopstick\n", id);

            sem_wait(&chopsticks[(id + 1) % N]);  // Pick right chopstick
            printf("Philosopher %d picked up right chopstick\n", id);
        }

        // Eating
        printf("Philosopher %d is eating...\n", id);
        sleep(2); // Simulate eating time

        // Put down chopsticks
        sem_post(&chopsticks[id]);  // Put down left chopstick
        printf("Philosopher %d put down left chopstick\n", id);

        sem_post(&chopsticks[(id + 1) % N]);  // Put down right chopstick
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
localhost:/home/alphapeeler/OsSp25/week10 # gcc ex04_dining_philo_prob_other_sol_c.c -o ex04_dining_philo_prob_other_sol_c.o -lpthread
localhost:/home/alphapeeler/OsSp25/week10 # ./ex04_dining_philo_prob_other_sol_c.o 
Philosopher 0 is thinking...
Philosopher 1 is thinking...
Philosopher 2 is thinking...
Philosopher 3 is thinking...
Philosopher 4 is thinking...
Philosopher 1 picked up left chopstick
Philosopher 1 picked up right chopstick
Philosopher 1 is eating...
Philosopher 2 picked up right chopstick
Philosopher 4 picked up right chopstick
Philosopher 4 picked up left chopstick
Philosopher 4 is eating...
Philosopher 1 put down left chopstick
Philosopher 1 put down right chopstick
Philosopher 1 is thinking...
Philosopher 2 picked up left chopstick
Philosopher 2 is eating...
Philosopher 0 picked up right chopstick
Philosopher 4 put down left chopstick
Philosopher 4 put down right chopstick
Philosopher 4 is thinking...
Philosopher 0 picked up left chopstick
Philosopher 0 is eating...
Philosopher 2 put down left chopstick
Philosopher 2 put down right chopstick
Philosopher 2 is thinking...
Philosopher 3 picked up left chopstick
Philosopher 3 picked up right chopstick
Philosopher 3 is eating...
Philosopher 0 put down left chopstick
Philosopher 0 put down right chopstick
Philosopher 0 is thinking...
Philosopher 4 picked up right chopstick
Philosopher 1 picked up left chopstick
Philosopher 1 picked up right chopstick
Philosopher 1 is eating...
...
...
*/


/*
Explanation
1. Odd-numbered philosophers (1, 3):
Pick up their left chopstick first, then the right one.
2. Even-numbered philosophers (0, 2, 4):
Pick up their right chopstick first, then the left one.
3. This removes the possibility of a circular wait, which is a necessary condition for deadlock.

NOTE: The loop is infinite because each philosopher runs inside a while (1) loop 
in the philosopher function. This means they will continuously go through the cycle 
of thinking, picking up chopsticks, eating, and putting them down without ever stopping.
Since the program never exits naturally, the main function never reaches the semaphore 
destruction part. To stop the program, you would need to manually terminate it 
(e.g., using Ctrl+C).
*/


