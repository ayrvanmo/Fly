/**
 * @file page_rank.h
 * @author Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison
 * @brief Cabezeras para funcion de pagerank (page_rank.c)
 */

#ifndef PAGE_RANK_H
#define PAGE_RANK_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"


#define DUMPING_FACTOR 0.85
#define FRONTIER 0.0001

void calculate_page_rank(Graph rankGraph);


#endif
