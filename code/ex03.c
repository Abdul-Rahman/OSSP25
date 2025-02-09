//Write a C code snippet that copies a text file to a new text file. #include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#define BUFFER_SIZE 1024
int main(int argc, char *argv[]) {
	// Check if the correct number of arguments is provided
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
    // Open the source file for reading
	int src_fd = open(argv[1], O_RDONLY);
	if (src_fd == -1) {
		perror("Error opening source file");
		exit(EXIT_FAILURE);
	}
	// Open the destination file for writing (create if it doesn't exist, truncate if it does)
	int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dest_fd == -1) {
		perror("Error opening destination file");
		close(src_fd); // Close the source file descriptor
		exit(EXIT_FAILURE);
	}
	// Buffer to hold data read from the source file
	char buffer[BUFFER_SIZE];
	ssize_t bytes_read, bytes_written;
	// Copy data from source to destination
	while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
		bytes_written = write(dest_fd, buffer, bytes_read);
		if (bytes_written != bytes_read) {
			perror("Error writing to destination file");
			close(src_fd);
			close(dest_fd);
			exit(EXIT_FAILURE);
		}
	}
	// Check for read errors
	if (bytes_read == -1) {
		perror("Error reading from source file");
		close(src_fd);
		close(dest_fd);
		exit(EXIT_FAILURE);
	}
	// Close file descriptors
	close(src_fd);
	close(dest_fd);
	printf("File copied successfully from %s to %s.\n", argv[1], argv[2]);
	return 0;
}


/*
./ex03.o ex03-src.txt ex03-dest.txt

File copied successfully from ex03-src.txt to ex03-dest.txt.

*/
