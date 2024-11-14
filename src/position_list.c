/**
 * file position_list.h
 * author Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison
 * brief Funciones para el manejo de una lista de posciones de palabras
*/

#include "position_list.h"

// Funciones para el manejo de la lista enlazada

/**
 * @brief Funcion para vaciar una lista de posiciones
 * @param positionList Lista de posiciones
 * @return Puntero a una lista vacia
*/
PositionList create_empty_positionList(PositionList positionList)
{
    if(!is_empty_positionList(positionList)){
        delete_positionList(positionList);
    }
    PositionList newList = (PositionList) malloc(sizeof(struct _positionListNode));
    if(newList == NULL){
        print_error(200, NULL, NULL);
    }
    newList->next = NULL;
    newList->coincidences = 0;
    newList->graphNode = NULL;
    newList->sentenceList = NULL;
    return newList;
}

/**
 * @brief Funcion para eliminar una lista de posiciones
 * @param linkList Lista de posiciones a eliminar
*/
void delete_positionList(PositionList positionList)
{
    if(is_empty_positionList(positionList)){
        return;
    }
    PositionLocation aux = positionList->next;
    while(aux != NULL){
        delete_positionList_node(aux, positionList);
        aux = positionList->next;
    }
    free(positionList);
}

/**
 * @brief Funcion para verificar si una lista de posiciones esta vacia
 * @param positionList Lista de posiciones
 * @return TRUE si la lista esta vacia, FALSE en caso contrario
*/
bool is_empty_positionList(PositionList positionList)
{
    return positionList == NULL;
}

/**
 * @brief Funcion para imprimir una lista de posiciones
 * @param positionList Lista de posiciones
*/
void print_positionList(PositionList positionList) {
    PositionLocation P = positionList_first(positionList);

    while (P != NULL) {
        printf("        Nodo: "); // COMPLETAR FUNCION
        P = P->next;
    }
}

