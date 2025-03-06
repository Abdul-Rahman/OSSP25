/*
Parent and Child Processes
The next logical step in our investigation of the pipe call is to allow
the child process to be a different program from its parent, rather than
just a different process running the same program. We do this using the
exec call. One difficulty is that the new execed process needs to know
which file descriptor to access. We can get around this by passing the
file descriptor (which is, after all, just a number) as a parameter to
the newly execed program.

To show how this works, we need two programs. The first is the data producer.
It creates the pipe and then invokes the child, the data consumer.
*/

// following is the data producer code:

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
		if (fork_result == (pid_t)-1) {
			fprintf(stderr, "Fork failure");
			exit(EXIT_FAILURE);
		}
		if (fork_result == 0) {
			sprintf(buffer, "%d", file_pipes[0]);
			(void)execl("ex07_pipe04_DataConsumer.o", "ex07_pipe04_DataConsumer.o", buffer, (char *)0);
			exit(EXIT_FAILURE);
		} else {
			data_processed = write(file_pipes[1], some_data,
			strlen(some_data));
			printf("%d - wrote %d bytes\n", getpid(), data_processed);
		}
	}
	exit(EXIT_SUCCESS);
}



/*
Run following command after compiling both consumer and producer:

localhost:/home/alphapeeler/OsSp25/week05 # gcc ex07_pipe03_DataProducer.c -o ex07_pipe03_DataProducer.o
localhost:/home/alphapeeler/OsSp25/week05 # gcc ex07_pipe04_DataConsumer.c -o ex07_pipe04_DataConsumer.o

localhost:/home/alphapeeler/OsSp25/week05 # ./ex07_pipe03_DataProducer.o 
1996 - wrote 11 bytes
1997 - read 11 bytes: AlphaPeeler
localhost:/home/alphapeeler/OsSp25/week05 # 

*/