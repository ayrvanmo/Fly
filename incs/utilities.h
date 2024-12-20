/**
 * @file utilities.h
 * @author Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison
 * @brief Cabecera para funciones de utilities.c
*/
#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <getopt.h>
#include "errors.h"


// Colores para texto
#define CLEAR_SCREEN "\033[H\033[J"
#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"


char* get_terminal_parameters(int argc, char **argv);
// Para cadenas de caracteres
void to_low_case(char* s1);
void remove_punctuation(char* s1);
char* get_only_fileName(char* file);
bool is_valid_extension(char* extension);
// Funciones para usar como parametros
bool increasing(double a, double b);
bool decreasing(double a, double b);

#endif