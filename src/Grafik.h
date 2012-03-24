#ifndef GRAFIK_h
#define GRAFIK_h
/*****************************************************************************/
/*  o o o o      Berner Fachhochschule                                       */
/*        :...o  Technik und Informatik                                      */
/*****************************************************************************/
/*  Header     : LaserChess/Grafik                              Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Desc       : Header for graphics functions                               */
/*                                                                           */
/*  Procedures :                                                             */
/*                                                                           */
/*  Author     : J. Haldemann + N. Käser                                     */
/*                                                                           */
/*  Email      : haldj3@bfh.ch                                               */
/*                                                                           */
/*  Creation   : xx.03.2012                                                  */
/*                                                                           */
/*  File       : Grafik.h                                                    */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/

/*imports*/
#include <stdio.h>
#include <stdlib.h>

#include "window.h"
#include "LaserChess.h"
#include "Logik.h"
#include "Spiel.h"

/*Grundsätzliche Grafik Definitionen*/
#define FIELD_SIZE 100				//Feldbreite
#define PLAYGROUND_X_MAX 8			//Anzahl Felder - Breite
#define PLAYGROUND_Y_MAX 6			//Anzahl Felder - Höhe
#define PLAYGROUND_COL COL_BLACK	//Spielfeldfarbe
#define LINE_COL COL_GREY			//Linienfarbe
#define FIELD_LINE_WIDTH 3			//Breite der Spielfeldlinien
#define FOCUS_COL COL_GREEN			//Fokusfarbe
#define FOCUS_IDENT 5				//Einzurückende Pixel der Focusfunktion
#define LASER_COL COL_RED			//Laserfarbe
#define LASER_SPEED	100				//Geschwindigkeit beim Zeichnen des Lasers in ms

/*Prototypen*/
location pixel_to_map(location Mapkoordinaten);
location map_to_pixel(location Windowskoordinaten);
void draw_playground();
void draw_focus(location Field);
void draw_empty_field(location pos);
void draw_laser (location pos, int dir);					//enum Direction dir
void draw_angled_laser(location pos, int dir, int angle);	//enum Direction dir
void draw_figure(pawn *figure);
void draw_mirror_destroyed(location pos);
void draw_king_destroyed(location pos);

/*module type declaration*/

/*module data declaration*/

/*module procedure declaration*/

/*ALLE PROTOTYPEN DER GRAFIKFUNKTIONEN*/

/*****************************************************************************/
/*  End Header  : ErrorHandler                                               */
/*****************************************************************************/
#endif

