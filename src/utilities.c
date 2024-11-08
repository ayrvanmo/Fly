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