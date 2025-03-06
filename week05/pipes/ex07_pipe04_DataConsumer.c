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

// following is the data consumer code:

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]) {
	int data_processed;
	char buffer[BUFSIZ + 1];
	int file_descriptor;
	memset(buffer, '\0', sizeof(buffer));
	sscanf(argv[1], "%d", &file_descriptor);
	data_processed = read(file_descriptor, buffer, BUFSIZ);
	printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);
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