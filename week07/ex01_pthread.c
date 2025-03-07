#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
void *helloWorld(void *vargp) {
	sleep(1);
	printf("Hello World \n");
	return NULL;
}
int main() {
	pthread_t thread_id;
	printf("Before Thread\n");
	pthread_create(&thread_id, NULL, helloWorld, NULL);
	pthread_join(thread_id, NULL);
	printf("After Thread\n");
	exit(0);
}

/*
localhost:/home/alphapeeler/OsSp25/week07 # gcc ex01_pthread.c -o ex01_pthread.o -lpthread
localhost:/home/alphapeeler/OsSp25/week07 # ./ex01_pthread.o 
Before Thread
Hello World 
After Thread
localhost:/home/alphapeeler/OsSp25/week07 # 
*/