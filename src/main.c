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
    printf("Creando grafo\n");
    Graph myGrpah = create_graph(NULL);
    printf("Grafo creado\n");

    for (int i = 0; i < 1000; i++) {
        char str[11];
        generarCadenaAleatoria(str, 10);
        insert_graphNode(str, myGrpah);
    }
    float sum =0;
    for(int i = 0; i<MAX_HASH_TABLE_SIZE; i++)
    {
        sum+=(float)myGrpah[i].nodeNumber;
    }

    print_graph(myGrpah);
        printf("Suma: %f, Promedio es %f", sum, sum/MAX_HASH_TABLE_SIZE);

    delete_graph(myGrpah);
}