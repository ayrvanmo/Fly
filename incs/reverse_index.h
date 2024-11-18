/**
 * @file reverse_index.h
 * @author Franco Aguilar, Milton Hernández, Iván Mansilla, Ayrton Morrison
 * @brief Cabecera relacionada a funciones de índice invertido
 */

#ifndef REVERSE_INDEX_H
#define REVERSE_INDEX_H

typedef struct _ReverseIndexNode ReverseIndexNode;
typedef ReverseIndexNode* ReverseIndexList;
typedef struct _ReverseIndexTable ReverseIndexTableNode;
typedef ReverseIndexTableNode* ReverseIndexTable;

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "errors.h"
#include "link_list.h"
#include "position_list.h"

#define MAX_STRING_LENGTH 50
#define MAX_HASH_TABLE_SIZE 10

/**
* @struct _ReverseIndexNode
* @brief Nodo de la lista de palabras asociadas a un hash key
*/
struct _ReverseIndexNode{
    char *word; /*!< Palabra asociada al hash key */
    PositionList files; /*!< Lista de archivos asociados a la palabra */
    unsigned int fileNumbers; /*!< Número de archivos asociados a la palabra */
    ReverseIndexList next; /*!< Siguiente nodo de la lista */
};

/** \struct _ReverseIndexTable
 *  @brief Estructura que representa un bloque de la tabla hash del índice invertido
 */
struct _ReverseIndexTable{
    ReverseIndexList wordList; /*!< Lista de palabras asociadas al hash key */
    unsigned int wordNumber; /*!< Conteo de cuantas palabras están asociadas al hash key */
};


/* Funciones de manejo de tablas hash */
ReverseIndexList init_empty_indexList();
ReverseIndexTable init_indexTable();
void print_hashTable(ReverseIndexTable hashTable);
ReverseIndexList insert_word_to_index(ReverseIndexTable hashTable, char* word);
ReverseIndexList search_word_in_index(ReverseIndexTable hashTable, char* word);
ReverseIndexList find_previous_index(ReverseIndexTable hashTable, char* word);
void delete_index_word(ReverseIndexTable hashTable, char* word);
void delete_indexTable(ReverseIndexTable hashTable);
void move_word_to_front(ReverseIndexTable hashTable, char* word);
void insert_file_to_index(ReverseIndexTable hashTable, PtrToGraphNode file, char* word, long byte);



#endif