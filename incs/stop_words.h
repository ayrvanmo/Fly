/**
 * @file stop_words.h
 * @author Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison
 * @brief Cabeceras para funciones de stop_words.c
*/
#ifndef STOP_WORDS_H
#define STOP_WORDS_H

#define STOP_WORDS_HASH_SIZE 150

typedef struct _stopWord StopWord;
typedef StopWord *PtrToStopWord;
typedef PtrToStopWord StopWordPosition;
typedef PtrToStopWord StopWordList;
typedef struct _stopHashTable* StopWordsTable;

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "hash.h"

/** \struct _stopWord
 * @brief Palabra perteneciente al diccionario de stop words
*/
struct _stopWord {
    char word[25]; /*!< Palabra almacenada*/
    StopWordPosition next; /*!< Posición siguiente en la lista de palabras */
};

/** \struct _stopHashTable
 *  @brief Estructura para representar un diccionario de stop words
 */
struct _stopHashTable{
    StopWordList wordList; /*!< Lista de palabras asociadas al hash key */
    int nodeNumber; /*!< Cantidad de nodos asociados al hash key */
};

// Funciones de lista de palabras
StopWordList create_empty_stopWordList(StopWordList stopWordList);
void delete_stopWordList(StopWordList stopWordList);
bool is_empty_stopWordList(StopWordList stopWordList);
void print_stopWordList(StopWordList stopWordList);
StopWordPosition find_stopWordList_word(StopWordList stopWordList, char *word);
StopWordPosition find_stopWordList_prev_word(StopWordPosition P, StopWordList stopWordList);
StopWordPosition insert_stopWordList_word(StopWordPosition prevPosition, char *word);
void delete_stopWordList_word(StopWordPosition P, StopWordList stopWordList);

// Funciones de interaccion con el usuario
StopWordPosition stopWordList_first(StopWordList stopWordList);
StopWordPosition stopWordList_last(StopWordList stopWordList);
StopWordPosition stopWordList_advance(StopWordPosition P);
char *get_word(StopWordPosition P);

// Funciones del diccionario de stop words
StopWordsTable create_stopWordsTable(StopWordsTable stopWordsTable);
StopWordsTable read_stopWord_file(char *fileName, StopWordsTable stopWordsTable);
void print_stopWordsTable(StopWordsTable stopWordsTable);
StopWordPosition insert_stopWord(char *word, StopWordsTable stopWordsTable);
void delete_stopWordsTable_word(char *word, StopWordsTable stopWordsTable);
void delete_stopWordsTable(StopWordsTable stopWordsTable);
bool is_stopWord(char *word, StopWordsTable stopWordsTable);

#endif