/**
 * @file output.c
 * @author Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison
 * @brief Funciones para manejo de entrega de datos por pantalla
*/

#include "output.h"

/**
 * @brief Muestra las coincidencias de una palabra en los archivos
 * @param indexTable Tabla de índices invertidos
 * @param asked_word Palabra a buscar
 */
void show_coincidences(ReverseIndexTable indexTable, char *asked_word)
{
    printf(CLEAR_SCREEN);
    int id_elegido;
    int count = 1;
    int auxCount = 1;
    char cadena_id_elegido[10];
    ReverseIndexList P;
    P = search_word_in_index(indexTable, asked_word);
    PositionList Q;
    Q = P->files;
    Q = Q->next;
    printf("La palabra " ANSI_COLOR_MAGENTA"%s"ANSI_COLOR_MAGENTA ANSI_COLOR_RESET " se encuentra en los siguientes archivos:\n",asked_word);
    printf("--------------------------------------------------------------------------------------------------\n");
    printf("    ID  |  Pagerank  ||  Archivo\n");
    printf("--------------------------------------------------------------------------------------------------\n");
    while(Q != NULL)
    {
        if(count == 1){
            printf(ANSI_COLOR_RED "  %4d  |  %lf  ||  %s\n"ANSI_COLOR_RED ANSI_COLOR_RESET , count,  Q->graphNode->pageRank, Q->graphNode->file->name);
        }
        else if(count == 2){
            printf(ANSI_COLOR_MAGENTA "  %4d  |  %lf  ||  %s\n"ANSI_COLOR_MAGENTA ANSI_COLOR_RESET, count,  Q->graphNode->pageRank, Q->graphNode->file->name);
        }
        else if(count == 3){
            printf(ANSI_COLOR_GREEN "  %4d  |  %lf  ||  %s\n"ANSI_COLOR_GREEN ANSI_COLOR_RESET, count,  Q->graphNode->pageRank, Q->graphNode->file->name);
        }
        else if(count == 4){
            printf(ANSI_COLOR_YELLOW "  %4d  |  %lf  ||  %s\n"ANSI_COLOR_YELLOW ANSI_COLOR_RESET, count,  Q->graphNode->pageRank, Q->graphNode->file->name);
        }
        else if(count == 5){
            printf(ANSI_COLOR_CYAN "  %4d  |  %lf  ||  %s\n"ANSI_COLOR_CYAN ANSI_COLOR_RESET, count,  Q->graphNode->pageRank, Q->graphNode->file->name);
        }
        else{
            printf("  %4d  |  %lf  ||  %s\n", count,  Q->graphNode->pageRank, Q->graphNode->file->name);
        }
        count++;
        Q = Q->next;
    }
    count--;

    do{
        auxCount = 1;
        printf("Ingrese ID del archivo el cual quiere revisar (0 para salir): ");
        if(scanf("%s", cadena_id_elegido) == 0){
            print_error(201, NULL, NULL);
            return;
        }
        id_elegido = atoi(cadena_id_elegido);

        if(id_elegido == 0){
            break;
        }

        if(id_elegido > count || id_elegido < 0){
            printf("El ID introducido no es valido, por favor intente nuevamente\n");
            continue;
        }

        Q = P->files->next;
        while(Q != NULL && auxCount < id_elegido){
            Q = Q->next;
            auxCount++;
        }
        print_file_paragraphs(Q->graphNode->file, Q->sentenceList, asked_word);

    }while(id_elegido != 0);
}

/**
 * @brief Imprime los párrafos de un archivo que contienen una palabra
 * @param file Archivo en el que se buscará
 * @param bytes Byte en el que se encuentra la palabra
 * @param asked_word Palabra buscada
 */
void print_file_paragraphs(FilePosition file, SentenceList bytes, char *asked_word)
{
    FILE *to_search_file = fopen(file->filePath, "r");
    fseek(to_search_file, 0, SEEK_END);
    char* buffer = malloc(sizeof(char) * (ftell(to_search_file) + 1));
    char* token;
    char token_aux[256];

    SentencePosition aux = bytes->next;

    printf(ANSI_COLOR_GREEN"Archivo: %s"ANSI_COLOR_RESET"\n", file->name);
    printf("=================================================================================================\n");
    while (aux != NULL)
    {
        fseek(to_search_file, aux->byte, SEEK_SET);
        if(fgets(buffer, 4096, to_search_file) == NULL){
            print_error(100, NULL, NULL);
            fclose(to_search_file);
            free(buffer);
            return;
        }
        printf("\n--------------------------------------------------------------------------------------------\n");
        char *aux_ptr;
        token = strtok_r(buffer, " \n\t", &aux_ptr);
        while(token != NULL){
            sprintf(token_aux, "%s", token);
            to_low_case(token_aux);
            remove_punctuation(token_aux);
            //printf("%s - %s\n", asked_word, token_aux);
            if(strcmp(token_aux, asked_word) == 0){
                printf(ANSI_COLOR_MAGENTA"%s "ANSI_COLOR_RESET, token);
            }
            else{
                printf("%s ", token);
            }
            token = strtok_r(NULL, " \n\t", &aux_ptr);
        }
        aux = aux->next;
    }
    printf("\n=================================================================================================\n\n\n");

    fclose(to_search_file);
    free(buffer);

}