#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function
void sigint_handler(int signum) {
    printf("\nCaught SIGINT signal (%d)\n", signum);
}

int main() {
    // Registering signal handler for SIGINT
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        printf("Error setting up signal handler for SIGINT\n");
        return 1;
    }

    printf("Press Ctrl+C to send a SIGINT signal\n");

    // Infinite Loop to keep the program running
    while (1) {
        sleep(1);
    }

    return 0;
}


/*
WARNING : Followng program never exits!


localhost:/home/alphapeeler/OsSp25/week08 # gcc ex13b_pthread_signals.c -o ex13b_pthread_signals.o
localhost:/home/alphapeeler/OsSp25/week08 # ./ex13b_pthread_signals.o 
Press Ctrl+C to send a SIGINT signal
^C
Caught SIGINT signal (2)
^C
Caught SIGINT signal (2)
^C
Caught SIGINT signal (2)
^C
Caught SIGINT signal (2)
^C
Caught SIGINT signal (2)

*/