#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main() {
	// Open system call - returns a file descriptor
	int fd = open("test.txt", O_RDONLY);
	if (fd < 0) {
		perror("open failed");
		return 1;
	}
	// Close system call - takes a single integer argument
	if (close(fd) < 0) {
		perror("close failed");
		return 1;
	}
	// Get process ID - no arguments
	pid_t pid = getpid();
	printf("Process ID: %d\n", pid);
	return 0;
}

/*
output
Process ID: 13574
*/