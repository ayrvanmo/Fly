/**
 * file graph.c
 * author Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison
 * brief Funciones relacionadas con el grafo de archivos
*/
#include "graph.h"

// Funciones de lista de nodos

/**
 * @brief Funcion para crear una lista de nodos
 * @param GraphList Puntero a una lista de nodos si se quiere vaciar
 * @return Puntero al centinela de la lista
*/
GraphList create_empty_graphList(GraphList graphList)
{
    if(!is_empty_graphList(graphList)){
        delete_graphList(graphList);
    }
    GraphList newList = (GraphList) malloc(sizeof(struct _graphNode));
    if(newList == NULL){
        print_error(200, NULL, NULL);
    }
    newList->pageRank = 0;
    return newList;
}

/**
 * @brief Funcion para verificar si una lista de nodos está vacía
 * @param graphList Puntero a la lista de nodos
 * @return TRUE si la lista está vacía, FALSE en caso contrario
*/
bool is_empty_graphList(GraphList graphList)
{
    return graphList == NULL;
}

/**
 * @brief Funcion para borrar una lista de nodos
 * @param graphList Puntero a la lista de nodos
*/
void delete_graphList(GraphList graphList)
{
    if(is_empty_graphList(graphList)){
        return;
    }
    GraphPosition aux = graphList->next;
    while(aux != NULL){
        delete_graphList_node(aux, graphList);
        aux = graphList->next;
    }
    free(graphList); // No se necesitan liberar adyacencias y incidencias porque no fueron alocadas en el centinela
}

/**
 * @brief Funcion para imprimir una lista de nodos por consola
 * @param graphList Puntero a la lista de nodos
*/
void print_graphList(GraphList graphList)
{
    GraphPosition P = graphList_first(graphList);

    while (P != NULL) {
        printf("Nodo: %s, PageRank: %lf\n", P->name, P->pageRank);
        P = P->next;
    }
}

