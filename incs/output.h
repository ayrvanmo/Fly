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
    // IDEAS PARA LA FUNCION
    // 1. AGARRAR UN ARCHIVO ABIERTO, DEBIDO A QUE PUEDE IMPRIMIR MAS DE UN PARAGRAPH
    // 2. LEER EL ARCHIVO E IMPRIMIR EL ARCHIVO HASTA EL PRIMER SALTO DE LINEA
    // 3. IMPRIMIR EL PARAGRAPH QUE CONTIENE LA PALABRA BUSCADA
    // 4. RESALTAR LA PALABRA BUSCADA



#endif