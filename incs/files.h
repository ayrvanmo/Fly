/**
 * @file files.h
 * @author Franco Aguilar, Milton Hernández, Iván Mansilla, Ayrton Morrison
 * @brief Cabecera para funciones de files.c
 */

#ifndef FILES_H
#define FILES_H

typedef struct _fileNode FileNode;
typedef FileNode *PtrToFileNode;
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
#include "output.h"
#include "position_list.h"

/** \struct _fileNode
 *  @brief Estructura que representa una lista de archivos
*/
struct _fileNode {
    int fileCount;
    char* filePath;
    char* name;
    unsigned long id;
    PtrToFileNode Next;
};

// funciones para el manejo de archivos
FileList make_empty_fileList(FileList L);
FilePosition insert_fileList_file(FileList L, FilePosition Prev, char* filePath, char* name, unsigned long id);
void delete_fileList(FileList L);
void print_fileList(FileList L);
FileList get_files_from_directory(char *directory, FileList list);
int count_filesList(FileList L);
void delete_fileList_file(FileList L, FilePosition file);
FilePosition find_fileList_file(FileList L, char* fileName);
FilePosition find_fileList_prev_file(FileList L, FilePosition File);
void process_file(FilePosition fileInfo, Graph graph, ReverseIndexTable index, StopWordsTable stopWords, FileList files);

#endif