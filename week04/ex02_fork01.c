/*
C Program Forking Separate Process
*/
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>  // Include this for wait()
int main()
{
pid_t  pid;
	/* fork another process */
	pid = fork();
	if (pid < 0) { /* error occurred */
		fprintf(stderr, "Fork Failed");
		return 1;
	}
	else if (pid == 0) { /* child process */
		execlp("/bin/ls", "ls", NULL);
	}
	else { /* parent process */ // if pid > 0, then parent run
		/* parent will wait for the child */
		wait (NULL);
		printf ("Child Complete");
	}
	return 0;
}

/*
output:
localhost:/home/alphapeeler/OsSp25/week04 # gcc ex02_fork01.c -o ex02_fork01.o
localhost:/home/alphapeeler/OsSp25/week04 # ./ex02_fork01.o 
ex01_heap_stack.c  ex01_heap_stack.o  ex02_fork01.c  ex02_fork01.o  ex03_orphan01.c  ex04_orphan02.c  ex05_zombie01.c
Child Completelocalhost:/home/alphapeeler/OsSp25/week04 # 
*/