/**
 * @file files.h
 * @author Franco Aguilar, Milton Hernández, Iván Mansilla, Ayrton Morrison
 * @brief funciones para manejar archivos de directorio
 */

#ifndef FILES_H
#define FILES_H

typedef struct _elementType fileInfo;
typedef struct Node *PtrToFileNode; 
typedef PtrToFileNode fileList; 
typedef PtrToFileNode filePosition; 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "errors.h"

/** \struct _elementType
     *  @brief Estructura que representa un archivo
     */
struct _elementType {
    char* filePath;
    char* name;
    unsigned long id;  
}; 

/** \struct Node
     *  @brief Estructura que representa una lista de archivos
     */
struct Node {
    fileInfo Element;
    struct Node *Next;
    int fileCount;
};

// funciones para el manejo de archivos
fileList make_empty_fileList(fileList L);
filePosition insert_fileList_file(fileInfo X, fileList L, filePosition P);
void delete_fileList(fileList L);
void print_fileList(fileList L);
fileList get_files_from_directory(char *directory, fileList list);
int count_filesList(fileList L);
void delete_fileList_file(fileList L, char *fileName);
/*filePosition find_fileList_file(fileList L, char* fileName);*/
char* get_only_fileName(char* name);
#endif