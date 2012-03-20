#ifndef LASERCHESS_H
#define LASERCHESS_H

/*****************************************************************************/
/*	o o o o      Berner Fachhochschule										 */
/*		  :...o  Technik und Informatik										 */
/*****************************************************************************/
/*  Header     : LaserChess/Mapdefinition                       Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   :                                                             */
/*                                                                           */
/*  Procedures :                                                             */
/*                                                                           */
/*  Author     : C. Stoller  												 */
/* 																			 */
/*  Email	   : stolc2@bfh.ch  						                     */
/*                                                                           */
/*  History    : 17.03.2012  File created                                    */
/*                                                                           */
/*  File       : LaserChess.h                                                */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/


enum Affiliation {PLAYER_RED = 1, PLAYER_BLUE = 2};
enum Species {KING, MIRROR, SPLITTER, WALL, LASER};
enum Orientation {TOP_RIGHT, TOP_LEFT, BOTTOM_LEFT, BOTTOM_RIGHT};
enum Direction {LEFT, UP, RIGHT, DOWN};


#define NORM(a) (a<0 ? a+=4 : (a>3 ? a%=4 : a))

#define ROTATE_LEFT(a) a++; NORM(a)
#define ROTATE_RIGHT(a) a--; NORM(a)

#define ANZ_FIGURES		14
// Map Koordinaten, 0,0 ist unten links
typedef struct {
	int x;
	int y;
} location;

// Deklaration der Spielfigur
typedef struct {
	enum Affiliation PLAYER;
	enum Species TYPE;
	enum Orientation DIR;
	location Pos;
}pawn;

// Globale Variable

pawn *map[PLAYGROUND_X_MAX][PLAYGROUND_Y_MAX];


#endif
