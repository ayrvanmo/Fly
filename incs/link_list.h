/**
 * @file link_list.h
 * @author Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison
 * @brief Cabeceras para funciones de link_list.c
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
#include <unistd.h>
#include "errors.h"
#include "graph.h"
#include "utilities.h"


/** \struct _linkListNode
 * @brief Estructura para manejar una lista de enlaces a nodos de un grafo
*/
struct _linkListNode {
    PtrToGraphNode graphNode; /*!< Nodo de grafo */
    LinkPosition next; /*!< Posicion siguiente en la lista */
};

// Funciones para el manejo de una lista de enlaces
LinkList create_empty_linkList(LinkList linkList);
void delete_linkList(LinkList linkList);
bool is_empty_linkList(LinkList linkList);
void print_linkList(LinkList linkList);
LinkPosition find_linkList_node(LinkList linkList, GraphNode graphNode);
LinkPosition find_linkList_prev_node(LinkPosition P, LinkList linkList);
LinkPosition insert_linkList_node(LinkPosition prevPosition, PtrToGraphNode graphNode);
void delete_linkList_node(LinkPosition P, LinkList linkList);

// Funciones de interaccion con el usuario
LinkPosition linkList_first(LinkList linkList);
LinkPosition linkList_last(LinkList linkList);
LinkPosition linkList_advance(LinkPosition P);
PtrToGraphNode get_graphNode(LinkPosition P);



#endif