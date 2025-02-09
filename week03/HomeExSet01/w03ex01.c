/*
1. Write a program which uses fork () system-call to create a 
child process. The child process prints the contents of the 
current directory, and the parent process waits for the 
childprocess to terminate.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) { 
        // Child process
        printf("Child Process (PID: %d) listing directory contents:\n", getpid());
        execlp("ls", "ls", "-l", NULL);
        perror("execlp failed");
        exit(1);
    } else { 
        // Parent process
        printf("Parent Process (PID: %d) waiting for child process (PID: %d) to complete...\n", getpid(), pid);
        wait(NULL);  
        printf("Child process finished. Parent process exiting.\n");
    }

    return 0;
}


/*
output:
localhost:/home/alphapeeler/OsSp25/week03/HomeExSet01 # ./w03ex01.o 
Parent Process (PID: 10576) waiting for child process (PID: 10577) to complete...
Child Process (PID: 10577) listing directory contents:
total 16
-rw-r--r-- 1 alphapeeler users   911 Feb  9 20:29 w03ex01.c
-rwxr-xr-x 1 root        root  11864 Feb  9 20:29 w03ex01.o
Child process finished. Parent process exiting.
localhost:/home/alphapeeler/OsSp25/week03/HomeExSet01 # 
*/