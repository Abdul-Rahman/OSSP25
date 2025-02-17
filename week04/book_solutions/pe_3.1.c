// Practice Exercises 3.1 Using the program shown in Figure 3.30, 
// explain what the output will be at LINE A.
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>  // Include this for wait()
int value = 5;
int main() {
	pid_t pid;
	pid = fork();
	if (pid == 0) { /* child process */
		value += 15;
		return 0;
	}
	else if (pid > 0) { /* parent process */
	wait(NULL);
	printf("PARENT: value = %d",value); /* LINE A */
	return 0;
	}
}

/*
Output:
PARENT: value = 5

The result is still 5, as the child updates its copy of value.When control
returns to the parent, its value remains at 5.

*/