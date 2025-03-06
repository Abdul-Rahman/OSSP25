/*
We can count the
lines in all the popen example source files by cating the files 
and then piping the output to wc -l, which counts the number of 
lines. On the command line, the equivalent command is 
$ cat ex0?_popen*.c | wc -l
*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main() {
    FILE *read_fp;
    char buffer[BUFSIZ + 1];
    int chars_read;
    memset(buffer, '\0', sizeof(buffer));
    read_fp = popen("cat ex0?_popen*.c | wc -l", "r");
    if (read_fp != NULL) {
        chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
        while (chars_read > 0) {
            buffer[chars_read - 1] = '\0';
            printf("Reading:-\n %s\n", buffer);
            chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);
        }
        pclose(read_fp);
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);
}

/*
localhost:/home/alphapeeler/OsSp25/week05 # gcc ex04_popen_word_count.c -o ex04_popen_word_count.o
localhost:/home/alphapeeler/OsSp25/week05 # ./ex04_popen_word_count.o 
Reading:-
 86
localhost:/home/alphapeeler/OsSp25/week05 # cat ex0?_popen*.c | wc -l
86
localhost:/home/alphapeeler/OsSp25/week05 # 


How It Works
The program shows that the shell is being invoked to expand popen*.c to the list of all files starting
popen and ending in .c and also to process the pipe (|) symbol and feed the output from cat into wc.
We invoke the shell, the cat program, and wc and cause an output redirection, all in a single popen call.
The program that invokes the command sees only the final output.

*/