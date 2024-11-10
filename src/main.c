#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "reverse_index.h"
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

    insert_hash(hashTable, "holiwis");
    insert_hash(hashTable, "hola");
    insert_hash(hashTable, "adios");
    insert_hash(hashTable, "hello");
    insert_hash(hashTable, "hi");
    insert_hash(hashTable, "bye");
    insert_hash(hashTable, "ciao");
    insert_hash(hashTable, "salut");
    insert_hash(hashTable, "bonjour");
    insert_hash(hashTable, "guten tag");
    insert_hash(hashTable, "buenas");

    move_word_to_front(hashTable, "hola");
    
    insert_file_to_index(hashTable, nodos[0], "buenas");
    insert_file_to_index(hashTable, nodos[1], "salut");
    insert_file_to_index(hashTable, nodos[0], "hola");
    insert_file_to_index(hashTable, nodos[3], "hola");

    print_hash_table(hashTable);
    //liberar
    delete_hash_table(hashTable);
    delete_graph(myGrpah);
}