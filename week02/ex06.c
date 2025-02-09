//### 3. System Calls with Structure Parameters
//These system calls use structures to pass multiple related parameters.

#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <fcntl.h>     // Include this for AT_FDCWD

int main() {
	struct stat file_info;
	// stat system call fills a structure with file information
	if (stat("test.txt", &file_info) < 0) {
		perror("stat failed");
		return 1;
	}
	printf("File size: %ld bytes\n", file_info.st_size);
	printf("Last modified: %s", ctime(&file_info.st_mtime));
	// Setting file times using structure
	struct timespec times[2];
	times[0].tv_sec = time(NULL); // Access time
	times[0].tv_nsec = 0;
	times[1].tv_sec = time(NULL); // Modify time
	times[1].tv_nsec = 0;
	if (utimensat(AT_FDCWD, "test.txt", times, 0) < 0) {
		perror("utimensat failed");
		return 1;
	}
	return 0;
}


/*

output:

File size: 198 bytes
Last modified: Sun Feb  9 05:56:09 2025

*/