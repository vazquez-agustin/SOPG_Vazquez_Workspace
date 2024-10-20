#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 1  // Tamaño del buffer para leer el archivo por bloques

// Función que aplica ROT13 a un solo carácter
char apply_rot13(char c) {
    if (c >= 'A' && c <= 'Z') {
        return (c - 'A' + 13) % 26 + 'A';
    } else if (c >= 'a' && c <= 'z') {
        return (c - 'a' + 13) % 26 + 'a';
    }
    return c;  // No es letra, devolver tal cual
}

// Función principal del programa
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s archivo\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];

    // Abrir el archivo en modo lectura/escritura
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    off_t offset = 0;

    // Leer y procesar el archivo en bloques
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        // Aplicar ROT13 a cada carácter en el buffer
        for (ssize_t i = 0; i < bytes_read; i++) {
            buffer[i] = apply_rot13(buffer[i]);
        }

        // Desplazar el puntero de archivo a la posición original
        if (lseek(fd, offset, SEEK_SET) == (off_t)-1) {
            perror("Error con lseek");
            close(fd);
            exit(EXIT_FAILURE);
        }

        // Escribir el contenido transformado en el archivo
        if (write(fd, buffer, bytes_read) != bytes_read) {
            perror("Error al escribir en el archivo");
            close(fd);
            exit(EXIT_FAILURE);
        }

        // Actualizar el desplazamiento para el próximo bloque
        offset += bytes_read;
    }

    // Verificar si hubo error en la lectura
    if (bytes_read == -1) {
        perror("Error al leer el archivo");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Cerrar el archivo
    close(fd);
    return EXIT_SUCCESS;
}

