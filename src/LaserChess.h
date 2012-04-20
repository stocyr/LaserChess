#ifndef LASERCHESS_H
#define LASERCHESS_H

/*****************************************************************************/
/*	o o o o      Berner Fachhochschule										 */
/*		  :...o  Technik und Informatik										 */
/*****************************************************************************/
/*  Header     : LaserChess/Mapdefinition                       Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Header for main() (LaserChess.c)                            */
/*                                                                           */
/*  Procedures : -                                                           */
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

// TITLE in ASCII art:
#define TITLE \
"#                                    #####                              \n" \
"#         ##    ####  ###### #####  #     # #    # ######  ####   ####  \n" \
"#        #  #  #      #      #    # #       #    # #      #      #      \n" \
"#       #    #  ####  #####  #    # #       ###### #####   ####   ####  \n" \
"#       ######      # #      #####  #       #    # #           #      # \n" \
"#       #    # #    # #      #   #  #     # #    # #      #    # #    # \n" \
"####### #    #  ####  ###### #    #  #####  #    # ######  ####   ####  \n" \

enum Affiliation {PLAYER_RED, PLAYER_BLUE}; //enum Affiliation {PLAYER_RED = 0, PLAYER_BLUE = 1}; //Weil in Spiel.c PLAYER = !PLAYER; Changed by kasen1
enum Species {KING, MIRROR, SPLITTER, WALL, CANNON};
enum Orientation {EAST, NORTH, WEST, SOUTH, NORTH_EAST = 0, NORTH_WEST = 1, SOUTH_WEST = 2, SOUTH_EAST = 3};
enum Direction {RIGHT, UP, LEFT, DOWN};
enum Angle {CCW = 1, CW = -1};
enum Spielmodus {NORMALMODE, SETMODE, OPEN, EXIT, INVALID_INPUT};
enum Gamecontrol {EXIT_GAME, KING_RED_DEST, KING_BLUE_DEST, NONE, MIRROR_RED_DEST, MIRROR_BLUE_DIST};
enum Sound {Laser, Reflexion, Destruction, Victory};

#define FOREVER 1

#define NORM(a) (a<0 ? a+=4 : (a>3 ? a%=4 : a))

#define ABS(a) (a<0 ? -(a) : a)

#define IS_EVEN(x) (!((x)%2))

#define ROTATE_LEFT(a) a++; NORM(a)
#define ROTATE_RIGHT(a) a--; NORM(a)

#define ANZ_FIGURES		14

// Figurearray zuerst rot dann blau, umrechnen
#define RED_FIG(i) (i/2)
#define BLUE_FIG(i)	((i/2)+7)

// Map-Koordinatenstruct
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

// Globale Variablen
const char *AppPath; //EXE-Pfad

pawn *map[8][6];

#endif
