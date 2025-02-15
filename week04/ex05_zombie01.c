// A C program to demonstrate Zombie Process. Child becomes Zombie as parent is sleeping
// when child process exits.
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
	// Fork returns process id
	// in parent process
	pid_t child_pid = fork();

	// Parent process
	if (child_pid > 0)
		sleep(50);

	// Child process
	else
		exit(0);
	return 0;
}

/*
output:

localhost:/home/alphapeeler/OsSp25/week04 # gcc ex05_zombie01.c -o ex05_zombie01.o
localhost:/home/alphapeeler/OsSp25/week04 # ./ex05_zombie01.o 
localhost:/home/alphapeeler/OsSp25/week04 # ./ex05_zombie01.o 
localhost:/home/alphapeeler/OsSp25/week04 # 

Now open a new terminal and issue commands:

alphapeeler@localhost:~> ps -ax | grep ex05
 5287 ?        Sl     0:00 /usr/bin/kate -b /home/alphapeeler/OsSp25/week04/ex05_zombie01.c
 5361 pts/1    S+     0:00 ./ex05_zombie01.o
 5362 pts/1    Z+     0:00 [ex05_zombie01.o] <defunct>
 5367 pts/2    S+     0:00 grep --color=auto ex05

// Here you can see for 50 seconds process is in Zombie state Z+ <defunct>
//Now after 50 seconds issue this command again:
alphapeeler@localhost:~> ps -ax | grep ex05
 5287 ?        Sl     0:00 /usr/bin/kate -b /home/alphapeeler/OsSp25/week04/ex05_zombie01.c
 5381 pts/2    S+     0:00 grep --color=auto ex05
alphapeeler@localhost:~> 
// Zombie is gone. 
*/