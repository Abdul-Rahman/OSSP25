/*
Write a program that lists all files and directories in the current directory
using system calls. The program should traverse the directory structure 
recursively and print the names of all files and directories found, 
along with their respective types (file or directory). 
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

void list_directory(const char *dir_path, int depth) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    char full_path[1024];

    // Open directory
    if ((dir = opendir(dir_path)) == NULL) {
        perror("Error opening directory");
        return;
    }

    // Read directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Ignore "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Construct full path
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        // Get file status
        if (stat(full_path, &file_stat) == -1) {
            perror("Error getting file status");
            continue;
        }

        // Print indentation for better readability
        for (int i = 0; i < depth; i++) {
            printf("  ");
        }

        // Print file/directory information
        if (S_ISDIR(file_stat.st_mode)) {
            printf("[DIR]  %s\n", entry->d_name);
            // Recursive call to list subdirectories
            list_directory(full_path, depth + 1);
        } else {
            printf("[FILE] %s\n", entry->d_name);
        }
    }

    closedir(dir);  // Close directory
}

int main() {
    printf("Listing files and directories in: .\n");
    list_directory(".", 0);  // Start from the current directory
    return 0;
}


/*
localhost:/home/alphapeeler/OsSp25/week03/HomeExSet01 # ./w03ex04.o 
Listing files and directories in: .
[FILE] w03ex01.c
[FILE] w03ex01.o
[FILE] w03ex02.c
[FILE] w03ex02.o
[FILE] w03ex03.c
[FILE] w03ex03.o
[FILE] w03ex03-src.txt
[FILE] w03ex03-dest.txt
[FILE] w03ex04.c
[FILE] w03ex04.o
[DIR]  subDir
  [DIR]  alpha
    [DIR]  peeler
localhost:/home/alphapeeler/OsSp25/week03/HomeExSet01 # 

*/