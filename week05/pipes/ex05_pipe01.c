/*
The two file descriptors returned are connected in a special way. 
Any data written to file_descriptor[1] can be read back from 
file_descriptor[0]. The data is processed in a first in, first out 
basis, usually abbreviated to FIFO. This means that if you write 
the bytes A, L, P, H, A, P, E, E, L, E, R to file_descriptor[1], reading 
from file_descriptor[0] will produce A, L, P, H, A, P, E, E, L, E, R. 
This is different from a stack, which operates on a last in, first out 
basis, usually abbreviated to LIFO.
*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main() {
    int data_processed;
    int file_pipes[2];
    const char some_data[] = "AlphaPeeler";
    char buffer[BUFSIZ + 1];
    memset(buffer, '\0', sizeof(buffer));
    if (pipe(file_pipes) == 0) {
        data_processed = write(file_pipes[1], some_data, strlen(some_data));
        printf("Wrote %d bytes\n", data_processed);
        data_processed = read(file_pipes[0], buffer, BUFSIZ);
        printf("Read %d bytes: %s\n", data_processed, buffer);
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);
}

/*
localhost:/home/alphapeeler/OsSp25/week05 # gcc ex05_pipe01.c -o ex05_pipe01.o
localhost:/home/alphapeeler/OsSp25/week05 # ./ex05_pipe01.o 
Wrote 11 bytes
Read 11 bytes: AlphaPeeler
localhost:/home/alphapeeler/OsSp25/week05 # 

*/