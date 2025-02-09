//### 4. System Calls with Variable Arguments
//Some system calls can take a variable number of arguments or complex parameter combinations.


#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>  // Include this for close()

// See details here : https://man7.org/linux/man-pages/man2/fcntl.2.html

int main() {
	// fcntl can take different numbers and types of arguments
	// depending on the command
	int fd = open("test.txt", O_RDWR); // O_RDWR : Open for reading and writing
	if (fd < 0) {
		perror("open failed");
		return 1;
	}
	// Retrieve the current file flags using fcntl() system call
	int flags = fcntl(fd, F_GETFL);  // F_GETFL: Get file status flags
	if (flags < 0) { //Check flag < 0 for error
		perror("fcntl F_GETFL failed");
		close(fd);
		return 1;
	}
	// Modify the file status flags to enable "Append Mode" (O_APPEND)
    // fcntl() is used to set new file flags
		if (fcntl(fd, F_SETFL, flags | O_APPEND) < 0) { // F_SETFL: Set file status flags
		perror("fcntl F_SETFL failed");
		close(fd);
		return 1;
	}
	close(fd);
	return 0;
}

/*
No output just get and set file status flags.
*/