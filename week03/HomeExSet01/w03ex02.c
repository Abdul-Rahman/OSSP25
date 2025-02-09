/*
Write a program which prints its PID and uses fork () system call
to create a child process. After fork () system call, both parent
and child processes print what kind of process they are and their 
PID. Also, the parent process prints its child’s PID, and the 
child process prints its parent’s PID. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid;

    printf("Before fork: Parent PID is %d\n", getpid());

    pid = fork();  // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } 
    else if (pid == 0) {  
        // Child process
        printf("I am the Child Process. My PID is %d and my Parent's PID is %d\n", getpid(), getppid());
    } 
    else {  
        // Parent process
        printf("I am the Parent Process. My PID is %d and my Child's PID is %d\n", getpid(), pid);
    }

    return 0;
}


/*
output:
Before fork: Parent PID is 10642
I am the Parent Process. My PID is 10642 and my Child's PID is 10643
I am the Child Process. My PID is 10643 and my Parent's PID is 1149
*/