/**
 * @file stop_words.c
 * @author Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison
 * @brief Funciones relacionadas con el diccionario de stop words
*/
#include "stop_words.h"

// Funciones de lista palabras

/**
 * @brief Funcion para crear una lista palabras
 * @param stopWordList Puntero a una lista de palabras si se quiere vaciar
 * @return Puntero al centinela de la lista
*/
StopWordList create_empty_stopWordList(StopWordList stopWordList)
{
    if(!is_empty_stopWordList(stopWordList)){
        delete_stopWordList(stopWordList);
    }
    StopWordList newList = (StopWordList) malloc(sizeof(struct _stopWord));
    if(newList == NULL){
        print_error(200, NULL, NULL);
    }
    newList->next = NULL;
    return newList;
}

/**
 * @brief Funcion para verificar si una lista de palabras está vacía
 * @param stopWordList Puntero a la lista de palabras
 * @return TRUE si la lista está vacía, FALSE en caso contrario
*/
bool is_empty_stopWordList(StopWordList stopWordList)
{
    return stopWordList == NULL;
}

/**
 * @brief Funcion para borrar una lista de palabras
 * @param stopWordList Puntero a la lista de palabras
*/
void delete_stopWordList(StopWordList stopWordList)
{
    if(is_empty_stopWordList(stopWordList)){
        return;
    }
    StopWordPosition aux = stopWordList->next;
    while(aux != NULL){
        delete_stopWordList_word(aux, stopWordList);
        aux = stopWordList->next;
    }
    free(stopWordList); // No se necesitan liberar adyacencias y incidencias porque no fueron alocadas en el centinela
}

/**
 * @brief Funcion para imprimir una lista de palabras por consola
 * @param stopWordList Puntero a la lista de palabras
*/
void print_stopWordList(StopWordList stopWordList)
{
    StopWordPosition P = stopWordList_first(stopWordList);

    while (P != NULL) {
        printf("%s\n", P->word);
        P = P->next;
    }
}

