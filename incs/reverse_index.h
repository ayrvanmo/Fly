/**
 * @file reverse_index.h
 * @author Franco Aguilar, Milton Hernández, Iván Mansilla, Ayrton Morrison
 * @brief Cabecera relacionada a funciones de índice invertido
 */

#ifndef REVERSE_INDEX_H
#define REVERSE_INDEX_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
    #include "errors.h"
    #include "link_list.h"

    #define MAX_STRING_LENGTH 50
    #define MAX_HASH_TABLE_SIZE 10


    /**
     * @struct HashList
     * @brief Nodo de la lista de palabras asociadas a un hash key
     */
    typedef struct HashList{
        char *word; /*!< Palabra asociada al hash key */
        LinkList files; /*!< Lista de archivos asociados a la palabra */
        unsigned int fileNumbers; /*!< Número de archivos asociados a la palabra */
        struct HashList* next; /*!< Siguiente nodo de la lista */
    } HashList;

    /** \struct HashTable
     *  @brief Estructura que representa una tabla de hash
     */
    typedef struct HashTable{
        struct HashList* wordList; /*!< Lista de palabras asociadas al hash key */
        unsigned int wordNumber; /*!< Conteo de cuantas palabras están asociadas al hash key */
    } HashTable;


    /* Funciones de manejo de tablas hash */
    unsigned int jenkins_hash(char* key);
    void init_hash_table(HashTable hashTable[MAX_HASH_TABLE_SIZE]);
    void print_hash_table(HashTable hashTable[MAX_HASH_TABLE_SIZE]);
    void insert_hash(HashTable hashTable[MAX_HASH_TABLE_SIZE], char* word);
    HashList* search_hash(HashTable hashTable[MAX_HASH_TABLE_SIZE], char* word);
    HashList* find_previous_hash(HashTable hashTable, char* word);
    void delete_hash(HashTable hashTable[MAX_HASH_TABLE_SIZE], char* word);
    void delete_hash_table(HashTable HashTable[MAX_HASH_TABLE_SIZE]);
    
    /* Funciones de manejo del índice invertido */
    

    /* Funciones de depuración */
    char* generate_random_word();

    

#endif