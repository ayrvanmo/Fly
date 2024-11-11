#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "reverse_index.h"
#include "stop_words.h"
#include "graph.h"
#include "utilities.h"

int main(){
    
     // Prueba de indice invertido
    srand(time(NULL));
    ReverseIndexTable hashTable=init_hash_table();

    // Prueba de grafo

    GraphPosition nodos[5];

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



     // Prueba de stop words
    // char word[25];

    // StopWordsTable stopWords = read_stopWord_file("./spanish.txt", NULL);

    // printf("exit para salir\n");
    // while(1)
    // {
    //     printf("Ingrese una palabra: ");
    //     scanf("%s", word);
    //     if(strcmp(word, "exit") == 0){
    //         break;
    //     }
    //     if(is_stopWord(word, stopWords)){
    //         printf("Palabra %s es un stop word\n", word);
    //     }
    //     else{
    //         printf("Palabra %s no es un stop word\n", word);
    //     }
    // }

    // delete_stopWordsTable(stopWords);
    return 0;
}