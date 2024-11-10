#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "reverse_index.h"
#include "graph.h"
#include "utilities.h"

int main(){
    // Prueba de indice invertido
    /* srand(time(NULL));
    HashTable hashTable[MAX_HASH_TABLE_SIZE];

    init_hash_table(hashTable);


    insert_hash(hashTable, "adios");
    insert_hash(hashTable, "hola");
    print_hash_table(hashTable);

    //liberar
    delete_hash_table(hashTable); */

    // Prueba de grafo

    GraphPosition nodos[5];

    printf("Creando grafo\n");
    Graph myGrpah = create_graph(NULL);
    printf("Grafo creado\n");

    nodos[0] = insert_graphNode("A", myGrpah);
    nodos[1] = insert_graphNode("B", myGrpah);
    nodos[2] = insert_graphNode("C", myGrpah);
    nodos[3] = insert_graphNode("D", myGrpah);
    nodos[4] = insert_graphNode("E", myGrpah);

    print_graph(myGrpah);

    printf("------------------\n");
    printf("Key: 0\n");
    print_graphList(myGrpah[0].nodeList);
    printf("Key: 1\n");
    print_graphList(myGrpah[1].nodeList);

    printf("------------------\n");
    create_graph_edge(nodos[0], nodos[1], 1);
    create_graph_edge(nodos[0], nodos[2], 1);
    create_graph_edge(nodos[0], nodos[3], 1);
    create_graph_edge(nodos[0], nodos[4], 1);
    create_graph_edge(nodos[2], nodos[0], 1);

    printf("Imprimiendo nodo %d, %s\n", 0, nodos[0]->name);
    print_graphNode(nodos[0]);

    delete_graph(myGrpah);
}