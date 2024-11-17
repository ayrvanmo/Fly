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

#define MAX 5

int main(int argc, char **argv){

    char* root_dir=get_terminal_parameters(argc, argv);
    // Obtener los parametros de la terminal
    if(!root_dir){
        return -1;
    }
    printf("Directorio: %s\n", root_dir);

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
        printf("Archivo: %s\n", P->name);
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
            LinkList toProcess = aux->files;
            toProcess->next = mergeSort_linkList(toProcess->next);
            //printf("Lista de archivos para la palabra %s:\n", aux->word);
            //print_linkList(toProcess);
            aux=aux->next;
        }
    }
    end_timer(&timer);
    sleep(1);
    printf(CLEAR_SCREEN);

    // Interaccion con el usuario
    while(1)
    {
        printf("\n\n\tIngrese una palabra: ");
        char word[500];
        if(scanf("%s", word) != 1)
        {
            printf("Error: No se pudo leer la palabra\n");
            break;
        }

        to_low_case(word);
        remove_punctuation(word);

        if(strcmp(word, "exit") == 0){
            break;
        }

        if(is_stopWord(word, stop_words)){
            printf("Palabra %s es un stop word\n", word);
            continue;
        }

        ReverseIndexList search = search_word_in_index(reverse_index, word);
        if(search == NULL){
            printf("Palabra %s no encontrada\n", word);
            continue;
        }

        LinkList files = search->files->next;
        while(files != NULL){
            printf("Archivo: %s - %lf\n", files->graphNode->file->name, files->graphNode->pageRank);
            files = files->next;
        }
    }


    delete_stopWordsTable(stop_words);
    delete_indexTable(reverse_index);
    delete_graph(graph);
    delete_fileList(files);

    return 0;
}