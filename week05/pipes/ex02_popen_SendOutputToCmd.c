// Sending Output to an External Program
// OD -c What Octal Dump (od from the command line) does is display the 
// contents of a binary file, including an execution files, as sets of octals
// od -c : select printable characters or backslash escapes
// https://man7.org/linux/man-pages/man1/od.1.html
              
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main() {
    FILE *write_fp;
    char buffer[BUFSIZ + 1];
    sprintf(buffer, "Once upon a time, there was AlphaPeeler ...\n");
    write_fp = popen("od -c", "w");
    if (write_fp != NULL) {
        fwrite(buffer, sizeof(char), strlen(buffer), write_fp);
        pclose(write_fp);
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);
}

/*
Output:

localhost:/home/alphapeeler/OsSp25/week05 # gcc ex02_popen_SendOutputToCmd.c -o ex02_popen_SendOutputToCmd.o
localhost:/home/alphapeeler/OsSp25/week05 # ./ex02_popen_SendOutputToCmd.o 
0000000   O   n   c   e       u   p   o   n       a       t   i   m   e
0000020   ,       t   h   e   r   e       w   a   s       A   l   p   h
0000040   a   P   e   e   l   e   r       .   .   .  \n
0000054
localhost:/home/alphapeeler/OsSp25/week05 # 



From the command line, we can get the same output with the command
$ echo "Once upon a time, there was AlphaPeeler ..." | od -c

ocalhost:/home/alphapeeler/OsSp25/week05 # echo "Once upon a time, there was AlphaPeeler ..." | od -c
0000000   O   n   c   e       u   p   o   n       a       t   i   m   e
0000020   ,       t   h   e   r   e       w   a   s       A   l   p   h
0000040   a   P   e   e   l   e   r       .   .   .  \n
0000054
localhost:/home/alphapeeler/OsSp25/week05 # 


*/