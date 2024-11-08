/**
 * file hash.c
 * author Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison
 * brief Funciones de hashing
*/
#include "hash.h"

/**
 *  @brief Función de hash de Jenkins (One-at-a-time)
 *  @param key Cadena de texto a hashear
 *  @param len Longitud de la cadena a hashear
 *  @return Hash
*/
unsigned int jenkinsHash(char *key, size_t len) {
    unsigned int hash = 0;
    for (size_t i = 0; i < len; i++) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}
/**
 *  @brief Función para leer el contenido de un archivo y calcular el hash
 *  @param filename Nombre del archivo a hashear
 *  @return hash del archivo
*/
unsigned int hashFile(char *filename) {
    FILE *file = fopen(filename, "rb"); // Abrir el archivo en modo binario
    char aux[30];
    if (!file) {
        print_error(100, filename, NULL);
        exit(EXIT_FAILURE);
    }

    // Determinar el tamaño del archivo
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Leer el contenido del archivo
    char *buffer = (char*)malloc(fileSize * sizeof(char));
    if (!buffer) {
        sprintf(aux, "%lu", (fileSize * sizeof(char)));
        print_error(200, aux, NULL);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    if(fread(buffer, sizeof(char), fileSize, file) < (long unsigned int)fileSize)
    {
        print_error(101, filename, NULL);
        return 0;
    }
    fclose(file);

    // Calcular el hash del contenido
    unsigned int hash = jenkinsHash(buffer, fileSize);

    // Liberar la memoria del buffer
    free(buffer);

    return hash;
}
