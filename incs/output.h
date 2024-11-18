/**
 * @file output.c
 * @author Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison
 * @brief Archivo de cabezera para output (output.c)
*/


#ifndef OUTPUT_H
#define OUTPUT_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "position_list.h"
#include "errors.h"
#include "graph.h"
#include "reverse_index.h"


void show_coincidences(ReverseIndexTable indexTablem, char *seeked_word);
void print_file_paragraphs(FilePosition file, SentenceList bytes, char *asked_word);

#endif