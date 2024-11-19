#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "reverse_index.h"
#include "files.h"
#include "stop_words.h"
#include "graph.h"
#include "utilities.h"
#include "page_rank.h"
#include "timer.h"
#include "position_list.h"

#define MAX 5

int main(int argc, char **argv){

    char* root_dir=get_terminal_parameters(argc, argv);
    // Obtener los parametros de la terminal
    if(!root_dir){
        return 0;
    }
    Timer timer;

    // Obtener los archivos de la carpeta e inicializar variables
    Graph graph = create_graph(NULL);
    ReverseIndexTable reverse_index = init_indexTable(NULL);
    init_timer(&timer);
    printf("Listando archivos...\n");
    FileList files = get_files_from_directory(root_dir, NULL);

    printf("Leyendo stop words...\n");
    StopWordsTable stop_words = read_stopWord_file("./build/spanish.txt", NULL);

    // Procesar los archivos
    printf("Procesando archivos...\n");
    FilePosition P = files->Next;
    while(P != NULL){
        printf(ANSI_COLOR_YELLOW"Procesando archivo:"ANSI_COLOR_RESET"%s\n", P->name);
        process_file(P, graph, reverse_index, stop_words, files);
        P = P->Next;
    }

    // Calculamos el PageRank
    printf("Calculando PageRank...\n");
    calculate_page_rank(graph);

    // Ordenamos las palabras por PageRank
    printf("Ordenando palabras...\n");
    for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++){
        ReverseIndexList aux = reverse_index[i].wordList->next;
        while(aux != NULL){
            PositionList toProcess = aux->files;
            toProcess->next = mergeSort_positionList(toProcess->next);
            // printf("Lista de archivos para la palabra %s:\n", aux->word);
            // print_positionList(toProcess);
            aux=aux->next;
        }
    }
    end_timer(&timer);
    sleep(1);
    printf(CLEAR_SCREEN);
    char *token = NULL;
    char *aux_ptr;

    // Interaccion con el usuario
    while(1)
    {
        printf(CLEAR_SCREEN);
        printf("\tIngrese una palabra (exit para terminar): ");
        char word[500];

        if(fgets(word, sizeof(word), stdin) == NULL)
         {
            print_error(204,NULL,NULL);
            break;
         }

        // Remover el caracter de nueva línea
         word[strcspn(word, "\n")] = '\0';
        if(word[0] == '\0'){
            //print_error(306, NULL, NULL);
            continue;
         }

        if((token = strtok_r(word, " \t", &aux_ptr)) == NULL){
            //print_error(306, NULL, NULL);
            continue;
        }
        char *next_token = strtok_r(NULL, " \t", &aux_ptr);
        if(next_token != NULL){
            print_error(307, NULL, NULL);
            sleep(1);
            continue;
        }

        // Se reactualiza la palabra
        strcpy(word, token);
        token = NULL;

        to_low_case(word);
        remove_punctuation(word);
        if(strcmp(word, "exit") == 0){
            printf(CLEAR_SCREEN "Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison\n\n"ANSI_COLOR_CYAN);
            char frase[] = "Gracias por usar fly, nos vemos pronto... ";
            for(size_t i = 0; i < strlen(frase); i++){
                printf("\r            ");
                for(size_t j = 0; j < i; j++){
                    printf("%c", frase[j]);
                }
                fflush(stdout);
                for(double j = i; j < 90000000; j++);
            }
            printf("\n");
            break;
        }

        if(is_stopWord(word, stop_words)){
            printf("    Palabra %s es un stop word\n", word);
            sleep(1);
            fflush(stdin);
            continue;
        }

        ReverseIndexList search = search_word_in_index(reverse_index, word);
        if(search == NULL){
            printf("    Palabra %s no encontrada\n", word);
            sleep(1);
            fflush(stdin);
            continue;
        }
        else{
            show_coincidences(reverse_index, word);
        }

    }
    delete_stopWordsTable(stop_words);
    delete_indexTable(reverse_index);
    delete_graph(graph);
    delete_fileList(files);
    return 0;
}