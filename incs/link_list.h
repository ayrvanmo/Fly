/**
 * file link_list.h
 * author Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison
 * brief Archivo de cabecera para LinkList
*/

#ifndef LINK_LIST_H
#define LINK_LIST_H

typedef struct _linkListNode LinkListNode;
typedef LinkListNode *PtrToLinkNode;
typedef PtrToLinkNode LinkPosition;
typedef PtrToLinkNode LinkList;

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "errors.h"
#include "graph.h"


/** \struct _linkListNode
 * @brief Estructura para manejar una lista de enlaces a nodos de un grafo
*/
struct _linkListNode {
    PtrToGraphNode graphNode; /*!< Nodo de grafo */
    double weight; /*!< Peso del enlace */
    LinkPosition next; /*!< Posicion siguiente en la lista */
};

// Funciones para el manejo de una lista de enlaces
LinkList create_empty_linkList(LinkList linkList);
void delete_linkList(LinkList linkList);
bool is_empty_linkList(LinkList linkList);
void print_linkList(LinkList linkList);
LinkPosition find_linkList_node(LinkList linkList, GraphNode graphNode);
LinkPosition find_linkList_prev_node(LinkPosition P, LinkList linkList);
LinkPosition insert_linkList_node(LinkPosition prevPosition, PtrToGraphNode graphNode, double weight);
LinkPosition insert_ordered_linkList_node(bool (*order)(double, double), LinkList linkList, PtrToGraphNode graphNode, double weight);
void delete_linkList_node(LinkPosition P, LinkList linkList);

// Funciones de interaccion con el usuario
LinkPosition linkList_first(LinkList linkList);
LinkPosition linkList_last(LinkList linkList);
LinkPosition linkList_advance(LinkPosition P);
PtrToGraphNode get_graphNode(LinkPosition P);
unsigned int get_weight(LinkPosition P);

// Funciones para usar como parametros
bool increasing(double a, double b);
bool decreasing(double a, double b);


#endif