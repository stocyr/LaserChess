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

#include "Grafik.h"
#include "LaserChess.h"
//#include "Logik.h"

// Definition aller Spielfiguren
pawn figure[10] = {
		[0].PLAYER = PLAYER_RED,
		[0].TYPE = KING,
		[0].DIR = TOP_RIGHT,
		[0].Pos = {4, 0},

		[1].PLAYER = PLAYER_BLUE,
		[1].TYPE = KING,
		[1].DIR = TOP_RIGHT,
		[1].Pos = {4, 5},

		[2].PLAYER = PLAYER_RED,
		[2].TYPE = MIRROR,
		[2].DIR = TOP_RIGHT,
		[2].Pos = {1, 1},

		[3].PLAYER = PLAYER_RED,
		[3].TYPE = MIRROR,
		[3].DIR = TOP_RIGHT,
		[3].Pos = {1, 2},

		[4].PLAYER = PLAYER_RED,
		[4].TYPE = MIRROR,
		[4].DIR = TOP_RIGHT,
		[4].Pos = {1, 3},

		[5].PLAYER = PLAYER_BLUE,
		[5].TYPE = MIRROR,
		[5].DIR = TOP_RIGHT,
		[5].Pos = {7, 5},

		[6].PLAYER = PLAYER_BLUE,
		[6].TYPE = MIRROR,
		[6].DIR = TOP_RIGHT,
		[6].Pos = {7, 4},

		[7].PLAYER = PLAYER_BLUE,
		[7].TYPE = MIRROR,
		[7].DIR = TOP_RIGHT,
		[7].Pos = {7, 3}

};


int main(void) {
	/*
	map[0][0] = &figure[0];
	map[7][5] = &figure[3];

	printf("%d\n\n", ((map[0][0])->Pos.x));
	printf("%d\n\n", ((map[7][5])->Pos.x));
	printf("%d\n%d\n%d\n%d, %d", figure[0].PLAYER, figure[0].TYPE, figure[0].DIR, figure[0].Pos.x, figure[0].Pos.y);

	// Figur um 90 ccw drehen
	ROTATE_LEFT(map[7][5]->DIR);
	ROTATE_LEFT(map[7][5]->DIR);
	ROTATE_LEFT(map[7][5]->DIR);
	ROTATE_LEFT(map[7][5]->DIR);

	printf("%d\n", figure[3].DIR);
	*/
	system("pause");
	return EXIT_SUCCESS;
}
