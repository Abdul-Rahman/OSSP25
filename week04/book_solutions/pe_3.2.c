// Practice Exercises 3.2 : Including the initial parent process, 
// how many processes are created by the program shown in Figure 3.31?
/*
//Psedu code in 3.31:
int main() {
	// fork a child process
	fork();
	// fork another child process
	fork();
	// and fork another
	fork();
	return 0;
}
*/
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>  // Include this for wait()

int main() {
    printf("Process # started: PID = %d, Parent PID = %d\n", getpid(), getppid());

    // First fork
    if (fork() == 0) {
        printf("Process #: Child PID = %d, Parent PID = %d\n", getpid(), getppid());
    } else {
        wait(NULL);
    }

    // Second fork
    if (fork() == 0) {
        printf("Process #: Child PID = %d, Parent PID = %d\n", getpid(), getppid());
    } else {
        wait(NULL);
    }

    // Third fork
    if (fork() == 0) {
        printf("Process #: Child PID = %d, Parent PID = %d\n", getpid(), getppid());
    } else {
        wait(NULL);
    }

    return 0;
}
/*
Output:
//Eight processes are created.

localhost:/home/alphapeeler/OsSp25/week04/book_solutions # gcc pe_3.2.c -o pe_3.2.o
localhost:/home/alphapeeler/OsSp25/week04/book_solutions # ./pe_3.2.o 
Process # started: PID = 2420, Parent PID = 1934
Process #: Child PID = 2421, Parent PID = 2420
Process #: Child PID = 2422, Parent PID = 2421
Process #: Child PID = 2423, Parent PID = 2422
Process #: Child PID = 2424, Parent PID = 2421
Process #: Child PID = 2425, Parent PID = 2420
Process #: Child PID = 2426, Parent PID = 2425
Process #: Child PID = 2427, Parent PID = 2420
*/

