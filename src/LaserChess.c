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
#include "window.h"
#include "LaserChess.h"
//#include "Logik.h"


/*****************************************************************************/
/*  Function   : create_figures()                               Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Generats and save all Figures to an Array. Set the Figures  */
/*               to the default Mapposition. Creats currently 14 Figures.    */
/*                                                                           */
/*  Input Para :                                                             */
/*                                                                           */
/*  Output     : Ptr. to the Figure[0]                                       */
/*                                                                           */
/*  Author     : M. Bärtschi                                                 */
/*                                                                           */
/*  Email      : bartm9@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

pawn *create_figures(void) // Liefert Pointer auf Array der Spielfigren an Stelle 0
{
// Definition aller Spielfiguren
	pawn *fig_ptr;

	pawn figure[ANZ_FIGURES] = {
		[0].PLAYER = PLAYER_RED,
		[0].TYPE = KING,
		[0].DIR = DOWN,
		[0].Pos = {3, 5},

		[1].PLAYER = PLAYER_RED,
		[1].TYPE = LASER,
		[1].DIR = DOWN,
		[1].Pos = {0, 5},

		[2].PLAYER = PLAYER_RED,
		[2].TYPE = WALL,
		[2].DIR = UP,
		[2].Pos = {4, 5},

		[3].PLAYER = PLAYER_RED,
		[3].TYPE = MIRROR,
		[3].DIR = BOTTOM_LEFT,
		[3].Pos = {2, 5},

		[4].PLAYER = PLAYER_RED,
		[4].TYPE = MIRROR,
		[4].DIR = TOP_RIGHT,
		[4].Pos = {4, 3},

		[5].PLAYER = PLAYER_RED,
		[5].TYPE = MIRROR,
		[5].DIR = TOP_RIGHT,
		[5].Pos = {0, 2},

		[6].PLAYER = PLAYER_RED,
		[6].TYPE = MIRROR,
		[6].DIR = TOP_RIGHT,
		[6].Pos = {2, 1},

		[7].PLAYER = PLAYER_BLUE,
		[7].TYPE = KING,
		[7].DIR = UP,
		[7].Pos = {4, 0},

		[8].PLAYER = PLAYER_BLUE,
		[8].TYPE = LASER,
		[8].DIR = UP,
		[8].Pos = {7, 0},

		[9].PLAYER = PLAYER_BLUE,
		[9].TYPE = WALL,
		[9].DIR = UP,
		[9].Pos = {3, 0},

		[10].PLAYER = PLAYER_BLUE,
		[10].TYPE = MIRROR,
		[10].DIR = TOP_RIGHT,
		[10].Pos = {5, 0},

		[11].PLAYER = PLAYER_BLUE,
		[11].TYPE = MIRROR,
		[11].DIR = BOTTOM_LEFT,
		[11].Pos = {3, 2},

		[12].PLAYER = PLAYER_BLUE,
		[12].TYPE = MIRROR,
		[12].DIR = BOTTOM_LEFT,
		[12].Pos = {7, 3},

		[13].PLAYER = PLAYER_BLUE,
		[13].TYPE = MIRROR,
		[13].DIR = BOTTOM_LEFT,
		[13].Pos = {5, 4}

	};
	fig_ptr = &figure[0];
	return fig_ptr;
}
/*****************************************************************************/
/*  End Function: create_figures()                                           */
/*****************************************************************************/

/*****************************************************************************/
/*  Function   : mouseclick_to_map()                            Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Get Mose-Clicks and returns the Mapcoordinate.              */
/*                                                                           */
/*  Input Para :                                                             */
/*                                                                           */
/*  Output     : Returns location struct, of the field who was hit or -1     */
/*               when the click was beyond the map                           */
/*  Author     : M. Bärtschi                                                 */
/*                                                                           */
/*  Email      : bartm9@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/
location mouseclick_to_map(void)
{
	MouseInfoType MouseEvent;
	//Get and analyze mouse-events
	MouseEvent = GetMouseEvent();
	location pos;

	if(MouseEvent.ButtonState & W_BUTTON_PRESSED)
	{
		/* Get Click-position */
		pos.x   = MouseEvent.MousePosX;
		pos.y   = MouseEvent.MousePosY;
	}
	else
	{
		pos.x = -1;
		pos.y = -1;
	}
	return /*pixel_to_map*/(pos);
}
/*****************************************************************************/
/*  End Function: mouseclick_to_map()                                        */
/*****************************************************************************/


