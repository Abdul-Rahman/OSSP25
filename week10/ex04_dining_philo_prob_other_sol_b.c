/* Possibility B, where a philosopher picks up both chopsticks only if both are available.
 * This prevents deadlock because no philosopher can hold one chopstick while waiting
 * indefinitely for the other.
 */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5  // Number of philosophers

sem_t chopsticks[N];  // Semaphore array for chopsticks
pthread_mutex_t mutex; // Mutex to ensure atomic checking of both chopsticks

void *philosopher(void *num) {
    int id = *(int *)num;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(1); // Simulate thinking time

        // Critical section: Check if both chopsticks are available
        pthread_mutex_lock(&mutex);

        if (sem_trywait(&chopsticks[id]) == 0) { // Try to pick left chopstick
            if (sem_trywait(&chopsticks[(id + 1) % N]) == 0) { // Try to pick right chopstick
                pthread_mutex_unlock(&mutex); // Release mutex after acquiring both

                // Eating
                printf("Philosopher %d is eating...\n", id);
                sleep(2); // Simulate eating time

                // Put down chopsticks
                sem_post(&chopsticks[id]);                   // Put down left chopstick
                printf("Philosopher %d put down left chopstick\n", id);

                sem_post(&chopsticks[(id + 1) % N]);         // Put down right chopstick
                printf("Philosopher %d put down right chopstick\n", id);
            } else {
                // If right chopstick is unavailable, release left chopstick
                sem_post(&chopsticks[id]);
            }
        }

        pthread_mutex_unlock(&mutex); // Ensure mutex is unlocked in any case
    }
    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    // Initialize semaphores and mutex
    pthread_mutex_init(&mutex, NULL);
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

    // Destroy semaphores and mutex (this part is never reached due to infinite loop)
    for (int i = 0; i < N; i++) {
        sem_destroy(&chopsticks[i]);
    }
    pthread_mutex_destroy(&mutex);

    return 0;
}


/*
localhost:/home/alphapeeler/OsSp25/week10 # gcc ex04_dining_philo_prob_other_sol_b.c -o ex04_dining_philo_prob_other_sol_b.o -lpthread
localhost:/home/alphapeeler/OsSp25/week10 # ./ex04_dining_philo_prob_other_sol_b.o 
Philosopher 3 is thinking...
Philosopher 0 is thinking...
Philosopher 4 is thinking...
Philosopher 2 is thinking...
Philosopher 1 is thinking...
Philosopher 3 is eating...
Philosopher 4 is thinking...
Philosopher 0 is eating...
Philosopher 2 is thinking...
Philosopher 1 is thinking...
Philosopher 4 is thinking...
Philosopher 1 is thinking...
Philosopher 2 is thinking...
Philosopher 3 put down left chopstick
Philosopher 3 put down right chopstick
Philosopher 3 is thinking...
Philosopher 4 is thinking...
Philosopher 1 is thinking...
Philosopher 2 is eating...
Philosopher 0 put down left chopstick
Philosopher 0 put down right chopstick
Philosopher 0 is thinking...
Philosopher 3 is thinking...
Philosopher 1 is thinking...
Philosopher 0 is eating...
Philosopher 4 is thinking...
Philosopher 4 is thinking...
Philosopher 2 put down left chopstick
Philosopher 2 put down right chopstick
Philosopher 2 is thinking...
Philosopher 3 is eating...
Philosopher 1 is thinking...
Philosopher 0 put down left chopstick
Philosopher 0 put down right chopstick
Philosopher 0 is thinking...
Philosopher 4 is thinking...
Philosopher 2 is thinking...
Philosopher 1 is eating...
...
...
...

*/

/*
Explanation
1. We introduce a mutex (pthread_mutex_t mutex) to ensure that checking and picking up 
chopsticks is done atomically.
2. Instead of waiting indefinitely (sem_wait), we use sem_trywait, which only picks up 
a chopstick if it is immediately available.
3. If a philosopher successfully picks up the left chopstick but fails to pick up the 
right one, they immediately put the left chopstick back.
4. This prevents a scenario where all philosophers pick up one chopstick and wait 
forever for the second one (which would cause deadlock).


NOTE: The loop is infinite because each philosopher runs inside a while (1) loop 
in the philosopher function. This means they will continuously go through the cycle 
of thinking, picking up chopsticks, eating, and putting them down without ever stopping.
Since the program never exits naturally, the main function never reaches the semaphore 
destruction part. To stop the program, you would need to manually terminate it 
(e.g., using Ctrl+C).
*/