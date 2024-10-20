//PRACTICA 2

#include <stdio.h>
#include <fcntl.h>    // Para open
#include <unistd.h>   // Para read y close
#include <errno.h>    // Para errno
#include <string.h>   // Para strerror

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s archivo\n", argv[0]);
        return 1;
    }

    const char *nombre_archivo = argv[1];

    // Abrimos el archivo en modo lectura
    int fd = open(nombre_archivo, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Error al abrir el archivo '%s': %s\n", nombre_archivo, strerror(errno));
        return 1;
    }

    unsigned char buffer;
    ssize_t bytes_leidos;

    // Leemos el archivo byte a byte
    while ((bytes_leidos = read(fd, &buffer, 1)) > 0) {
        // Si el byte no está en el rango ASCII (0-127)
        if (buffer > 127) {
            printf("El archivo '%s' no contiene solo texto ASCII.\n", nombre_archivo);
            close(fd);
            return 0;
        }
    }

    if (bytes_leidos == -1) {
        fprintf(stderr, "Error al leer el archivo '%s': %s\n", nombre_archivo, strerror(errno));
        close(fd);
        return 1;
    }

    // Si llegamos al final del archivo sin encontrar caracteres no ASCII
    printf("El archivo '%s' contiene solo texto ASCII.\n", nombre_archivo);

    // Cerramos el archivo
    close(fd);

    return 0;
}

