/*
Orphan Process Example
An orphan process occurs when a parent exits before the child,
leaving the child running. The init process (PID 1) adopts the
 orphan.
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid = fork(); // Create a child process

    if (pid > 0) {
        // Parent process: Exits immediately
        printf("Parent process (PID: %d) exiting.\n", getpid());
        exit(0); // Parent exits before the child
    }
    else if (pid == 0) {
        // Child process: Runs after parent exits
        sleep(5); // Ensures the parent exits first
        printf("\nChild process (PID: %d) is now an orphan, adopted by init (PID: %d).\n", getpid(), getppid());
    }
    else {
        // If fork fails
        printf("Fork failed!\n");
        return 1;
    }

    return 0;
}

/*
output:
localhost:/home/alphapeeler/OsSp25/week04 # gcc ex04_orphan02.c -o ex04_orphan02.o
localhost:/home/alphapeeler/OsSp25/week04 # ./ex04_orphan02.o 
Parent process (PID: 5253) exiting.
localhost:/home/alphapeeler/OsSp25/week04 # 
Child process (PID: 5254) is now an orphan, adopted by init (PID: 1156).
localhost:/home/alphapeeler/OsSp25/week04 #
*/