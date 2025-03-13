#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define ARRAY_SIZE 1000000

int global_array[ARRAY_SIZE]; // Shared array

// Function to initialize the array with random values
void initialize_array() {
    srand(time(NULL));  // Set a different seed based on the current time
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        global_array[i] = rand() % 1000; // Random numbers between 0 and 999
    }
}

// Function to find the sum of elements in a portion of the array
void *sum_array(void *arg) {
    int thread_id = *(int *)arg;
    int start = thread_id * (ARRAY_SIZE / NUM_THREADS);
    int end = start + (ARRAY_SIZE / NUM_THREADS);
    long sum = 0;

    // Calculate the sum of the assigned portion of the array
    for (int i = start; i < end; ++i) {
        sum += global_array[i];
    }

    return (void *)sum; // Return the sum as a void pointer
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    void *thread_results[NUM_THREADS];
    long total_sum = 0;

    // Initialize the array with random values
    initialize_array();

    // Create threads to compute the sum of array elements
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, sum_array, (void *)&thread_args[i]);
    }

    // Join threads and collect results
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], &thread_results[i]);
        total_sum += (long)thread_results[i]; // Accumulate the partial sums
    }

    printf("Total sum of array elements: %ld\n", total_sum);

    return 0;
}


/*
localhost:/home/alphapeeler/OsSp25/week07 # gcc ex11_pthread.c -o ex11_pthread.o -lpthread
localhost:/home/alphapeeler/OsSp25/week07 # ./ex11_pthread.o 
Total sum of array elements: 499865937
localhost:/home/alphapeeler/OsSp25/week07 # ./ex11_pthread.o 
Total sum of array elements: 499214022
localhost:/home/alphapeeler/OsSp25/week07 # ./ex11_pthread.o 
Total sum of array elements: 499042588
localhost:/home/alphapeeler/OsSp25/week07 # 
*/


/*
Explanation of the Program:
1. Initialization
* The program defines an array of size 1,000,000 and fills it with random integers between 0 and 999.
* It uses 4 threads to process the array in parallel.
2. Multi-threaded Sum Calculation
* The array is divided into 4 equal parts, and each thread computes the sum of one part.
* Each thread runs the function sum_array(), which calculates the sum for its portion.
* The results from each thread are returned as void*, which is then typecast back to long.
3. Aggregating the Results
* The pthread_join() function ensures that the main thread waits for all worker threads to complete.
* After collecting the partial sums, the main thread adds them together to get the total sum.
4. Output
* The program prints the total sum of all array elements.
* The actual output will vary depending on the random values generated.
* This approach improves performance by parallelizing the computation, making it significantly faster than a single-threaded approach when working with large datasets.
*/