// Reading Output from an External Program
// uname: To display the name of the operating system, use the uname command.
// The popen() function opens a process by creating a pipe, forking, and invoking the shell.
// The pclose() function closes a stream that was opened by popen()
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    FILE *read_fp;
    char buffer[BUFSIZ + 1];
    int chars_read;
    memset(buffer, '\0', sizeof(buffer));
    read_fp = popen("uname -a", "r");
    if (read_fp != NULL) {
        chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
        if (chars_read > 0) {
            printf("Output was:-\n%s\n", buffer);
        }
        pclose(read_fp);
        exit(EXIT_SUCCESS);
        }
    exit(EXIT_FAILURE);
}

/*
Output:

localhost:/home/alphapeeler/OsSp25/week05 # gcc ex01_popen_ReadCmdOutput.c -o ex01_popen_ReadCmdOutput.o
localhost:/home/alphapeeler/OsSp25/week05 # ./ex01_popen_ReadCmdOutput.o 
Output was:-
Linux localhost.localdomain 6.4.0-150600.23.33-default #1 SMP PREEMPT_DYNAMIC Thu Jan  9 14:10:22 UTC 2025 (ba46628) x86_64 x86_64 x86_64 GNU/Linux

localhost:/home/alphapeeler/OsSp25/week05 # 


*/