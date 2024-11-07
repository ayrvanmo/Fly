/**
 * @file reverse_index.c
 * @author Franco Aguilar, Milton Hernández, Iván Mansilla, Ayrton Morrison
 * @brief Funciones de índice invertido
 */

#include "reverse_index.h"


/**
 * @brief Función que calcula el hash de un string usando el algoritmo de Jenkins
 * @param key Palabra a calcular el hash
 * @return Devuelve el hash
 */
unsigned int jenkins_hash(char* key)
{
   unsigned int hash = 0;

   while (*key){
      hash += (unsigned char)(*key);
      hash += (hash << 10);     
      hash ^= (hash >> 6);
       
      key++;
   }

   hash += (hash << 3);
   hash ^= (hash >> 11);
   hash += (hash << 15);
   
   return hash;
}

/**
 * @brief Función que inicializa una tabla hash
 * 
 * @param hashTable Tabla hash a inicializar
 */
void init_hash_table(HashTable hashTable[MAX_HASH_TABLE_SIZE]){
    for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++){
        hashTable[i].wordList = malloc(sizeof(HashList));
        if(!hashTable[i].wordList){
            print_error(200,NULL,NULL);
        }
        hashTable[i].wordList->next = NULL;
        hashTable[i].wordList->word = NULL;
        hashTable[i].wordList->files = 0;
        hashTable[i].wordNumber = 0;
    }
}

/**
 * @brief Inserta una palabra en una tabla hash
 * 
 * @param hashTable Tabla hash a insertar la palabra
 * @param word Palabra a insertar
 * 
 * @note La inserción es al final de la lista
 */
void insert_hash(HashTable hashTable[MAX_HASH_TABLE_SIZE], char* word){

    if(!hashTable){
        print_error(302,NULL,NULL);
        return;
    }

    /* se obtiene el hash correspondiente a la palabra a insertar*/
    unsigned int hash = jenkins_hash(word) % MAX_HASH_TABLE_SIZE;

    HashList* tmpCell = hashTable[hash].wordList;
    
    while(tmpCell->next != NULL){
         tmpCell = tmpCell->next;
    }
    tmpCell->next = (HashList*)malloc(sizeof(HashList));
    if(!tmpCell->next){
        print_error(200,NULL,NULL);
    }
    tmpCell = tmpCell->next;
    
    tmpCell->word = malloc(strlen(word) + 1);
    if (!tmpCell->word) {
        print_error(200,NULL,NULL);
    }

    strcpy(tmpCell->word, word);
    create_empty_linkList(tmpCell->files);
    tmpCell->next = NULL;
    
    hashTable[hash].wordNumber++;
}

/**
 * @brief Imprime la tabla hash
 * 
 * @param hashTable Tabla hash
 * @note Ignora los hash que tengan su lista de palabras vacía
 */
void print_hash_table(HashTable hashTable[MAX_HASH_TABLE_SIZE]){

    if(!hashTable){
        print_error(302,NULL,NULL);
        return;
    }

    for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++){
        int j=1;
        if(hashTable[i].wordNumber == 0){
            continue;
        }
        HashList *aux = hashTable[i].wordList->next;
        printf("[HASH %u] - CANTIDAD PALABRAS: %d\n", i,hashTable[i].wordNumber);
        while(aux){
            printf("   %d. %s\n",j, aux->word);
            j++;
            aux = aux->next;
        }
    }
}

/**
 * @brief Función para generar palabras aleatorias
 * @note Función para debug
 * 
 * @return char* 
 */
char* generate_random_word() {
    int length = rand() % 20 + 1;
    char* word = (char*)malloc(length + 1);
    if (!word) {
        printf("Error: No se pudo asignar memoria para la palabra generada\n");
        return NULL;
    }
    for (int i = 0; i < length; i++) {
        word[i] = 'a' + rand() % 26;
    }
    word[length] = '\0';
    return word;
}

/**
 * @brief Función para buscar una palabra en una tabla hash
 * 
 * @param hashTable Tabla hash
 * @param word Palabra a buscar
 * 
 * @return Posición de la palabra en la lista asociada al hash key
 */
HashList* search_hash(HashTable hashTable[MAX_HASH_TABLE_SIZE], char* word){

    if(!hashTable){
        print_error(302,NULL,NULL);
        return NULL;
    }

    unsigned int hash = jenkins_hash(word) % MAX_HASH_TABLE_SIZE;

    HashList *aux = hashTable[hash].wordList->next;
    while(aux != NULL){
        if(strcmp(aux->word, word) == 0){
            printf("La palabra %s se encuentra en el hash key %u\n", word, hash);
            return aux;
        }
        aux = aux->next;
    }
    printf("La palabra %s no se encuentra en ningún hash key\n", word);
    return NULL;
}

/**
 * @brief Encuentra palabra anterior en una lista de palabras asociadas a un hash key
 * 
 * @param hashTable Tabla hash
 * @param word Palabra a buscar su anterior
 * @return HashList* 
 */
HashList* find_previous_hash(HashTable hashTable, char* word){

    HashList *aux = hashTable.wordList;
    while(aux != NULL){
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
void delete_hash(HashTable hashTable[MAX_HASH_TABLE_SIZE], char* word){
    if(!hashTable){
        print_error(302,NULL,NULL);
        return;
    }

    unsigned int hash = jenkins_hash(word) % MAX_HASH_TABLE_SIZE;

    HashList *aux = find_previous_hash(hashTable[hash], word);
    if(aux == NULL){
        return;
    }
    HashList *tmp = aux->next;
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
void delete_hash_table(HashTable hashTable[MAX_HASH_TABLE_SIZE]){
    for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++){
        HashList *aux = hashTable[i].wordList->next;
        while(aux != NULL){
            HashList *tmp = aux->next;
            free(aux->word);
            free(aux);
            aux = tmp;
        }
        free(hashTable[i].wordList);
        hashTable[i].wordList = NULL;
        hashTable[i].wordNumber = 0;
    }
}







