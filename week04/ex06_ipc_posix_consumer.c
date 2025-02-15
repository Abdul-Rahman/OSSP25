#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
int main() {
    /* the size (in bytes) of shared memory object */
    const int SIZE = 4096;
    /* name of the shared memory object */
    const char *name = "OS";
    /* shared memory file descriptor */
    int fd;
    /* pointer to shared memory obect */
    char *ptr;
    /* open the shared memory object */
    fd = shm_open(name, O_RDONLY, 0666);
    /* memory map the shared memory object */

    // ptr = (char *) mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); // Book code gives Segmentation fault (core dumped)
    // because mmap(), book used PROT_READ | PROT_WRITE, which tries to map it as writable.
    // This results in a segmentation fault since the shared memory was opened as read-only.

    ptr = (char *) mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0); //alphapeeler fix the book source code
    /* read from the shared memory object */
    printf("%s",(char *)ptr);
    /* remove the shared memory object */
    shm_unlink(name);
    return 0;
}

/*
output:
localhost:/home/alphapeeler/OsSp25/week04 # gcc ex06_ipc_posix_producer.c -o ex06_ipc_posix_producer.o
localhost:/home/alphapeeler/OsSp25/week04 # gcc ex06_ipc_posix_consumer.c -o ex06_ipc_posix_consumer.o
localhost:/home/alphapeeler/OsSp25/week04 # ./ex06_ipc_posix_producer.o 
localhost:/home/alphapeeler/OsSp25/week04 # ./ex06_ipc_posix_consumer.o 
Aregaato AlphaPeeler!
localhost:/home/alphapeeler/OsSp25/week04 # 

*/