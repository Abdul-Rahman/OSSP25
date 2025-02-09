#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>  // Include this for exit()

void forkexample()
{
    int x = 1;
    pid_t p = fork();
      if(p<0){
      perror("fork fail");
      exit(1);
    }
    else if (p == 0)
        printf("Child has x = %d\n", ++x);
    else 
        printf("Parent has x = %d\n", --x);
}
int main()
{
    forkexample();
    return 0;
}

/*
2 possible Outputs
Parent has x = 0
Child has x = 2

Child has x = 2
Parent has x = 0

Parent process and child process are running the same program, 
but it does not mean they are identical. OS allocates different 
data and states for these two processes, and the control flow 
of these processes can be different. 

Here, global variable change in one process does not affect two 
other processes because the data/state of the two processes is 
different. And also parent and child run simultaneously so two 
outputs are possible.

/*