/**
 * @brief Funcion para encontrar un nodo en una lista de posiciones
 * @param positionList Lista de posiciones dada
 * @param graphNode Nodo de grafo que se desea buscar en la lista
 * @return Puntero al nodo si se encuentra, NULL en caso contrario
*/
PositionLocation find_positionList_node(PositionList positionList, GraphNode graphNode)
{
    if(is_empty_positionList(positionList)){
        return NULL;
    }
    PositionLocation P = positionList_first(positionList);
    while (P != NULL && strcmp(P->graphNode->file->name, graphNode.file->name) != 0) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Encuentra el nodo previo a uno dado en una lista de posiciones
 * @param P Posicion dada
 * @param positionList Lista dada
 * @return PositionLocation Retorna el nodo previo
 */
PositionLocation find_positionList_prev_node(PositionLocation P, PositionList positionList)
{
    if(P == NULL){
        print_error(203, NULL, NULL);
    }
    PositionLocation prevNode = positionList;
    while (prevNode->next != P) {
        prevNode = prevNode->next;
    }
    return prevNode;
}
/**
 * @brief Inserta un nodo en una lista de posiciones
 * @param prevPosition Nodo anterior al que se desea insertar
 * @param graphNode Nodo de grafo a insertar
 * @return PositionLocation Puntero al nuevo nodo insertado
 */
PositionLocation insert_positionList_node(PositionLocation prevPosition, PtrToGraphNode graphNode)
{
    PositionLocation newNode = (PositionLocation) malloc(sizeof(struct _positionListNode));
    if(newNode == NULL){
        print_error(200, NULL, NULL);
    }

    newNode->graphNode = graphNode;
    newNode->next = prevPosition->next;
    prevPosition->next = newNode;
    newNode->sentenceList = create_empty_sentenceList(newNode->sentenceList);
    return newNode;
}

/**
 * @brief Funcion para eliminar un enlace de una lista de posiciones
 * @param P Puntero al enlace que se desea eliminar
 * @param positionList Lista de posiciones a la que pertenece @p P
*/
void delete_positionList_node(PositionLocation P, PositionList positionList)
{
    if(P == NULL){
        print_error(203, NULL, NULL);
    }
    PositionLocation prevNode = find_positionList_prev_node(P, positionList);
    if(prevNode == NULL){
        print_error(301, NULL, NULL);
        return;
    }
    delete_sentenceList(positionList->sentenceList);
    prevNode->next = P->next;
    free(P);
}


// Funciones de interaccion con el usuario

/**
 * @brief Funcion para obtener el primer enlace de una lista de posiciones
 * @param positionList Lista de posiciones
 * @return Puntero al primer enlace de la lista
*/
PositionLocation positionList_first(PositionList positionList)
{
    return positionList->next;
}

/**
 * @brief Funcion para obtener el ultimo enlace de una lista de posiciones
 * @param positionList Lista de posiciones
 * @return Puntero al ultimo enlace de la lista
*/
PositionLocation positionList_last(PositionList positionList)
{
    PositionLocation P = positionList->next;
    while (P->next != NULL) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Funcion para obtener el siguiente enlace de una lista de posiciones
 * @param P Puntero al enlace anterior al que se desea acceder
 * @return Puntero al siguiente enlace de la lista
*/
PositionLocation positionList_advance(PositionLocation P)
{
    return P->next;
}

/**
 * @brief Funcion para obtener el nodo de un grafo a partir de un enlace
 * @param P Puntero al enlace
 * @return Nodo de grafo
*/
PtrToGraphNode get_position_graphNode(PositionLocation P)
{
    if(P == NULL){
        print_error(203, NULL, NULL);
    }
    return P->graphNode;
}


// Funciones relacionadas con la lista de oraciones
/**
 * @brief Crea una lista enlazada de oraciones vacia
 * @param sentenceList Lista dada
 * @return SentenceList Retorna la lista vacia
 */
SentenceList create_empty_sentenceList(SentenceList sentenceList)
{
    if(!is_empty_sentenceList(sentenceList)){
        delete_sentenceList(sentenceList);
    }
    SentenceList newList = (SentenceList) malloc(sizeof(struct _sentenceListNode));
    if(newList == NULL){
        print_error(200, NULL, NULL);
    }
    newList->next = NULL; 
    return newList;
}

/**
 * @brief Elimina una lista enlazada de oraciones
 * @param sentenceList Lista a eliminar
 */
void delete_sentenceList(SentenceList sentenceList)
{
    if(is_empty_sentenceList(sentenceList)){
        return;
    }
    SentencePosition aux = sentenceList->next;
    while(aux != NULL){
        aux = sentenceList->next;
    }
    free(sentenceList);
}

/**
 * @brief Verifica si una lista enlazada de oraciones esta vacia
 * @param sentenceList Lista dada
 * @return true si la lista esta vacia, false en caso contrario
 */
bool is_empty_sentenceList(SentenceList sentenceList)
{
    return sentenceList == NULL;
}

/**
 * @brief Inserta un nodo en una lista enlazada de oraciones
 * @param prevPosition Nodo anterior al que se desea insertar
 * @return Puntero al nuevo nodo insertado
 */
SentencePosition insert_sentenceList_node(SentencePosition prevPosition)
{
    SentencePosition newNode = (SentencePosition) malloc(sizeof(struct _sentenceListNode));
    if(newNode == NULL){
        print_error(200, NULL, NULL);
    }

    newNode->next = prevPosition->next;
    prevPosition->next = newNode;
    return newNode;
}
/**
 * @brief Imprime la lista de bytes de una lista enlazada de oraciones
 * @param sentenceList Lista dada
 */
void print_sentenceList(SentenceList sentenceList)
{
    SentencePosition P = sentenceList->next;

    while (P != NULL) {
        printf("        Byte: %ld\n", P->byte);
        P = P->next;
    }
}
/**
 * @brief Busca un elemento en una lista enlazada de oraciones
 * @param sentenceList Lista dada
 * @param byte Elemento a comparar
 * @return SentencePosition Retorna la posicion encontrada
 */
SentencePosition find_sentenceList_element(SentenceList sentenceList, long byte)
{
    if(is_empty_sentenceList(sentenceList)){
        return NULL;
    }
    SentencePosition P = sentenceList->next;
    while (P != NULL && P->byte != byte) {
        P = P->next;
    }
    return P;
}

