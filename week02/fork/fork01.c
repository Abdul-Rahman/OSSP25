#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>  // Include this for exit()
int main()
{

    // make two process which run same
    // program after this instruction
    pid_t p = fork();
    if(p<0){
      perror("fork fail");
      exit(1);
    }
    printf("Hello world!, process_id(pid) = %d \n",getpid());
    return 0;
}

/*
Hello world!, process_id(pid) = 13135 
Hello world!, process_id(pid) = 13136 
*/