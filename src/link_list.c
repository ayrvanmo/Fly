/**
 * file link_list.h
 * author Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison
 * brief Funciones para el manejo de una lista de enlaces a nodos de un grafo
*/

#include "link_list.h"

/**
 * @brief Funcion para vaciar una lista de enlaces
 * @param linkList Lista de enlaces
 * @return Puntero a una lista vacia
*/
LinkList create_empty_linkList(LinkList linkList)
{
    if(!is_empty_linkList(linkList)){
        delete_linkList(linkList);
    }
    LinkList newList = (LinkList) malloc(sizeof(struct _linkListNode));
    if(newList == NULL){
        print_error(200, NULL, NULL);
    }
    newList->next = NULL;
    newList->graphNode = NULL;
    newList->weight = 0;
    return newList;
}

/**
 * @brief Funcion para eliminar una lista de enlaces
 * @param linkList Lista de enlaces a eliminar
*/
void delete_linkList(LinkList linkList)
{
    if(is_empty_linkList(linkList)){
        return;
    }
    LinkPosition aux = linkList->next;
    while(aux != NULL){
        delete_linkList_node(aux, linkList);
        aux = linkList->next;
    }
    free(linkList);
}

/**
 * @brief Funcion para verificar si una lista de enlaces esta vacia
 * @param linkList Lista de enlaces
 * @return TRUE si la lista esta vacia, FALSE en caso contrario
*/
bool is_empty_linkList(LinkList linkList)
{
    return linkList == NULL;
}

/**
 * @brief Funcion para imprimir una lista de enlaces
 * @param linkList Lista de enlaces
*/
void print_linkList(LinkList linkList) {
    LinkPosition P = linkList_first(linkList);

    while (P != NULL) {
        printf("Nodo: %s, Peso: %lf\n", P->graphNode->name, P->weight);
        P = P->next;
    }
}

/**
 * @brief Funcion para encontrar un nodo en una lista de enlaces
 * @param linkList Lista de enlaces
 * @param graphNode Nodo de grafo que se desea buscar en la lista
 * @return Puntero al nodo si se encuentra, NULL en caso contrario
*/
LinkPosition find_linkList_node(LinkList linkList, GraphNode graphNode)
{
    if(is_empty_linkList(linkList)){
        return NULL;
    }
    LinkPosition P = linkList_first(linkList);
    while (P != NULL && strcmp(P->graphNode->name, graphNode.name) != 0) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Funcion para obtener el anterior enlace de una lista de enlaces
 * @param P Puntero al enlace posterior al que se desea acceder
 * @return Puntero al anterior enlace de la lista
*/
LinkPosition find_linkList_prev_node(LinkPosition P, LinkList linkList)
{
    LinkPosition aux = linkList;
    while (aux != NULL && aux->next != P) {
        aux = aux->next;
    }
    return aux;
}

/**
 * @brief Funcion para insertar un nodo en una lista de enlaces
 * @param prevPosition Puntero al enlace anterior al que se desea insertar el nuevo enlace
 * @param graphNode Nodo de grafo al que apunta el enlace a insertar
 * @param weight Peso del enlace a insertar
 * @return Puntero al nuevo enlace insertado
*/
LinkPosition insert_linkList_node(LinkPosition prevPosition, PtrToGraphNode graphNode, double weight)
{
    LinkPosition newNode = (LinkPosition) malloc(sizeof(struct _linkListNode));
    if(newNode == NULL){
        print_error(200, NULL, NULL);
    }
    newNode->graphNode = graphNode;
    newNode->weight = weight;
    
    
    newNode->next = prevPosition->next;
    
    prevPosition->next = newNode;
    
    return newNode;
}

/**
 * @brief Funcion para insertar un enlace en una lista de enlaces de forma ordenada segun el peso de los enlaces
 * @param order Funcion que compara dos valores de tipo double para determinar el orden
 * @param linkList Lista de enlaces
 * @param graphNode Puntero a un Nodo de grafo al que apuntara el enlace a insertar
 * @param weight Peso del enlace a insertar
 * @return Puntero al nuevo enlace insertado
 * @note @p order debe ser la funcion increasing (para insertar en orden creciente) o decreasing (para insertar en orden decreciente)
*/
LinkPosition insert_ordered_linkList_node(bool (*order)(double, double), LinkList linkList, PtrToGraphNode graphNode, double weight)
{
    if(is_empty_linkList(linkList)){
        print_error(300, NULL, NULL);
        create_empty_linkList(linkList);
    }
    if(linkList->next == NULL){
        return insert_linkList_node(linkList, graphNode, weight);
    }

    LinkPosition aux = linkList;

    while (aux->next != NULL && order(aux->next->weight, weight)){
        aux = aux->next;
    }

    return insert_linkList_node(aux, graphNode, weight);
}


/**
 * @brief Funcion para eliminar un enlace de una lista de enlaces
 * @param P Puntero al enlace que se desea eliminar
 * @param linkList Lista de enlaces a la que pertenece @p P
*/
void delete_linkList_node(LinkPosition P, LinkList linkList)
{
    if(P == NULL){
        print_error(203, NULL, NULL);
    }
    LinkPosition prevNode = find_linkList_prev_node(P, linkList);
    if(prevNode == NULL){
        print_error(301, NULL, NULL);
        return;
    }

    prevNode->next = P->next;
    free(P);
}


// Funciones de interaccion con el usuario

/**
 * @brief Funcion para obtener el primer enlace de una lista de enlaces
 * @param linkList Lista de enlaces
 * @return Puntero al primer enlace de la lista
*/
LinkPosition linkList_first(LinkList linkList)
{
    return linkList->next;
}

/**
 * @brief Funcion para obtener el ultimo enlace de una lista de enlaces
 * @param linkList Lista de enlaces
 * @return Puntero al ultimo enlace de la lista
*/
LinkPosition linkList_last(LinkList linkList)
{
    LinkPosition P = linkList->next;
    while (P->next != NULL) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Funcion para obtener el siguiente enlace de una lista de enlaces
 * @param P Puntero al enlace anterior al que se desea acceder
 * @return Puntero al siguiente enlace de la lista
*/
LinkPosition linkList_advance(LinkPosition P)
{
    return P->next;
}

/**
 * @brief Funcion para obtener el nodo de un grafo a partir de un enlace
 * @param P Puntero al enlace
 * @return Nodo de grafo
*/
PtrToGraphNode get_graphNode(LinkPosition P)
{
    if(P == NULL){
        print_error(203, NULL, NULL);
    }
    return P->graphNode;
}

/**
 * @brief Funcion para obtener el peso de un enlace
 * @param P Puntero al enlace
 * @return Peso del enlace
*/
unsigned int get_weight(LinkPosition P)
{
    if(P == NULL){
        print_error(203, NULL, NULL);
    }
    return P->weight;
}


// Funciones para usar como parametros
/**
 * @brief Funcion para comparar si un valor es mayor o igual a otro
 * @param a Primer valor
 * @param b Segundo valor
 * @return TRUE si @p a es mayor o igual a @p b, FALSE en caso contrario
*/
bool increasing(double a, double b){
    return a <= b;
}

/**
 * @brief Funcion para comparar si un valor es menor o igual a otro
 * @param a Primer valor
 * @param b Segundo valor
 * @return TRUE si @p a es menor o igual a @p b, FALSE en caso contrario
*/
bool decreasing(double a, double b){
    return a >= b;
}