/*
Develop a program that copies the contents of one file into 
another file using system calls. The program should accept 
two file paths as command-line arguments: the source file 
to be copied from and the destination file to be copied to. 
Ensure proper error handling for file opening, reading, and 
writing operations. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024  // Buffer size for reading

int main(int argc, char *argv[]) {
    int src_fd, dest_fd;  
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    // Check for correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(1);
    }

    // Open source file for reading
    src_fd = open(argv[1], O_RDONLY);
    if (src_fd < 0) {
        perror("Error opening source file");
        exit(1);
    }

    // Open destination file for writing (create if it doesn't exist, truncate if it does)
    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Error opening destination file");
        close(src_fd);
        exit(1);
    }

    // Read from source and write to destination
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            close(src_fd);
            close(dest_fd);
            exit(1);
        }
    }

    // Check for read error
    if (bytes_read < 0) {
        perror("Error reading from source file");
    }

    // Close file descriptors
    close(src_fd);
    close(dest_fd);

    printf("File copied successfully from '%s' to '%s'\n", argv[1], argv[2]);
    return 0;
}



/*
output:
localhost:/home/alphapeeler/OsSp25/week03/HomeExSet01 # ./w03ex03.o w03ex03-src.txt w03ex03-dest.txt 
File copied successfully from 'w03ex03-src.txt' to 'w03ex03-dest.txt'
localhost:/home/alphapeeler/OsSp25/week03/HomeExSet01 # 
*/