/**
 * @file files.h
 * @author Franco Aguilar, Milton Hernández, Iván Mansilla, Ayrton Morrison
 * @brief funciones para manejar archivos de directorio
 */

#ifndef FILES_H
#define FILES_H

typedef struct _elementType fileInfo;
typedef struct Node *PtrToFileNode;
typedef PtrToFileNode FileList;
typedef PtrToFileNode FilePosition;

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "graph.h"
#include "reverse_index.h"
#include "stop_words.h"
#include "errors.h"
#include "utilities.h"

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
FileList make_empty_fileList(FileList L);
FilePosition insert_fileList_file(fileInfo X, FileList L, FilePosition P);
void delete_fileList(FileList L);
void print_fileList(FileList L);
FileList get_files_from_directory(char *directory, FileList list);
int count_filesList(FileList L);
void delete_fileList_file(FileList L, char *fileName);
/*FilePosition find_fileList_file(FileList L, char* fileName);*/
char* get_only_fileName(char* name);
void process_file(FilePosition file, Graph graph, ReverseIndexTable index, StopWordsTable stopWords);

#endif