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

/**
 * @brief Funcion para convertir una cadena de caracteres a minusculas
 *
 * @param s1 Cadena de caracteres
 * @warning Esta funcion no funciona con caracteres no ASCII
*/
void to_low_case(char* s1)
{
    for(size_t i = 0; i < strlen(s1); i++)
        s1[i] = tolower(s1[i]);
}

/**
 * @brief Elimina los signos de puntuacion que acompannan una cadena de caracteres
 *
 * @param s1 Cadena de caracteres a afectar
*/
void remove_punctuation(char* s1)
{
    // Removemos caracteres iniciales
    /* if(s1[0] == '¡' || s1[0] == '¿' || s1[0] == '“'){
        // Desplazar toda la cadena un carácter a la izquierda
        for (int i = 0; s1[i] != '\0'; i++) {
            s1[i] = s1[i + 1];
        }
    } */

    // Removemos caracteres finales
    int length = strlen(s1);
    if(s1[length - 1] == '!' || s1[length - 1] == '?' || s1[length - 1] == ',' || s1[length - 1] == '.' || s1[length - 1] == ';' || s1[length - 1] == ':'){
        // Eliminamos el ultimo carácter
        s1[length - 1] = '\0';
    }
}