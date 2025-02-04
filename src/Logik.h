#ifndef LOGIK_H
#define LOGIK_H

/*****************************************************************************/
/*  o o o o      Berner Fachhochschule                                       */
/*        :...o  Technik und Informatik                                      */
/*****************************************************************************/
/*  Header     : LaserChess/Logik                               Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Header for Logik.c                                          */
/*                                                                           */
/*  Procedures : laser(), is_inside_map(), is_figure, move_figure,           */
/*               destroy_figure(), mouseclick_to_map, path_handler,          */
/*               map_extension_handler, play_sound                           */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/*                                                                           */
/*  Email      : stolc2@bfh.ch                                               */
/*                                                                           */
/*  History    : 19.03.2012  File created                                    */
/*                                                                           */
/*  File       : Logik.h                                                     */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/

#include "LaserChess.h"

// Makro f�r Minimumwert aus zwei werten
#define MIN(a, b) (a<=b ? a : b)
#define MAX(a, b) (a>=b ? a : b)

// Wie lange nach abschluss des Laserschusses gewartet wird (ms)
#define LASER_FINISHED_WAIT_TIME 1000

// Globale Variable f�r Logik
location Hit_mirror;

// Prototypen
int laser(location pos, enum Direction dir);	//enum Direction dir
int is_inside_map(location pos);
int is_figure(location pos);
void move_figure(pawn *figure, location new_pos);
void destroy_figure(pawn *figure);
location mouseclick_to_map(void);
char *path_handler(const char path[], char file[]);
int map_extension_handler(char file[]);
void play_sound(enum Sound snd);

#endif
