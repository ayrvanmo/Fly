/**
 * @file utilities.c
 * @author Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison
 * @brief Definiciones de funciones de miscelania
*/

#include "utilities.h"


/**
 * @brief Funcion para obtener los parametros de la terminal. Devuelve el directorio en donde se ejecutara el programa
 * @param argc Cantidad de argumentos
 * @param argv Argumentos
 * @return char* Directorio en donde se ejecutara el programa
 * @note Devuelve NULL si no se quiere/puede ejecutar el programa según lo dado
 */
char* get_terminal_parameters(int argc, char **argv){
    int opt; // Variable para el manejo de opciones
	int opt_index = 0;

    // estructura para las opciones
	static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"directory", required_argument, 0, 'd'},
        {0, 0, 0, 0}
    };

    while((opt = getopt_long(argc, argv, ":hd:", long_options, &opt_index)) != -1){

		switch(opt){
			case 'h':
				printf("fly -d <directorio>      Ejecuta el programa sobre un directorio\n");
				return NULL;
                break;
			case 'd':
                return optarg;
                break;
			case ':':
                printf("Uso: 'fly -d <directorio>'\n'fly -h' para mostrar ayuda\n");
				return NULL;
				break;
			default:
				printf("Uso: 'fly -d <directorio>'\n'fly -h' para mostrar ayuda\n");
                return NULL;
				break;
		}
	}
    printf("Uso: 'fly -d <directorio>'\n'fly -h' para mostrar ayuda\n");
    return NULL;
}

/**
 * @brief Funcion para convertir una cadena de caracteres a minusculas
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
 * @param file Nombre del archivo
 * @return Nombre del archivo sin extension
 * @warning Esta funcion retorna un puntero con memoria reservada, debe liberarse fuera de esta funcion
*/
char* get_only_fileName(char* file){
    size_t originalLength = strlen(file);
    // Creamos una copia de la cadena para preservar el original
    char* name = malloc(sizeof(char) * (originalLength + 1));
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
    //printf("aqui toy\n");

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
        else{
            free(name);
            return NULL;
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