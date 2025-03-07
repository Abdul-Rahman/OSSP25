#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define NUM_THREADS 5
void *PrintHello(void *threadid) {
	long tid;
	tid = (long) threadid;
	printf("Hello World! It's me, thread #%ld!\n", tid);
	pthread_exit(NULL);
}
int main (int argc, char *argv[]) {
	pthread_t threads[NUM_THREADS];
	int rc; long t;
	for(t=0; t<NUM_THREADS; t++){
		printf("In main: creating thread %ld\n", t);
		rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}
	/* Last thing that main() should do */
	pthread_exit(NULL);
}
/*
localhost:/home/alphapeeler/OsSp25/week07 # gcc ex02_pthread.c -o ex02_pthread.o -lpthread
localhost:/home/alphapeeler/OsSp25/week07 # ./ex02_pthread.o 
In main: creating thread 0
In main: creating thread 1
In main: creating thread 2
In main: creating thread 3
In main: creating thread 4
Hello World! It's me, thread #3!
Hello World! It's me, thread #4!
Hello World! It's me, thread #2!
Hello World! It's me, thread #1!
Hello World! It's me, thread #0!
localhost:/home/alphapeeler/OsSp25/week07 # ^C
*/