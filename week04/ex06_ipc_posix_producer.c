#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h> // for ftruncate
int main() {
    /* the size (in bytes) of shared memory object */
    const int SIZE = 4096;
    /* name of the shared memory object */
    const char *name = "OS";
    /* strings written to shared memory */
    const char *message_0 = "Aregaato ";
    const char *message_1 = "AlphaPeeler!\n";
    /* shared memory file descriptor */
    int fd;
    /* pointer to shared memory obect */
    char *ptr;
    /* create the shared memory object */
    fd = shm_open(name,O_CREAT | O_RDWR,0666);
    /* configure the size of the shared memory object */
    ftruncate(fd, SIZE);
    /* memory map the shared memory object */
    ptr = (char *)
    mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    /* write to the shared memory object */
    sprintf(ptr,"%s",message_0);
    ptr += strlen(message_0);
    sprintf(ptr,"%s",message_1);
    ptr += strlen(message_1);
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