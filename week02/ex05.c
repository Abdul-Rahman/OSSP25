#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main() {
	char buffer[1024];
	int fd = open("input.txt", O_RDONLY);
	if (fd < 0) {
	perror("open failed");
	return 1;
	}
	// Read system call - fills a user-space buffer
	ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
	if (bytes_read < 0) {
	perror("read failed");
	close(fd);
	return 1;
	}
	// Write system call - transfers data from a buffer
	ssize_t bytes_written = write(STDOUT_FILENO, buffer, bytes_read);
	if (bytes_written < 0) {
	perror("write failed");
	close(fd);
	return 1;
	}
	close(fd);
	return 0;
}

/*
Output
My name is Abdul Rahman Mahmood. My name is Abdul Rahman Mahmood.
My name is Abdul Rahman Mahmood. My name is Abdul Rahman Mahmood.
My name is Abdul Rahman Mahmood. My name is Abdul Rahman Mahmood.
/*