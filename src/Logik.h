#ifndef LOGIK_H
#define LOGIK_H

/*****************************************************************************/
/*	o o o o      Berner Fachhochschule										 */
/*		  :...o  Technik und Informatik										 */
/*****************************************************************************/
/*  Header     : LaserChess/Logik                               Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Header for Logik.c  							             */
/*                                                                           */
/*  Procedures : laser(), is_inside_map(), is_figure, move_figure, 			 */
/* 				 destroy_figure()										     */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/* 																			 */
/*  Email	   : stolc2@bfh.ch  						                     */
/*                                                                           */
/*  History    : 19.03.2012  File created                                    */
/*                                                                           */
/*  File       : Logik.h                                                     */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/

#include "LaserChess.h"

// Makro für Minimumwert aus zwei werten
#define MIN(a, b) (a<=b ? a : b)
#define MAX(a, b) (a>=b ? a : b)

// Wie lange nach abschluss des Laserschusses gewartet wird (ms)
#define LASER_FINISHED_WAIT_TIME 1000

int laser(location pos, enum Direction dir);	//enum Direction dir
int is_inside_map(location pos);
int is_figure(location pos);
void move_figure(pawn *figure, location new_pos);
void destroy_figure(pawn *figure);
location mouseclick_to_map(void);

#endif
