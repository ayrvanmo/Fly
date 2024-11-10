/**
 * @file utilities.c
 * @author Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison
 * @brief Definiciones de funciones de micelania
*/

#include "utilities.h"

void generarCadenaAleatoria(char *string, int length) {
    const char characters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int numCaracteres = sizeof(characters) - 1;

    for (int i = 0; i < length; i++) {
        string[i] = characters[rand() % numCaracteres];
    }
    string[length] = '\0'; // Agrega el terminador de cadena
}

/**
 * @brief Función para generar palabras aleatorias
 * @note Función para debug
 * 
 * @return char* 
 */
char* generate_random_word() {
    int length = rand() % 20 + 1;
    char* word = (char*)malloc(length + 1);
    if (!word) {
        printf("Error: No se pudo asignar memoria para la palabra generada\n");
        return NULL;
    }
    for (int i = 0; i < length; i++) {
        word[i] = 'a' + rand() % 26;
    }
    word[length] = '\0';
    return word;
}