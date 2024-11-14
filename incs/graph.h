/**
 * file graph.h
 * author Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison
 * brief Archivo de cabecera para grafos (graph.c)
*/
#ifndef GRAPH_H
#define GRAPH_H

// Provisorio
#define GRAPH_HASH_SIZE 2

typedef struct _graphNode GraphNode;
typedef GraphNode *PtrToGraphNode;
typedef PtrToGraphNode GraphPosition;
typedef PtrToGraphNode GraphList;
typedef struct _graphHasTable* Graph;

#include <stdbool.h>
#include <string.h>
#include "files.h"
#include "link_list.h"
#include "hash.h"

/** \struct _graphNode
 * @brief Nodo perteneciente al grafo de archivos
*/
struct _graphNode {
    double prevPagerank; /*!< PageRank anteriordel nodo */
    double pageRank; /*!< PageRank del nodo */
    FilePosition file; /*!<Puntero a la estructura que contiene información sobre el archivo */
    LinkList adjacency; /*!< Lista de nodos adyacentes al nodo */
    LinkList incidence; /*!< Lista de nodos que lo incluyen como adyacente */
    int adjacencyNumber; /*!< Numero de nodos adyacentes al nodo */
    int incidenceNumber; /*!< Numero de nodos que lo incluyen como adyacente */
    GraphPosition next; /*!< Posición siguiente en la lista de nodos del grafo */
};

/** \struct _graphHasTable
 *  @brief Estructura para representar un grafo como tabla hash
 */
struct _graphHasTable{
    GraphList nodeList; /*!< Lista de nodos asociados al hash key */
    unsigned int nodeNumber; /*!< Conteo de cuantas nodos están asociados al hash key */
};

// Funciones de lista de nodos
GraphList create_empty_graphList(GraphList graphList);
void delete_graphList(GraphList graphList);
bool is_empty_graphList(GraphList graphList);
void print_graphList(GraphList graphList);
void print_graphNode(GraphPosition P);
GraphPosition find_graphList_node(GraphList graphList, char *name);
GraphPosition find_graphList_prev_node(GraphPosition P, GraphList graphList);
GraphPosition insert_graphList_node(GraphPosition prevPosition, FilePosition file);
void delete_graphList_node(GraphPosition P, GraphList graphList);

// Funciones de interaccion con el usuario
GraphPosition graphList_first(GraphList graphList);
GraphPosition graphList_last(GraphList graphList);
GraphPosition graphList_advance(GraphPosition P);
LinkList get_adjacentList(GraphPosition P);
LinkList get_incidentList(GraphPosition P);
char *get_name(GraphPosition P);
double get_pageRank(GraphPosition P);

// Funciones del grafo general
Graph create_graph(Graph graph);
void print_graph(Graph graph);
GraphPosition insert_graphNode(FilePosition file, Graph graph);
GraphPosition find_graphNode(char *name, Graph graph);
void delete_graphNode(char *name, Graph graph);
void delete_graph(Graph graph);
PtrToLinkNode create_graph_edge(GraphPosition node1, GraphPosition node2, double weight);
void remove_graph_edge(GraphPosition node1, GraphPosition node2);

#endif