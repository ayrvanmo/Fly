#include "reverse_index.h"
#include <time.h>

int main(){
    //srand(time(NULL));
    HashTable hashTable[MAX_HASH_TABLE_SIZE];

    init_hash_table(hashTable);


    insert_hash(hashTable, "adios");
    insert_hash(hashTable, "hola");
    print_hash_table(hashTable);

    /* liberar*/
    delete_hash_table(hashTable);
}