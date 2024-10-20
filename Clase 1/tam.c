//PRACTICA 1

#include <stdio.h>
#include <fcntl.h>    // Para open
#include <unistd.h>   // Para lseek
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

    // Usamos lseek para movernos al final del archivo y obtener su tamaño
    off_t tamano = lseek(fd, 0, SEEK_END);
    if (tamano == -1) {
        fprintf(stderr, "Error al obtener el tamaño del archivo '%s': %s\n", nombre_archivo, strerror(errno));
        close(fd);
        return 1;
    }

    // Mostramos el tamaño del archivo
    printf("Tamaño del archivo '%s': %ld bytes\n", nombre_archivo, (long)tamano);

    // Cerramos el archivo
    close(fd);

    return 0;
}

