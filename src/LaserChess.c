/*****************************************************************************/
/*	o o o o      Berner Fachhochschule										 */
/*		  :...o  Technik und Informatik										 */
/*****************************************************************************/
/*  Module     : LaserChess/Mapdefinition                       Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   :                                                             */
/*                                                                           */
/*  Procedures : main()                                                      */
/*                                                                           */
/*  Author     : M. Bärtschi 												 */
/* 																			 */
/*  Email	   : bartm9@bfh.ch  						                     */
/*                                                                           */
/*  History    : 12.03.2012  File created                                    */
/*                                                                           */
/*  File       : LaserChess.c                                                */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/


#include <stdio.h>
#include <stdlib.h>

enum Affiliation {PLAYER_RED, PLAYER_BLUE};
enum Species {KING, MIRROR, SPLITTER, WALL};
enum Orientation {TR, TB, BL, BR};

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

// Definition aller Spielfiguren
pawn figure[10] = {
		[0].PLAYER = PLAYER_RED,
		[0].TYPE = KING,
		[0].DIR = TR,
		[0].Pos = {4, 0},

		[1].PLAYER = PLAYER_BLUE,
		[1].TYPE = KING,
		[1].DIR = TR,
		[1].Pos = {4, 5},

		[2].PLAYER = PLAYER_RED,
		[2].TYPE = MIRROR,
		[2].DIR = TR,
		[2].Pos = {1, 1},

		[3].PLAYER = PLAYER_RED,
		[3].TYPE = MIRROR,
		[3].DIR = TR,
		[3].Pos = {1, 2},

		[4].PLAYER = PLAYER_RED,
		[4].TYPE = MIRROR,
		[4].DIR = TR,
		[4].Pos = {1, 3},

		[5].PLAYER = PLAYER_BLUE,
		[5].TYPE = MIRROR,
		[5].DIR = TR,
		[5].Pos = {7, 5},

		[6].PLAYER = PLAYER_BLUE,
		[6].TYPE = MIRROR,
		[6].DIR = TR,
		[6].Pos = {7, 4},

		[7].PLAYER = PLAYER_BLUE,
		[7].TYPE = MIRROR,
		[7].DIR = TR,
		[7].Pos = {7, 3}

};


	pawn *(Map[8][6]);

int main(void) {
	Map[0][0] = &figure[0];
	Map[8][6] = &figure[3];

	printf("%d\n\n", ((Map[0][0])->Pos.x));
	printf("%d\n\n", ((Map[8][6])->Pos.x));
	printf("%d\n%d\n%d\n%d, %d", figure[0].PLAYER, figure[0].TYPE, figure[0].DIR, figure[0].Pos.x, figure[0].Pos.y);

	system("pause");
	return EXIT_SUCCESS;
}
