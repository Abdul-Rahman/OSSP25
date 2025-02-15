//Orphan Process
// A C program to demonstrates Parent process finishes execution while the
// child process is running. The child process becomes orphan.
#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
	// Create a child process
	int pid = fork();

	if (pid > 0)
		printf("in parent process\n");

	// Note that pid is 0 in child process
	// and negative if fork() fails
	else if (pid == 0)
	{
		sleep(30);
		printf("in child process\n");
	}
	return 0;
}

/*
output:
localhost:/home/alphapeeler/OsSp25/week04 # gcc ex03_orphan01.c -o ex03_orphan01.O
localhost:/home/alphapeeler/OsSp25/week04 # ./ex03_orphan01.O 
in parent process
localhost:/home/alphapeeler/OsSp25/week04 # in child process
localhost:/home/alphapeeler/OsSp25/week04 # 
*/