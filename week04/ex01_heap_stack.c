/*
Heap vs Stack
*/

#include <stdio.h>
#include <stdlib.h>

void function1();
void function2();

int main() {
    //printf("Child Process (PID: %d) listing directory contents:\n", getpid());
    function1();
    function2();
    return 0;
}

void function1() {
    int x = 10;  // Stored in stack
    printf("x= %d, address of x: %p\n", x, (void*)&x);
} // x is automatically deallocated after function exits

void function2() {
    int* ptr = (int*) malloc(sizeof(int)); // Allocated on heap
    if (ptr == NULL) { // Always check if malloc succeeded
        printf("Memory allocation failed\n");
        return;
    }
    printf("Before: ptr= %p, address of ptr: %p\n", (void*)ptr, (void*)&ptr);
    *ptr = 10;
    printf("After: ptr= %p, address of ptr: %p, value at ptr: %d\n", (void*)ptr, (void*)&ptr, *ptr);
    free(ptr);  // Manual deallocation required
}

/*
output:
x= 10, address of x: 0x7fff543860dc
Before: ptr= 0x4022a6b0, address of ptr: 0x7fff543860d8
After: ptr= 0x4022a6b0, address of ptr: 0x7fff543860d8, value at ptr: 10
localhost:/home/alphapeeler/OsSp25/week04 # 
*/