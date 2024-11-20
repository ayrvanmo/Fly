/**
 * @file position_list.c
 * @author Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison
 * @brief Funciones para el manejo de una lista de posciones de palabras
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
        printf("Nodo de archivo: %s\n", P->graphNode->file->name);
        printf("    coincidencias = %d\n", P->coincidences);
        printf("    Lista de oraciones:\n");
        print_sentenceList(P->sentenceList);
        P = P->next;
    }
}

/**
 * @brief Funcion para encontrar un nodo en una lista de posiciones
 * @param positionList Lista de posiciones dada
 * @param graphNode Nodo de grafo que se desea buscar en la lista
 * @return Puntero al nodo si se encuentra, NULL en caso contrario
*/
PositionLocation find_positionList_node(PositionList positionList, GraphPosition graphNode)
{
    if(is_empty_positionList(positionList)){
        return NULL;
    }
    PositionLocation P = positionList_first(positionList);
    while (P != NULL && strcmp(P->graphNode->file->name, graphNode->file->name) != 0) {
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
 * @return PositionLocation Puntero al nuevo nodo insertado
 */
PositionLocation insert_positionList_node(PositionLocation prevPosition, PtrToGraphNode graphNode)
{
    PositionLocation newNode = (PositionLocation) malloc(sizeof(struct _positionListNode));
    if(newNode == NULL){
        print_error(200, NULL, NULL);
    }
    //printf("Insertando nodo en lista de posiciones\n");
    newNode->next = prevPosition->next;
    //printf("Cambiando punteros{1}\n");
    prevPosition->next = newNode;
    //printf("Cambiando punteros{2}\n");
    newNode->sentenceList = create_empty_sentenceList(NULL);
    newNode->coincidences = 0;
    newNode->graphNode = graphNode;
    //printf("Cambiando punteros{3}\n");
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
    delete_sentenceList(P->sentenceList);
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
    newList->byte = 0;
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
        delete_sentenceList_node(aux, sentenceList);
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
SentencePosition insert_sentenceList_node(SentencePosition prevPosition, long byte)
{
    SentencePosition newNode = (SentencePosition) malloc(sizeof(struct _sentenceListNode));
    if(newNode == NULL){
        print_error(200, NULL, NULL);
    }
    //printf("Insertando oracion en byte: %ld\n", byte);
    newNode->byte = byte;
    //printf("Cambiando punteros{1}\n");
    newNode->next = prevPosition->next;
    //printf("Cambiando punteros{2}\n");
    prevPosition->next = newNode;
    return newNode;
}
/**
 * @brief Imprime la lista de bytes de una lista enlazada de oraciones
 * @param sentenceList Lista dada
 */
void print_sentenceList(SentenceList sentenceList)
{
    if (sentenceList == NULL || sentenceList->next == NULL) {
        printf("La lista de oraciones está vacía.\n");
        return;
    }

    SentencePosition P = sentenceList->next;
    while (P != NULL) {
        printf("    Byte: %ld\n", P->byte);
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

/**
 * @brief Funcion para ordenar una lista de posiciones
 * @param L Lista de posiciones
 * @return La lista ordenada
 * @note Esta funcion debe recibir el PRIMER(->next) elemento de la lista, NO el centinela
*/
PositionList mergeSort_positionList(PositionList L)
{
    if (L == NULL || L->next == NULL) {
        return L;
    }

    PositionLocation middle = mid_point_positionList(L);
    if (middle == NULL) return L;

    PositionLocation nextOfMiddle = middle->next;
    middle->next = NULL;

    PositionLocation a = mergeSort_positionList(L);
    PositionLocation b = mergeSort_positionList(nextOfMiddle);

    return merge_positionList(a, b);
}

/**
 * @brief Funcion para encontrar el punto medio de una lista
 * @param L Lista de posiciones
 * @return el punto medio de la lista
*/
PositionLocation mid_point_positionList(PositionLocation L)
{
    if (L == NULL) return NULL;

    PositionLocation slow = L;
    PositionLocation fast = L;

    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

/**
 * @brief Funcion (iterativa) para fusionar dos listas ordenadas
 * @param a lista a
 * @param b lista b
 * @return retorna Lista Ordenada (a,b)
*/
PositionLocation merge_positionList(PositionLocation a, PositionLocation b)
{
    // Caso base: si una de las listas está vacía, retorna la otra
    if (a == NULL) return b;
    if (b == NULL) return a;

    // Nodo temporal para construir la lista resultante
    PositionLocation tmpCell = malloc(sizeof(*tmpCell));
    PositionLocation tail = tmpCell; // Puntero para recorrer y construir la lista

    while (a != NULL && b != NULL) {
        if (a->graphNode->pageRank >= b->graphNode->pageRank) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }

    // Agrega cualquier nodo restante en las listas
    if (a != NULL) {
        tail->next = a;
    } else {
        tail->next = b;
    }

    PositionLocation result = tmpCell->next;
    free(tmpCell); // Libera el nodo temporal
    return result;
}

/**
 * @brief Funcion que encuentra el nodo previo a uno dado en una lista de oraciones
 * @param P Posicion dada
 * @param sentenceList Lista dada
 * @return SentencePosition Retorna la posicion previa
 */
SentencePosition find_sentenceList_prev_node(SentencePosition P, SentenceList sentenceList)
{
    if(P == NULL){
        print_error(203, NULL, NULL);
    }
    SentencePosition prevNode = sentenceList;
    while (prevNode->next != P) {
        prevNode = prevNode->next;
    }
    return prevNode;
}

/**
 * @brief Funcion para eliminar un nodo de una lista de oraciones
 * @param P Nodo a eliminar
 * @param sentenceList Lista dada
 */
void delete_sentenceList_node(SentencePosition P, SentenceList sentenceList)
{
    if(P == NULL){
        print_error(203, NULL, NULL);
    }
    SentencePosition prevNode = find_sentenceList_prev_node(P, sentenceList);
    if(prevNode == NULL){
        print_error(301, NULL, NULL);
        return;
    }
    prevNode->next = P->next;
    free(P);
}
