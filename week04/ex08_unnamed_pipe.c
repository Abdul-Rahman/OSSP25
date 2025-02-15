//Demonstration of Un-named pipes
/*
Changes Made:
1. Removed mkfifo(), as unnamed pipes do not require a filesystem entry.
2. Replaced open() with pipe(), which creates a pipe between a parent and child process.
3. Introduced fork() to create a parent-child relationship since unnamed pipes only work between related processes.
4. Used pipefd[2] to store read (pipefd[0]) and write (pipefd[1]) ends of the pipe.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For pipe() and fork()

int main() {
    int pipefd[2];  // File descriptors for pipe
    pid_t pid;
    char str1[80], str2[80];

    // Create an unnamed pipe
    pipe(pipefd);  // Change: Used pipe() instead of mkfifo()

    pid = fork();  // Change: Used fork() to create a child process

    if (pid > 0) {  // Parent process (Reader)
        close(pipefd[1]); // Close unused write end
        while (1) {
            read(pipefd[0], str1, sizeof(str1));
            printf("User1: %s\n", str1);
        }
    } else {  // Child process (Writer)
        close(pipefd[0]); // Close unused read end
        while (1) {
            fgets(str2, 80, stdin);
            write(pipefd[1], str2, strlen(str2) + 1);
        }
    }

    return 0;
}

/*
Output
localhost:/home/alphapeeler/OsSp25/week04 # gcc ex08_unnamed_pipe.c -o ex08_unnamed_pipe.o
localhost:/home/alphapeeler/OsSp25/week04 # ./ex08_unnamed_pipe.o 
My name is AlphaPeeler i am parent of all crypt-analysis software
User1: My name is AlphaPeeler i am parent of all crypt-analysis software

*/