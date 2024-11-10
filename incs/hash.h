/**
 * file hash.h
 * author Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison
 * brief Archivo de cabecera para hashing (hash.c)
*/
#ifndef HASH
#define HASH

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

unsigned int jenkins_hash(char* key);

unsigned int hashFile (char *filename);

#endif