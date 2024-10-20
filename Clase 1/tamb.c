//PRACTICA 1

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s file1 [file2 ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
	
    
    int fd = open(argv[1], O_RDONLY);
        
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    
    off_t size;
    off_t offset = 0;
    size = lseek(fd, offset, SEEK_END);
    
    if (size == -1) {
        perror("Error reading file");
        exit(EXIT_FAILURE);
    }
    
    printf("File size is: %d \n", (int)size);
    
    if (close(fd) == -1) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}

// To compile, run the following line in LINUX terminal: 

// gcc -std=c99 -Wall -pedantic FILE_NAME.c -o FILE_NAME
