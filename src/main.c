#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "reverse_index.h"
#include "files.h"
#include "stop_words.h"
#include "graph.h"
#include "utilities.h"

#define MAX 5

int main(){
     // Prueba de indice invertido
    /* srand(time(NULL));
    ReverseIndexTable hashTable=init_hash_table(); */

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
    delete_hash_table(hashTable);
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

    FileList archivos = get_files_from_directory("./build/docs", NULL);
    StopWordsTable stopWords = read_stopWord_file("./build/spanish.txt", NULL);
    ReverseIndexTable reverseIndex = init_hash_table();
    Graph graph = create_graph(NULL);

    FilePosition P = archivos->Next;
    while(P != NULL){
        printf(ANSI_COLOR_BLUE"Archivo: %s\n"ANSI_COLOR_RESET, P->Element.name);
        process_file(P, graph, reverseIndex, stopWords);
        P = P->Next;
    }

    print_hash_table(reverseIndex);

        while(1)
    {
        char word[50];
        printf("Ingrese una palabra: ");
        scanf("%s", word);
        if(strcmp(word, "exit") == 0){
            break;
        }
        if(is_stopWord(word, stopWords)){
            printf("Palabra %s es un stop word\n", word);
        }
        else{
            ReverseIndexList aux = search_hash(reverseIndex, word);
            if(aux != NULL){
                print_linkList(aux->files);
            }
        }
    }

    delete_stopWordsTable(stopWords);
    delete_hash_table(reverseIndex);
    delete_graph(graph);
    delete_fileList(archivos);

    return 0;
}