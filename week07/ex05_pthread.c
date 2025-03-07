#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> // for atoi()
int sum; /* shared data by the thread(s) */
void *runner(void *param); /* threads call this function */
int main(int argc, char *argv[]) {
	pthread_t tid; /* the thread identifier */
	pthread_attr_t attr; /* set of thread attributes */
	if (argc != 2) {
	        fprintf(stderr,"usage: a.out <integer value>\n");
	        return -1;
	}
	if (atoi(argv[1]) < 0) {
	        fprintf(stderr,"%d must be >= 0\n",atoi(argv[1]));
	        return -1;
	}
	/* get the default attributes */
	pthread_attr_init(&attr);
	/* create the thread */
	pthread_create(&tid,&attr,runner,argv[1]);
	/* wait for the thread to exit */
	pthread_join(tid,NULL);
	printf("sum = %d\n",sum);
}

/* The thread will begin control in this function */
void *runner(void *param) {
        int i, upper = atoi(param);
        sum = 0;
        for (i = 1; i <= upper; i++)
                sum += i;
        pthread_exit(0);
}

/*
localhost:/home/alphapeeler/OsSp25/week07 # gcc ex05_pthread.c -o ex05_pthread.o -lpthread
localhost:/home/alphapeeler/OsSp25/week07 # ./ex05_pthread.o 
usage: a.out <integer value>
localhost:/home/alphapeeler/OsSp25/week07 # ./ex05_pthread.o 5
sum = 15
localhost:/home/alphapeeler/OsSp25/week07 # ./ex05_pthread.o 10
sum = 55
localhost:/home/alphapeeler/OsSp25/week07 # ./ex05_pthread.o 100
sum = 5050
localhost:/home/alphapeeler/OsSp25/week07 # 
*/