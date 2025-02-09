//### 5. System Calls with Memory Management
//These system calls handle memory allocation and mapping operations.

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
        //PAGE_SIZE is only declared in the kernel headers.
        //You can get the current page size from userland 
        //using getpagesize() from unistd.h

        // Get page size
        long page_size = sysconf(_SC_PAGE_SIZE);

        printf("Pagesize is: 0x%x\n",page_size);

        // mmap system call - maps memory pages
        void *addr = mmap(NULL, page_size,
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS,
        -1, 0);
        if (addr == MAP_FAILED) {
                perror("mmap failed");
                return 1;
        }

        // Print the memory address returned by mmap
        printf("Memory mapped at address: %p\n", addr);

        // Use the mapped memory
        char *buffer = (char *)addr;

        // Print the char buffer
        printf("initial Char buffer contents : %s\n", buffer);

        sprintf(buffer, "Hello, mapped memory!");
        printf("Buffer contains: %s\n", buffer);

        // Print the char buffer
        printf("Buffer address : %p\n", buffer);

        // Print the memory address returned by mmap
        printf("Memory mapped at address: %p\n", addr);

        // munmap system call - unmap memory
        if (munmap(addr, page_size) < 0) {
                perror("munmap failed");
                return 1;
        }
        return 0;
}


/*
Output:
Pagesize is: 0x1000
Memory mapped at address: 0x7fa95b5c6000
initial Char buffer contents : 
Buffer contains: Hello, mapped memory!
Buffer address : 0x7fa95b5c6000
Memory mapped at address: 0x7fa95b5c6000

*/