//gcc 7.4.0

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>  // Include this for wait()

int main() {
  pid_t pid;  

  /* fork a child process */
  pid = fork();

  if (pid<0) {  /*error occured*/
      fprintf(stderr, "fork failed");
      return 1;
  } else if (pid==0) { /*child process*/
    execlp("/usr/bin/ls", "ls", NULL);
  } else { /*child process*/
      
      /*parent waiting for the child process to complete*/
      wait(NULL);
      printf("child complete");
  }
  return 0;
}

/*
output: 
child complete
*/