/**
 * @brief Funcion para buscar un nodo en una lista de nodos (por su nombre)
 * @param graphList Puntero a la lista de nodos
 * @param name Nombre del nodo a buscar
 * @return Puntero al nodo encontrado, NULL en caso de no encontrarlo
*/
GraphPosition find_graphList_node(GraphList graphList, char *name)
{
    if(is_empty_graphList(graphList)){
        return NULL;
    }
    GraphPosition P = graphList_first(graphList);
    while (P != NULL && strcmp(P->name, name) != 0) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Funcion para encontrar el nodo anterior a un nodo en una lista de nodos
 * @param P Nodo del que se buscara el anterior
 * @param graphList Puntero a la lista de nodos
 * @return Puntero al nodo anterior a @p P
*/
GraphPosition find_graphList_prev_node(GraphPosition P, GraphList graphList)
{
    GraphPosition aux = graphList;
    while (aux != NULL && strcmp(aux->next->name, P->name) != 0){
        aux = aux->next;
    }
    return aux;
}

/**
 * @brief Funcion para insertar un nodo en una lista de nodos
 * @param prevPosition Puntero al nodo anterior al que se desea insertar el nuevo nodo
 * @param name Nombre del archivo contenido en el nodo
 * @return Puntero al nodo insertado
*/
GraphPosition insert_graphList_node(GraphPosition prevPosition, char *name)
{
    GraphPosition newNode = (GraphPosition) malloc(sizeof (struct _graphNode));
    if(newNode == NULL){
        print_error(200, NULL, NULL);
    }
    newNode->next = prevPosition->next;
    prevPosition->next = newNode;
    newNode->adjacency = create_empty_linkList(NULL);
    newNode->incidence = create_empty_linkList(NULL);
    strcpy(newNode->name, name);
    newNode->pageRank = 0;
    return newNode;
}

/**
 * @brief Funcion para borrar un nodo de una lista de nodos
 * @param P Puntero al nodo a borrar
 * @param graphList Puntero a la lista de nodos a la que pertenece @p P
*/
void delete_graphList_node(GraphPosition P, GraphList graphList)
{
    if(P == NULL){
        print_error(203, NULL, NULL);
    }
    GraphPosition prevNode = find_graphList_prev_node(P, graphList);
    if(prevNode == NULL){
        print_error(301, NULL, NULL);
        return;
    }

    prevNode->next = P->next;
    delete_linkList(P->adjacency);
    delete_linkList(P->incidence);
    free(P);
}

// Funciones de interaccion con el usuario

/**
 * @brief Funcion para obtener el primer enlace de una lista de nodos
 * @param GraphList Lista de nodos del grafo
 * @return Puntero al primer enlace de la lista
*/
GraphPosition graphList_first(GraphList graphList)
{
    return graphList->next;
}

/**
 * @brief Funcion para obtener el ultimo enlace de una lista de nodos
 * @param GraphList Lista de nodos del grafo
 * @return Puntero al ultimo enlace de la lista
*/
GraphPosition graphList_last(GraphList graphList)
{
    GraphPosition P = graphList->next;
    while (P->next != NULL) {
        P = P->next;
    }
    return P;
}

/**
 * @brief Funcion para obtener el siguiente enlace de una lista de nodos
 * @param P Puntero al nodo anterior al que se desea acceder
 * @return Puntero al siguiente nodo de la lista
*/
GraphPosition graphList_advance(GraphPosition P)
{
    return P->next;
}

/**
 * @brief Funcion para para obtener la lista de adyacencias de un nodo
 * @param P Puntero al nodo del que se desea obtener la lista de adyacencias
 * @return Puntero a la lista de adyacencias
*/
LinkList get_adjacentList(GraphPosition P)
{
    return P->adjacency;
}

/**
 * @brief Funcion para obtener la lista de incidencias de un nodo
 * @param P Puntero al nodo del que se desea obtener la lista de incidencias
 * @return Puntero a la lista de incidencias
*/
LinkList get_incidentList(GraphPosition P){
    return P->incidence;
}

/**
 * @brief Funcion para obtener el nombre de un nodo
 * @param P Puntero al nodo del que se desea obtener el nombre
 * @return Puntero al nombre del nodo
*/
char *get_name(GraphPosition P)
{
    return P->name;
}

/**
 * @brief Funcion para obtener el PageRank de un nodo
 * @param P Puntero al nodo del que se desea obtener el peso
 * @return Puntero al PageRank del nodo
*/
double get_pageRank(GraphPosition P)
{
    return P->pageRank;
}

// Funciones del grafo general

/**
 * @brief Funcion para crear un grafo
 * @param graph Grafo a crear
 * @return Grafo creado
*/
Graph create_graph(Graph graph)
{
    if(graph != NULL)
    {
        delete_graph(graph);
    }

    graph = (Graph)malloc(sizeof(struct _graphHasTable) * GRAPH_HASH_SIZE);

    if(!graph){
        print_error(200,NULL,NULL);
    }

    for(int i = 0; i < GRAPH_HASH_SIZE; i++)
    {
        graph[i].nodeList = create_empty_graphList(NULL);
        graph[i].nodeNumber = 0;
    }

    return graph;
}

/**
 * @brief Funcion para imprimir un grafo por consola
 * @param graph Grafo a imprimir
*/
void print_graph(Graph graph)
{
    // Impresion completa
    /* for(int i = 0; i < GRAPH_HASH_SIZE; i++)
    {
        printf("-----------------------------\n");
        printf("Hash key: %d\n", i);
        print_graphList(graph[i].nodeList);
        printf("\n\n");
    } */
    // Cantidad de nodos
    for(int i = 0; i < GRAPH_HASH_SIZE; i++)
    {
        printf("%d: %d nodos\n", i, graph[i].nodeNumber);
    }
}

/**
 * @brief Funcion para insertar un nodo en un grafo
 * @param name Nombre del archivo contenido en el nodo
 * @param graph Grafo en el que se desea insertar el nodo
 * @return Puntero al nodo insertado
*/
GraphPosition insert_graphNode(char *name, Graph graph)
{
    int index = jenkinsHash(name, strlen(name)) % GRAPH_HASH_SIZE;
    GraphPosition P = insert_graphList_node(graph[index].nodeList, name);
    if(P!=NULL){
        graph[index].nodeNumber++;
    }
    return P;
}

/**
 * @brief Funcion para borrar un nodo de un grafo
 * @param name Nombre del archivo contenido en el nodo
 * @param graph Grafo en el que se busca el nodo de nombre @p name
*/
void delete_graphNode(char *name, Graph graph)
{
    int index = jenkinsHash(name, strlen(name)) % GRAPH_HASH_SIZE;
    GraphPosition P = find_graphList_node(graph[index].nodeList, name);
    if(P == NULL){
        print_error(301, NULL, NULL);
        return;
    }
    delete_graphList_node(P, graph[index].nodeList);
    graph[index].nodeNumber--;
}

/**
 * @brief Funcion para borrar un grafo
 * @param graph Grafo a borrar
*/
void delete_graph(Graph graph)
{
    for(int i = 0; i < GRAPH_HASH_SIZE; i++)
    {
        delete_graphList(graph[i].nodeList);
    }
    free(graph);
}