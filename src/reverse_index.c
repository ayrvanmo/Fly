/**
 * @file reverse_index.c
 * @author Franco Aguilar, Milton Hernández, Iván Mansilla, Ayrton Morrison
 * @brief Funciones de índice invertido
 */

#include "reverse_index.h"

/**
 * @brief Función para inicializar una lista de palabras vacia
 *
 * @return ReverseIndexList
 */
ReverseIndexList init_empty_hashList(){
    ReverseIndexList newList = malloc(sizeof(ReverseIndexNode));
    if(!newList){
        print_error(200,NULL,NULL);
    }
    newList->next = NULL;
    newList->word = NULL;
    newList->files = 0;
    return newList;
}

/**
 * @brief Función que inicializa una tabla hash
 *
 * @param hashTable Tabla hash a inicializar
 * @return ReverseIndexTable
 */
ReverseIndexTable init_hash_table(){
    ReverseIndexTable hashTable = malloc(sizeof(struct _ReverseIndexTable)*MAX_HASH_TABLE_SIZE);
    if(!hashTable){
        print_error(200,NULL,NULL);
    }
    /* inicializar la tabla hash */
    for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++){
        hashTable[i].wordList = init_empty_hashList();
        hashTable[i].wordNumber = 0;
    }
    return hashTable;
}

/**
 * @brief Inserta una palabra en una tabla hash
 *
 * @param hashTable Tabla hash a insertar la palabra
 * @param word Palabra a insertar
 *
 * @note Se inserta la palabra al inicio de la lista
 */
void insert_hash(ReverseIndexTable hashTable, char* word){

    if(!hashTable){
        print_error(302,NULL,NULL);
        return;
    }

    /* se obtiene el hash correspondiente a la palabra a insertar*/
    unsigned int hash = jenkins_hash(word) % MAX_HASH_TABLE_SIZE;

    ReverseIndexList tmpCell;

    tmpCell = (ReverseIndexList)malloc(sizeof(ReverseIndexNode));
    if(!tmpCell){
        print_error(200,NULL,NULL);
    }

    tmpCell->word = malloc(strlen(word) + 1);
    if (!tmpCell->word) {
        print_error(200,NULL,NULL);
    }
    strcpy(tmpCell->word, word);

    tmpCell->files=create_empty_linkList(NULL);
    tmpCell->fileNumbers = 0;

    tmpCell->next = hashTable[hash].wordList->next;
    hashTable[hash].wordList->next = tmpCell;

    hashTable[hash].wordNumber++;
}

/**
 * @brief Imprime la tabla hash
 *
 * @param hashTable Tabla hash
 * @note Ignora los hash que tengan su lista de palabras vacía
 */
void print_hash_table(ReverseIndexTable hashTable){

    if(!hashTable){
        print_error(302,NULL,NULL);
        return;
    }

    for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++){
        int j=1;
        if(hashTable[i].wordNumber == 0){
            continue;
        }

        ReverseIndexList aux = hashTable[i].wordList->next;
        printf("[HASH %u] - CANTIDAD PALABRAS: %d\n", i,hashTable[i].wordNumber);
        while(aux){
            printf("   %d. %s [archivos: %d]\n",j, aux->word, aux->fileNumbers);
            print_linkList(aux->files);
            j++;
            aux = aux->next;
        }
    }
}

/**
 * @brief Función para buscar una palabra en una tabla hash
 *
 * @param hashTable Tabla hash
 * @param word Palabra a buscar
 *
 * @return ReverseIndexList
 */
ReverseIndexList search_hash(ReverseIndexTable hashTable, char* word){

    if(!hashTable){
        print_error(302,NULL,NULL);
        return NULL;
    }

    unsigned int hash = jenkins_hash(word) % MAX_HASH_TABLE_SIZE;

    ReverseIndexList aux = hashTable[hash].wordList->next;
    while(aux != NULL){
        if(strcmp(aux->word, word) == 0){
            printf("La palabra %s se encuentra en el hash key %u\n", word, hash);
            return aux;
        }
        aux=aux->next;
    }
    printf("La palabra %s no se encuentra en ningún hash key\n", word);
    return NULL;
}

