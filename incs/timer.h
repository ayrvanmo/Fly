/**
 * @file timer.h
 * @author Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison
 * @brief Funciones para manejo de tiempos (Only for testing)
*/
#ifndef TIMER_H
#define TIMER_H

#include <stdio.h>
#include <time.h>
#include <stdbool.h>

/** \struct Timer
 *  @brief Estructura que representa un temporizador
 */
typedef struct{
    clock_t start; 
    clock_t pause; 
    double total; 
    bool in_pause; 
}Timer;

// funciones del temporizador
void init_timer(Timer* timer); 
void pause_timer(Timer* timer); 
void resume_timer(Timer* timer); 
void end_timer(Timer* timer);
void print_timer(Timer* timer);
#endif