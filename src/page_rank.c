/**
 * @file page_rank.h
 * @author Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison
 * @brief Funciones relacionadas con la implementacion del algoritmo PageRank
 */

#include "page_rank.h"

void calculate_page_rank(Graph rankGraph)
{
    double diff = FRONTIER; // Diferencia entre los page rank
    double noLinks;// Valor de los nodos que no cuentan con enlaces incidentes
    double N = 0; // Cantidad de nodos
    GraphPosition P; //Varibles auxiliar para recorrer el grafo

    // Se obtiene la cantidad de nodos que contiene el grafo
    for(int i = 0; i < GRAPH_HASH_SIZE; i++){
        N += rankGraph[i].nodeNumber;
    }

    // Se inicializan los valores de los page rank
    for(int i = 0; i < GRAPH_HASH_SIZE; i++){
        P = graphList_first(rankGraph[i].nodeList);
        while (P != NULL){
            P->prevPagerank = 1/N;
            P->pageRank = 1/N;
            P = P->next;
        }
    }

    while (diff >= FRONTIER){
        diff = 0;
        noLinks = 0;

        // Se actualizan los page rank antiguos
        for(int i = 0; i < GRAPH_HASH_SIZE; i++){
            P = graphList_first(rankGraph[i].nodeList);
                while (P != NULL){
                    P->prevPagerank = P->pageRank;
                    P = P->next;
                }
        }

        // Se calcula la suma de los nodos sin enlaces adyacentes
        for(int i= 0; i < GRAPH_HASH_SIZE; i++){

            P = graphList_first(rankGraph[i].nodeList);
            while(P != NULL){
                if(P->adjacencyNumber == 0 ){
                    noLinks += P->prevPagerank;
                }
                P = P->next;
            }
        }
        // Se calcula el pagerank de cada nodo
        for(int i = 0; i < GRAPH_HASH_SIZE; i++){
            P = graphList_first(rankGraph[i].nodeList);

            while(P != NULL)
            {
                double sum = 0;
                LinkList Q = linkList_first(P->incidence);
                double newPR = (1 - DUMPING_FACTOR)/N;
                newPR += DUMPING_FACTOR * (noLinks/N);
                while(Q != NULL){
                    if(Q->graphNode->adjacencyNumber == 0){
                        continue;
                    }
                    sum += Q->graphNode->prevPagerank / Q->graphNode->adjacencyNumber;
                    Q = Q->next;
                }
                newPR += DUMPING_FACTOR * sum;
                diff += fabs(newPR - P->pageRank);
                P->pageRank = newPR;
                P = P->next;
            }
        }
    }
}