/*****************************************************************************/
/*  Function   : menu                                           Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : This should be a menu.                                      */
/*                                                                           */
/*  Input Para :                                                             */
/*                                                                           */
/*  Output     :                                                             */
/*                                                                           */
/*  Author     : M. Bärtschi                                                 */
/*                                                                           */
/*  Email      : bartm9@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

void menu(void)
{
	int a = 0;

	printf("#                                    #####                              \n"
		   "#         ##    ####  ###### #####  #     # #    # ######  ####   ####  \n"
		   "#        #  #  #      #      #    # #       #    # #      #      #      \n"
		   "#       #    #  ####  #####  #    # #       ###### #####   ####   ####  \n"
		   "#       ######      # #      #####  #       #    # #           #      # \n"
		   "#       #    # #    # #      #   #  #     # #    # #      #    # #    # \n"
		   "####### #    #  ####  ###### #    #  #####  #    # ######  ####   ####  \n");
	printf("Welcome to Laserchess\nPress\n1 - To start normal mode\n2 - To start placing mode\n3 - Exit ");
	scanf("%d",&a);
	switch(a)
	{
	case 1:

		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
}
/*****************************************************************************/
/*  End Function: menu                                                       */
/*****************************************************************************/

/*****************************************************************************/
/*  Function   : set_figure_positions(pawn *figure)             Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : The Player can set his pawn freely to the map. The figures  */
/*               in the array are by the color. To toggle the player I use   */
/*               i/2 for red and (i/2)+7 for blue.                           */
/*                                                                           */
/*  Input Para : Array of all figures                                        */
/*                                                                           */
/*  Output     : none                                                        */
/*                                                                           */
/*  Author     : M. Bärtschi                                                 */
/*                                                                           */
/*  Email      : bartm9@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

void set_figure_positions(pawn *figure)
{
	int i = 0;
	location mouse_pos;
	enum Affiliation PLAYER = PLAYER_RED;
	while(i < ANZ_FIGURES)
	{
		switch (PLAYER)
		{
		case PLAYER_RED:
			mouse_pos = mouseclick_to_map();
			if(mouse_pos.x >= 0)
			{
				figure[(i/2)].Pos.x = mouse_pos.x;
				figure[(i/2)].Pos.y = mouse_pos.y;
				i++;
				PLAYER = PLAYER_BLUE;
			}
			break;
		case PLAYER_BLUE:
			mouse_pos = mouseclick_to_map();
			if(mouse_pos.x >= 0)
			{
				figure[(i/2)+7].Pos.x = mouse_pos.x;
				figure[(i/2)+7].Pos.y = mouse_pos.y;
				i++;
				PLAYER = PLAYER_RED;
			}
			break;
		}
	}
}

/*****************************************************************************/
/*  End Function: set_figure_positions(pawn *figure)                         */
/*****************************************************************************/


void init_game(pawn *figure)
{
	int i = 0;
	draw_playground();
	//if(SETMODE)			//noch definieren im menu
	{
		set_figure_positions(figure);
	}
	for(i = 0; i < ANZ_FIGURES; i++)
	{
		map[figure[i].Pos.x][figure[i].Pos.y] = &figure[i];
		printf("*%d*", figure[i].Pos.x);
		draw_figure(figure[i]);
	}
}

int main(void) {

	//////////////////////////////////

	pawn *figure = create_figures();

	init_game(figure);




	/////////////////////////////////

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