/**
 * @brief Funcion para buscar una palabra en una lista de palabras
 * @param stopWordList Puntero a la lista de palabras
 * @param word Palabra a buscar
 * @return Puntero al nodo encontrado, NULL en caso de no encontrarlo
*/
StopWordPosition find_stopWordList_word(StopWordList stopWordList, char *word)
{
    if(is_empty_stopWordList(stopWordList)){
        return NULL;
    }
    StopWordPosition P = stopWordList_first(stopWordList);
    while (P != NULL && strcmp(P->word, word) != 0) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Funcion para encontrar el nodo anterior a un nodo en una lista de palabras
 * @param P Nodo del que se buscara el anterior
 * @param stopWordList Puntero a la lista de palabras
 * @return Puntero al nodo anterior a @p P
*/
StopWordPosition find_stopWordList_prev_word(StopWordPosition P, StopWordList stopWordList)
{
    StopWordPosition aux = stopWordList;
    while (aux != NULL && strcmp(aux->next->word, P->word) != 0){
        aux = aux->next;
    }
    return aux;
}

/**
 * @brief Funcion para insertar un nodo en una lista de palabras
 * @param prevPosition Puntero al nodo anterior al que se desea insertar el nuevo nodo
 * @param word Palabra a insertar
 * @return Puntero al nodo insertado
*/
StopWordPosition insert_stopWordList_word(StopWordPosition prevPosition, char *word)
{
    StopWordPosition newNode = (StopWordPosition) malloc(sizeof (struct _stopWord));
    if(newNode == NULL){
        print_error(200, NULL, NULL);
    }
    newNode->next = prevPosition->next;
    prevPosition->next = newNode;
    sprintf(newNode->word, "%s", word);
    return newNode;
}

/**
 * @brief Funcion para borrar un nodo de una lista de palabras
 * @param P Puntero al nodo a borrar
 * @param stopWordList Puntero a la lista de palabras a la que pertenece @p P
*/
void delete_stopWordList_word(StopWordPosition P, StopWordList stopWordList)
{
    if(P == NULL){
        print_error(203, NULL, NULL);
    }
    StopWordPosition prevNode = find_stopWordList_prev_word(P, stopWordList);
    if(prevNode == NULL){
        print_error(301, NULL, NULL);
        return;
    }
    prevNode->next = P->next;
    free(P);
}

// Funciones de interaccion con el usuario

/**
 * @brief Funcion para obtener el primer nodo de una lista de palabras
 * @param StopWordList lista de palabras
 * @return Puntero a la primera palabra de la lista
*/
StopWordPosition stopWordList_first(StopWordList stopWordList)
{
    return stopWordList->next;
}

/**
 * @brief Funcion para obtener el ultimo nodo de una lista de palabras
 * @param StopWordList lista de palabras
 * @return Puntero a la ultima palabra de la lista
*/
StopWordPosition stopWordList_last(StopWordList stopWordList)
{
    StopWordPosition P = stopWordList->next;
    while (P->next != NULL) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Funcion para obtener la siguiente palabra de una lista de palabras
 * @param P Puntero a la palabra anterior al que se desea acceder
 * @return Puntero a la siguiente palabra de la lista
*/
StopWordPosition stopWordList_advance(StopWordPosition P)
{
    return P->next;
}

/**
 * @brief Funcion para obtener la palabra almacenada en un nodo
 * @param P Puntero al nodo del que se desea obtener la palabra
 * @return Palabra almacenada en el nodo
*/
char *get_word(StopWordPosition P)
{
    return P->word;
}

// Funciones del diccionario de stop words

/**
 * @brief Funcion para crear un diccionario de stop words
 * @param stopWordsTable Puntero a una lista de palabras si se quiere vaciar
 * @return Puntero al centinela de la lista
*/
StopWordsTable create_stopWordsTable(StopWordsTable stopWordsTable)
{
    if(stopWordsTable != NULL)
    {
        delete_stopWordsTable(stopWordsTable);
    }

    stopWordsTable = (StopWordsTable)malloc(sizeof(struct _stopHashTable) * STOP_WORDS_HASH_SIZE);

    if(!stopWordsTable){
        print_error(200,NULL,NULL);
    }

    for(int i = 0; i < STOP_WORDS_HASH_SIZE; i++)
    {
        stopWordsTable[i].wordList = create_empty_stopWordList(NULL);
        stopWordsTable[i].nodeNumber = 0;
    }

    return stopWordsTable;
}

/**
 * @brief Funcion para leer un archivo de palabras y llevarlas a un diccionario de stop words
 * @param fileName Nombre del archivo a leer
 * @param stopWordsTable Diccionario de stop words en el que se desea insertar las palabras
 * @return Diccionario de stop words con las palabras leidas del archivo
*/
StopWordsTable read_stopWord_file(char *fileName, StopWordsTable stopWordsTable)
{
    FILE* file = fopen(fileName, "r");
    char readedWord[25];

    if(file == NULL){
        print_error(100, fileName, NULL);
    }

    if(stopWordsTable == NULL){
        stopWordsTable = create_stopWordsTable(NULL);
    }

    while(fscanf(file, "%s", readedWord) != EOF){
        //printf("%s\n", readedWord);
        insert_stopWord(readedWord, stopWordsTable);
    }

    fclose(file);
    return stopWordsTable;
}

/**
 * @brief Funcion para imprimir un diccionario de stop words por consola
 * @param stopWordsTable Diccionario de stop words a imprimir
*/
void print_stopWordsTable(StopWordsTable stopWordsTable)
{
    // Impresion completa
    for(int i = 0; i < STOP_WORDS_HASH_SIZE; i++)
    {
        printf("-----------------------------\n");
        printf("Hash key: %d\n", i);
        print_stopWordList(stopWordsTable[i].wordList);
        printf("\n\n");
    }
    // Cantidad de nodos
    /* for(int i = 0; i < STOP_WORDS_HASH_SIZE; i++)
    {
        printf("%d: %d nodos\n", i, stopWordsTable[i].nodeNumber);
    } */
}

/**
 * @brief Funcion para insertar una palabra en un diccionario de stop words
 * @param word Palabra a insertar
 * @param stopWordsTable Diccionario de stop words en el que se desea insertar la palabra
*/
StopWordPosition insert_stopWord(char *word, StopWordsTable stopWordsTable)
{
    unsigned int index = jenkins_hash(word) % STOP_WORDS_HASH_SIZE;
    StopWordPosition P = insert_stopWordList_word(stopWordsTable[index].wordList, word);
    if(P!=NULL){
        stopWordsTable[index].nodeNumber++;
    }
    return P;
}

/**
 * @brief Funcion para borrar una palabra de un diccionario de stop words
 * @param word Palabra a borrar
 * @param stopWordsTable Diccionario de stop words en el que se busca la palabra @p word
*/
void delete_stopWordsTable_word(char *word, StopWordsTable stopWordsTable)
{
    int index = jenkins_hash(word) % STOP_WORDS_HASH_SIZE;
    StopWordPosition P = find_stopWordList_word(stopWordsTable[index].wordList, word);
    if(P == NULL){
        print_error(301, NULL, NULL);
        return;
    }
    delete_stopWordList_word(P, stopWordsTable[index].wordList);
    stopWordsTable[index].nodeNumber--;
}

/**
 * @brief Funcion para borrar un diccionario de stop words
 * @param stopWordsTable Diccionario de stop words a borrar
*/
void delete_stopWordsTable(StopWordsTable stopWordsTable)
{
    for(int i = 0; i < STOP_WORDS_HASH_SIZE; i++)
    {
        delete_stopWordList(stopWordsTable[i].wordList);
    }
    free(stopWordsTable);
}

/**
 * @brief Funcion para verificar si una palabra es una palabra de un diccionario de stop words
 * @param word Palabra a verificar
 * @param stopWordsTable Diccionario de stop words en el que se busca la palabra @p word
 * @return TRUE si la palabra es una palabra de diccionario de stop words, FALSE en caso contrario
*/
bool is_stopWord(char *word, StopWordsTable stopWordsTable)
{
    int index = jenkins_hash(word) % STOP_WORDS_HASH_SIZE;
    return find_stopWordList_word(stopWordsTable[index].wordList, word) != NULL;
}