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
/*  Procedures : laser(), is_inside_map(), move_figure, spiel()              */
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


/*****************************************************************************/
/*  Function   : laser                                          Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   :                                                             */
/*                                                                           */
/*  Input Para : position from which the laser line is moving AWAY. And the  */
/*               And the direction.                                          */
/*                                                                           */
/*  Output     : if a wall was hit: 0. If a king was hit: -1 for player_red, */
/*               -2 for player_blue. If a mirror was hit: +1 for player_red, */
/*               +2 for player_blue                                          */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/*                                                                           */
/*  Email      : stolc2@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

int laser(location pos, enum Direction dir);
int is_inside_map(location pos);
void move_figure(*pawn figure, location new_pos);

#endif
