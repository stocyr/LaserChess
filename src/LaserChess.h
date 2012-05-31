#ifndef LASERCHESS_H
#define LASERCHESS_H

/*****************************************************************************/
/*  o o o o      Berner Fachhochschule                                       */
/*        :...o  Technik und Informatik                                      */
/*****************************************************************************/
/*  Header     : LaserChess/Mapdefinition                       Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Header for main() (LaserChess.c)                            */
/*                                                                           */
/*  Procedures : -                                                           */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/*                                                                           */
/*  Email      : stolc2@bfh.ch                                               */
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
"------------------------------------------------------------------------\n" \
"#                                    #####                              \n" \
"#         ##    ####  ###### #####  #     # #    # ######  ####   ####  \n" \
"#        #  #  #      #      #    # #       #    # #      #      #      \n" \
"#       #    #  ####  #####  #    # #       ###### #####   ####   ####  \n" \
"#       ######      # #      #####  #       #    # #           #      # \n" \
"#       #    # #    # #      #   #  #     # #    # #      #    # #    # \n" \
"####### #    #  ####  ###### #    #  #####  #    # ######  ####   ####  \n" \
"------------------------------------------------------------------------\n" \

// Spielerzugehörtigkeit
enum Affiliation {PLAYER_RED, PLAYER_BLUE}; //enum Affiliation {PLAYER_RED = 0, PLAYER_BLUE = 1}; //Weil in Spiel.c PLAYER = !PLAYER; Changed by kasen1

// Verschiedene Figur-Typen
enum Species {KING, MIRROR, SPLITTER, WALL, CANNON};

// Orientierung der >>Figur-Typen<<
enum Orientation {EAST, NORTH, WEST, SOUTH, NORTH_EAST = 0, NORTH_WEST = 1, SOUTH_WEST = 2, SOUTH_EAST = 3};

// Richtungsangabe, wird nur in zusammenhang mit dem Laserstrahl verwendet
enum Direction {RIGHT, UP, LEFT, DOWN};

// Drehwinkel in 90°-Schritten: Rechtsdrehung = -1, Linksdrehung = 1 -> Kooperiert mit dem Enum "Direction"
enum Angle {CCW = 1, CW = -1};

// Spielmodus für Konsolen-Menu
enum Spielmodus {NORMALMODE, SETMODE, STARTOPEN, OPEN, EXIT, INVALID_INPUT, EASTER_EGG1, EASTER_EGG2, EASTER_EGG3, EASTER_EGG4};

// Modul-internes Enum
enum Gamecontrol {EXIT_GAME, KING_RED_DEST, KING_BLUE_DEST, NONE, MIRROR_RED_DEST, MIRROR_BLUE_DIST};

// Bezeichnung der verschiedenen Sounds
enum Sound {Laser, Reflection, Destruction, Victory, Ignore, Intro, Music, Pling, Bell};

// usability Makros
#define FOREVER 1
#define IS_EVEN(x) (!((x)%2))
#define ABS(a) (a<0 ? -(a) : a)
#define STRINGS_EQUAL(a,b) (strcmp(a,b)==0 ? 1 : 0)

// Normierung für das Enum "Direction"
#define NORM(a) (a<0 ? a+=4 : (a>3 ? a%=4 : a))

// Richtungsänderung für das Enum "Direction"
#define ROTATE_LEFT(a) a++; NORM(a)
#define ROTATE_RIGHT(a) a--; NORM(a)

// Spiel-Logik / Grösse
#define ANZ_FIGURES 14

#define PLAYGROUND_X_MAX 9                        //Anzahl Felder - Breite
#define PLAYGROUND_Y_MAX 7                        //Anzahl Felder - Höhe

// Figurearray zuerst rot dann blau, umrechnen
#define RED_FIG(i) (i/2)
#define BLUE_FIG(i) ((i/2)+ (ANZ_FIGURES / 2))

//Ordnerpfad zu den vordefinierten Maps (Pfad relativ zu *ApplicationPath)
#define MAP_DIR "\\maps"

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
const char *AppPath;	//EXE-Pfad
char Sound_On;			//On/Off Sound
const char *MapPath;	//Pfad der Map, falls direkt Map geoeffnet wurde

// Map, welche jede Figurposition "speichert"
pawn *map[PLAYGROUND_X_MAX][PLAYGROUND_Y_MAX];

#endif