/**
 * @brief Encuentra palabra anterior en una lista de palabras asociadas a un hash key
 *
 * @param hashTable Tabla hash
 * @param word Palabra a buscar su anterior
 * @return ReverseIndexList
 */
ReverseIndexList find_previous_hash(ReverseIndexTable hashTable, char* word){

    unsigned int hash = jenkins_hash(word) % MAX_HASH_TABLE_SIZE;

    ReverseIndexList aux = hashTable[hash].wordList;
    while(aux){
        if(strcmp(aux->next->word, word) == 0){
            return aux;
        }
        aux = aux->next;
    }
    printf("La palabra %s no se encuentra en la lista de palabras asociadas al hash key\n", word);
    return NULL;
}

/**
 * @brief Elimina una palabra de la tabla hash
 *
 * @param hashTable Tabla hash
 * @param word Palabra a eliminar
 */
void delete_hash(ReverseIndexTable hashTable, char* word){
    if(!hashTable){
        print_error(302,NULL,NULL);
        return;
    }

    unsigned int hash = jenkins_hash(word) % MAX_HASH_TABLE_SIZE;

    ReverseIndexList aux = find_previous_hash(hashTable, word);
    if(aux == NULL){
        return;
    }
    ReverseIndexList tmp = aux->next;
    aux->next = tmp->next;
    free(tmp->word);
    free(tmp);
    hashTable[hash].wordNumber--;
}

/**
 * @brief Libera memoria de la tabla hash en su totalidad
 *
 * @param hashTable Tabla hash a liberar memoria
 */
void delete_hash_table(ReverseIndexTable hashTable){
    for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++){
        ReverseIndexList aux = hashTable[i].wordList->next;
        while(aux != NULL){
            ReverseIndexList tmp = aux->next;
            free(aux->word);
            delete_linkList(aux->files);
            free(aux);
            aux = tmp;
        }
        free(hashTable[i].wordList);
        hashTable[i].wordList = NULL;
        hashTable[i].wordNumber = 0;
    }
    free(hashTable);
}

/**
 * @brief Mueve una palabra a la primera posición de su lista asociada al hash key
 *
 * @param hashTable
 * @param word
 */
void move_word_to_front(ReverseIndexTable hashTable, char* word){
    if(!hashTable){
        print_error(302,NULL,NULL);
        return;
    }
    unsigned int hash = jenkins_hash(word) % MAX_HASH_TABLE_SIZE;
    ReverseIndexList aux = find_previous_hash(hashTable, word);
    if(!aux){
        printf("La palabra %s no se encuentra en la tabla hash\n", word);
        return;
    }
    else if(aux == hashTable[hash].wordList){
        return;
    }
    ReverseIndexList tmp = aux->next;
    aux->next = tmp->next;
    tmp->next = hashTable[hash].wordList->next;
    hashTable[hash].wordList->next = tmp;
}

/**
 * @brief Inserta un archivo en el índice invertido
 *
 * @param hashTable
 * @param file
 * @param word
 */
void insert_file_to_index(ReverseIndexTable hashTable, PtrToGraphNode file, char* word){
    if(!hashTable){
        print_error(302,NULL,NULL);
        return;
    }

    ReverseIndexList search = search_hash(hashTable, word);
    if(search==NULL){;
        insert_hash(hashTable, word);
        search = search_hash(hashTable, word);
    }

    if(find_linkList_node(search->files, *file)){
        printf("El archivo '%s' ya se encuentra en la lista de archivos asociados a la palabra '%s'\n", file->file->Element.name, word);
    }
    else{
        insert_linkList_node(search->files, file, 0);
        search->fileNumbers++;
    }

    return;
}







