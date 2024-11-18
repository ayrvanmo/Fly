/**
 * @file timer.c
 * @author Franco Aguilar, Milton Hernandez, Ivan Mansilla, Ayrton Morrison
 * @brief Funciones relacionadas a temporizador
 */

# include "timer.h"

/**
 * @brief inicializa el temporizador
 * @param timer Puntero al struct del temporizador
 */
void init_timer(Timer* timer)
{
    timer->start = clock();
    timer->total = 0.0;
    timer->in_pause = false;
    printf("Temporizador iniciado\n");
}

/**
 * @brief pausa el temporizador
 * @param timer Puntero al struct del temporizador
 */
void pause_timer(Timer* timer)
{
    if(!timer->in_pause){
        timer->pause = clock();
        timer->total += (double)(timer->pause - timer->start) / CLOCKS_PER_SEC;
        timer->in_pause = true;
        printf("Temporizador pausado\n");
    }
}

/**
 * @brief reanuda el temporizador
 * @param timer Puntero al struct del temporizador
 */
void resume_timer(Timer* timer)
{
    if(timer->in_pause){
        timer->start = clock();
        timer->in_pause = false;
        printf("Temporizador reanudado\n");
    }
}

/**
 * @brief finaliza el temporizador
 * @param timer Puntero al struct del temporizador
 */
void end_timer(Timer* timer)
{
    if (!timer->in_pause){
        timer->total += (double)(clock() - timer->start) / CLOCKS_PER_SEC;
    }
    printf("Temporizador terminado en %.6f segundos\n", timer->total);
}

/**
 * @brief imprime el tiempo del temporizador
 * @param timer Puntero al struct del temporizador
 */
void print_timer(Timer* timer)
{
    printf("Tiempo del timer: %.6f segundos%s\n", timer->total, timer->in_pause ? " (pausado)." : ".");
}