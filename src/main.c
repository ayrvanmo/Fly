#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "reverse_index.h"
#include "files.h"
#include "stop_words.h"
#include "graph.h"
#include "utilities.h"
#include "page_rank.h"

#define MAX 5

int main(int argc, char **argv){

    char* root_dir=get_terminal_parameters(argc, argv);
    // Obtener los parametros de la terminal
    if(!root_dir){
        return -1;
    }
    printf("Directorio: %s\n", root_dir);


     // Prueba de indice invertido
    /* srand(time(NULL));
    ReverseIndexTable hashTable=init_indexTable(); */

    // Prueba de grafo

    /**GraphPosition nodos[5];

    Graph myGrpah = create_graph(NULL);

    nodos[0] = insert_graphNode("A", myGrpah);
    nodos[1] = insert_graphNode("B", myGrpah);
    nodos[2] = insert_graphNode("C", myGrpah);
    nodos[3] = insert_graphNode("D", myGrpah);
    nodos[4] = insert_graphNode("E", myGrpah);

    
    insert_file_to_index(hashTable, nodos[0], "buenas");
    insert_file_to_index(hashTable, nodos[1], "salut");
    insert_file_to_index(hashTable, nodos[2], "hola");
    insert_file_to_index(hashTable, nodos[3], "hola");
    insert_file_to_index(hashTable, nodos[4], "buenas");
    print_hash_table(hashTable);



    //liberar
    delete_indexTable(hashTable);
    delete_graph(myGrpah);
    */



     // Prueba de stop words
    /* char word[25];

    StopWordsTable stopWords = read_stopWord_file("./spanish.txt", NULL);

    printf("exit para salir\n");
    while(1)
    {
        printf("Ingrese una palabra: ");
        scanf("%s", word);
        if(strcmp(word, "exit") == 0){
            break;
        }
        if(is_stopWord(word, stopWords)){
            printf("Palabra %s es un stop word\n", word);
        }
        else{
            printf("Palabra %s no es un stop word\n", word);
        }
    }

    delete_stopWordsTable(stopWords);*/

    //Prueba de lista de archivos

    // FileList files = get_files_from_directory("./build/example", NULL);
    // StopWordsTable stopWords = read_stopWord_file("./build/spanish.txt", NULL);
    // ReverseIndexTable reverseIndex = init_indexTable();
    // Graph graph = create_graph(NULL);

    // FilePosition P = files->Next;

    // print_fileList(files);

    // while(P != NULL){
    //     printf(ANSI_COLOR_BLUE"Archivo: %s\n"ANSI_COLOR_RESET, P->name);
    //     process_file(P, graph, reverseIndex, stopWords, files);
    //     P = P->Next;
    // }
    // calculate_page_rank(graph);
    // print_graph(graph);

    // delete_stopWordsTable(stopWords);
    // delete_indexTable(reverseIndex);
    // delete_graph(graph);
    // delete_fileList(files);

    return 0;
}