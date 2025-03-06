// Pipes across a fork

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main() {
    int data_processed;
    int file_pipes[2];
    const char some_data[] = "AlphaPeeler";
    char buffer[BUFSIZ + 1];
    pid_t fork_result;
    memset(buffer, '\0', sizeof(buffer));
    if (pipe(file_pipes) == 0) {
        fork_result = fork();
        if (fork_result == -1) {
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
        }
        if (fork_result == 0) {
            data_processed = read(file_pipes[0], buffer, BUFSIZ);
            printf("Read %d bytes: %s\n", data_processed, buffer);
            exit(EXIT_SUCCESS);
        } else {
            data_processed = write(file_pipes[1], some_data,
            strlen(some_data));
            printf("Wrote %d bytes\n", data_processed);
        }
    }
    exit(EXIT_SUCCESS);
}

/*
localhost:/home/alphapeeler/OsSp25/week05 # gcc ex06_pipe02.c -o ex06_pipe02.o
localhost:/home/alphapeeler/OsSp25/week05 # ./ex06_pipe02.o 
Wrote 11 bytes
Read 11 bytes: AlphaPeeler
localhost:/home/alphapeeler/OsSp25/week05 # 


How It Works
First, the program creates a pipe with the pipe call. It then uses 
the fork call to create a new process. If the fork was successful, 
the parent writes data into the pipe, while the child reads data 
from the pipe.
*/