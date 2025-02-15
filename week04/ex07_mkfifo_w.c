// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    int fd;
    // FIFO file path
    char * myfifo = "/home/alphapeeler/OsSp25/week04/myfifo";
    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    mkfifo(myfifo, 0666);
    char arr1[80], arr2[80];
    while (1)
    {
        // Open FIFO for write only
        fd = open(myfifo, O_WRONLY);
        // Take an input arr2ing from user.
        // 80 is maximum length
        fgets(arr2, 80, stdin);
        // Write the input arr2ing on FIFO
        // and close it
        write(fd, arr2, strlen(arr2)+1);
        close(fd);
        // Open FIFO for Read only
        fd = open(myfifo, O_RDONLY);
        // Read from FIFO
        read(fd, arr1, sizeof(arr1));
        // Print the read message
        printf("User2: %s\n", arr1);
        close(fd);
    }
    return 0;
}


/*
output:
=======

Terminal 1 :
localhost:/home/alphapeeler/OsSp25/week04 # gcc ex07_mkfifo_w.c -o ex07_mkfifo_w.o
localhost:/home/alphapeeler/OsSp25/week04 # gcc ex07_mkfifo_r.c -o ex07_mkfifo_r.o
localhost:/home/alphapeeler/OsSp25/week04 # ./ex07_mkfifo_w.o 

//After this run another terminal window to see if mkfifo pipe has been created
//Terminal 2 :
localhost:/home/alphapeeler/OsSp25/week04 # ls -al
total 144
drwxr-xr-x 1 alphapeeler users   632 Feb 15 19:51 .
drwxr-xr-x 1 alphapeeler users    36 Feb 10 04:26 ..
-rw-r--r-- 1 alphapeeler users   844 Feb 15 18:16 ex01_heap_stack.c
-rwxr-xr-x 1 root        root  11744 Feb 15 18:16 ex01_heap_stack.o
-rw-r--r-- 1 alphapeeler users   544 Feb 10 04:28 ex02_fork01.c
-rwxr-xr-x 1 root        root  11776 Feb 15 18:23 ex02_fork01.o
-rw-r--r-- 1 alphapeeler users   482 Feb 10 04:34 ex03_orphan01.c
-rwxr-xr-x 1 root        root  11632 Feb 15 18:24 ex03_orphan01.O
-rw-r--r-- 1 alphapeeler users   854 Feb 10 05:03 ex04_orphan02.c
-rwxr-xr-x 1 root        root  11832 Feb 15 18:29 ex04_orphan02.o
-rw-r--r-- 1 alphapeeler users   373 Feb 10 04:39 ex05_zombie01.c
-rwxr-xr-x 1 root        root  11632 Feb 15 18:31 ex05_zombie01.o
-rw-r--r-- 1 alphapeeler users  1101 Feb 15 19:03 ex06_ipc_posix_consumer.c
-rwxr-xr-x 1 root        root  11688 Feb 15 19:06 ex06_ipc_posix_consumer.o
-rw-r--r-- 1 alphapeeler users  1068 Feb 15 19:06 ex06_ipc_posix_producer.c
-rwxr-xr-x 1 root        root  11752 Feb 15 19:06 ex06_ipc_posix_producer.o
-rw-r--r-- 1 alphapeeler users   908 Feb 15 19:50 ex07_mkfifo_r.c
-rwxr-xr-x 1 root        root  11920 Feb 15 19:50 ex07_mkfifo_r.o
-rw-r--r-- 1 alphapeeler users  1021 Feb 15 19:50 ex07_mkfifo_w.c
-rwxr-xr-x 1 root        root  11920 Feb 15 19:50 ex07_mkfifo_w.o
prw-r--r-- 1 root        root      0 Feb 15 19:51 myfifo
localhost:/home/alphapeeler/OsSp25/week04 #

// then run the 2nd program to start reading in Termial 2
//Termial 2
localhost:/home/alphapeeler/OsSp25/week04 # ./ex07_mkfifo_r.o 

// then switch back to Terminal 1 and write a message in Termial 1
//Termial 1
localhost:/home/alphapeeler/OsSp25/week04 # ./ex07_mkfifo_w.o 
My name is AlphaPeeler

// then switch to Termial 2 immediately to see the mesage from writing end:
//Termial 2
localhost:/home/alphapeeler/OsSp25/week04 # ./ex07_mkfifo_r.o 
User1: My name is AlphaPeeler

//Now write a message in Termial 2 so that it can be read from Terminal 1:
//Termial 2
localhost:/home/alphapeeler/OsSp25/week04 # ./ex07_mkfifo_r.o 
User1: My name is AlphaPeeler
My name is Abdul Rahman (Asst. Prof. FAST-NU)


// then switch to Termial 1 immediately to see the mesage from Terminal 2:
//Termial 1
localhost:/home/alphapeeler/OsSp25/week04 # gcc ex07_mkfifo_w.c -o ex07_mkfifo_w.o
localhost:/home/alphapeeler/OsSp25/week04 # gcc ex07_mkfifo_r.c -o ex07_mkfifo_r.o
localhost:/home/alphapeeler/OsSp25/week04 # ./ex07_mkfifo_w.o 
My name is AlphaPeeler
User2: My name is Abdul Rahman (Asst. Prof. FAST-NU)

*/
