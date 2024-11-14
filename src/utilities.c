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

/**
 * @brief conserva solo el nombre del archivo sin extension
 *
 * @param file Nombre del archivo
 *
 * @return Nombre del archivo sin extension
 * @warning Esta funcion retorna un puntero con memoria reservada, debe liberarse fuera de esta funcion
*/
char* get_only_fileName(char* file){
    size_t originalLength = strlen(file);
    // Creamos una copia de la cadena para preservar el original
    char* name = malloc(sizeof(char) * (originalLength - 1));
    if(name == NULL){
        print_error(200,NULL,NULL);
    }

    // Guardamos en name solamente el contenido despues de la barra '/'
    char* barPosition = strrchr(file, '/');
    if(barPosition != NULL){
        strcpy(name, barPosition + 1);
    }
    else{
        strcpy(name, file);
    }

    // Eliminar el contenido después del primer '|', si existe
    char* pipe_pos = strchr(name, '|');
    if (pipe_pos) {
        *pipe_pos = '\0';
    }

    // Eliminar el contenido después del primer '#', si existe
    char* hashtag_pos = strchr(name, '#');
    if (hashtag_pos) {
        *hashtag_pos = '\0';
    }

    // Encontrar la última aparición de '.' en filename
    char* dot_pos = strrchr(name, '.');

    // Si encontramos un punto, lo analizamos
    if (dot_pos && dot_pos != name && dot_pos[1] != '\0') {
        // Verificar si el texto después del punto es una extensión
        if (is_valid_extension(dot_pos + 1)) {
            *dot_pos = '\0'; // Truncamos en el punto para eliminar la extensión
        }
    }

    return name;
}

/**
 * @brief Comprueba si una cadena corresponde a una extension de archivo conocida por el programa
 * @param extension Cadena de caracteres a evaluar
 * @return TRUE si la extensión es valida, FALSE en caso contrario
*/
bool is_valid_extension(char* extension)
{
    const char* valid_extensions[] = {"txt", "md", "log", "conf", "ini", "cfg", "yaml", "yml", "json", "xml", "csv", "tsv", "sh", "bash", "zsh", "php", "py", "js", "html", "css", "cpp", "c", "h", "java", "sql", "r", "pl", "rb", "go", "rs"};
    size_t extensionNumber = 30;

    for (size_t i = 0; i < extensionNumber; i++) {
        if (strcmp(extension, valid_extensions[i]) == 0) {
            return true;
        }
    }
    return false;
}
/**
 * @brief Funcion para comparar si un valor es mayor o igual a otro
 * @param a Primer valor
 * @param b Segundo valor
 * @return TRUE si @p a es mayor o igual a @p b, FALSE en caso contrario
*/
bool increasing(double a, double b){
    return a <= b;
}

/**
 * @brief Funcion para comparar si un valor es menor o igual a otro
 * @param a Primer valor
 * @param b Segundo valor
 * @return TRUE si @p a es menor o igual a @p b, FALSE en caso contrario
*/
bool decreasing(double a, double b){
    return a >= b;
}