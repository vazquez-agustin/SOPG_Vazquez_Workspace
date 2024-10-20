//PRACTICA 1

#include <stdio.h>
#include <fcntl.h>    // Para open
#include <unistd.h>   // Para lseek
#include <errno.h>    // Para errno
#include <string.h>   // Para strerror
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s archivo\n", argv[0]);
        return 1;
    }
    
    struct stat buffer;
    int status;
    
    status = stat(argv[1], &buffer);
    
    if (status == -1) {
    
        fprintf(stderr, "%s\n", strerror(errno));
    	return 1;
    }

    // Mostramos el tamaño del archivo
    printf("Tamaño del archivo '%s': %ld bytes\n", argv[1], buffer.st_size);

    return 0;
}
