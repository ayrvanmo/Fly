/**
 * file position_list.h
 * author Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison
 * brief Archivo de cabecera para position_list (position_list.c)
*/

#ifndef POSITION_LIST_H
#define POSITION_LIST_H

// typedef PositionList
typedef struct _positionListNode PositionListNode;
typedef PositionListNode *PtrToPositionListNode;
typedef PtrToPositionListNode PositionLocation;
typedef PtrToPositionListNode PositionList;

// typedef SentenceList
typedef struct _sentenceListNode SentenceListNode;
typedef SentenceListNode *PtrToSentenceListNode;
typedef PtrToSentenceListNode SentencePosition;
typedef PtrToSentenceListNode SentenceList;

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "errors.h"
#include "graph.h"
#include "utilities.h"

#define MAX_NAME 30

/** \struct _positionListNode
 * @brief Estructura para manejar una lista de enlaces a nodos de un grafo
*/
struct _positionListNode {
    int coincidences; /*!< Cantidad de coincidencias */
    PtrToGraphNode graphNode; /*!< Nodo de grafo */
    PositionLocation next; /*!< Posicion siguiente en la lista */
    SentenceList sentenceList; /*!< Lista de oraciones */
};


/** \struct _sentenceListNode
 * @brief Estructura para manejar una lista enlazada de oraciones
 */
struct _sentenceListNode {
    long byte; /*!< Posicion en byte de la oracion almacenada */
    SentencePosition next; /*!< Siguiente nodo en la lista */
};

// Funciones para el manejo de una lista de enlaces
PositionList create_empty_positionList(PositionList positionList);
void delete_positionList(PositionList positionList);
bool is_empty_positionList(PositionList positionList);
void print_positionList(PositionList positionList);
PositionLocation find_positionList_node(PositionList positionList, GraphPosition graphNode);
PositionLocation find_positionList_prev_node(PositionLocation P, PositionList positionList);
PositionLocation insert_positionList_node(PositionLocation prevPosition, PtrToGraphNode graphNode);
PositionLocation head_positionList(PositionList positionList);
void delete_positionList_node(PositionLocation P, PositionList positionList);
PositionList mergeSort_positionList(PositionList L);
PositionLocation merge_positionList(PositionLocation a, PositionLocation b);
PositionLocation mid_point_positionList(PositionLocation L);

// Funciones de interaccion con el usuario
PositionLocation positionList_first(PositionList positionList);
PositionLocation positionList_last(PositionList positionList);
PositionLocation positionList_advance(PositionLocation P);
PtrToGraphNode get_position_graphNode(PositionLocation P);

// Funciones relacionadas a la lista de oraciones
SentenceList create_empty_sentenceList(SentenceList sentenceList);
SentencePosition insert_sentenceList_node(SentencePosition prevPosition, long byte);
SentencePosition find_sentenceList_element(SentenceList sentenceList, long byte);
SentencePosition find_sentenceList_prev_node(SentencePosition P, SentenceList sentenceList);
void delete_sentenceList_node(SentencePosition P, SentenceList sentenceList);
void delete_sentenceList(SentenceList sentenceList);
void print_sentenceList(SentenceList sentenceList);
bool is_empty_sentenceList(SentenceList sentenceList);

#endif