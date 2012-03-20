#ifndef LOGIK_H
#define LOGIK_H

/*****************************************************************************/
/*	o o o o      Berner Fachhochschule										 */
/*		  :...o  Technik und Informatik										 */
/*****************************************************************************/
/*  Header     : LaserChess/Logik                               Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Contains several logic and helper functions                 */
/*                                                                           */
/*  Procedures : laser(), is_inside_map(), is_figure, move_figure, spiel()   */
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

int laser(location pos, enum Direction dir);
int is_inside_map(location pos);
int is_figure(location pos);
void move_figure(pawn *figure, location new_pos);

#endif
