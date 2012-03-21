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
#include "Spiel.h"
#include "Logik.h"


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

enum Spielmodus menu(void)
{
	enum Spielmodus MODE = NORMALMODE;
	int a = 0;
	printf ("#                                    #####                              \n"
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
		MODE = NORMALMODE;
		break;
	case 2:
		MODE = SETMODE;
		break;
	case 3:
		MODE = EXIT;
		break;
	default:
		break;
	}
	return MODE;
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
	MouseInfoType MouseEvent;

	enum Affiliation PLAYER = PLAYER_RED;
	enum Zustand {READ_POS, ROTATE} STATE;
	STATE = READ_POS;

	while(i < ANZ_FIGURES)
	{
		switch (STATE)
		{
		case READ_POS:
			//Holt Maus Status
			mouse_pos = mouseclick_to_map();
			if(mouse_pos.x >= 0)
			{
				//Playerunterscheiden wegen unterschiedlicher Addressierung im Figurearray
				if(PLAYER == PLAYER_RED)
				{
					figure[RED_FIG(i)].Pos.x = mouse_pos.x;
					figure[RED_FIG(i)].Pos.y = mouse_pos.y;
				}
				else
				{
					figure[BLUE_FIG(i)].Pos.x = mouse_pos.x;
					figure[BLUE_FIG(i)].Pos.y = mouse_pos.y;
				}
				draw_figure(&figure[i]);
				STATE = ROTATE;
			}
			break;
		case ROTATE:
			//Wenn 2. Mal auf die Figur gedrückt wird, ist der Zug beendet
			MouseEvent = GetMouseEvent();
			if(MouseEvent.ButtonState & W_BUTTON_PRESSED)
			{
				//Player toggeln
				if(PLAYER == PLAYER_RED)
				{
					PLAYER = PLAYER_BLUE;
				}
				else
				{
					PLAYER = PLAYER_RED;
				}
				STATE = READ_POS;
				i++;
			}
			else
			{
				//Wenn rechte Maustaste gedrückt, dreht es rechts
				if(MouseEvent.ButtonState & W_BUTTON_RIGHT)
				{
					figure->DIR = ROTATE_RIGHT(figure->DIR);
					draw_figure(&figure[i]);
				}
			}
			break;
		}

	}
}

/*****************************************************************************/
/*  End Function: set_figure_positions(pawn *figure)                         */
/*****************************************************************************/


void init_game(pawn *figure, enum Spielmodus MODE)
{
	int i = 0;
	draw_playground();
	if(MODE == SETMODE)
	{
		set_figure_positions(figure);
	}
	else
	{
		for(i = 0; i < ANZ_FIGURES; i++)
		{
			map[figure[i].Pos.x][figure[i].Pos.y] = &figure[i];
			draw_figure(figure[i]);
		}
	}
}

int main(void) {

	//////////////////////////////////
	enum Spielmodus MODE = menu();
	if(MODE == EXIT)
	{
		printf("Tschüss");
		system("pause");
		return EXIT_SUCCESS;
	}
	pawn *figure = create_figures();

	init_game(figure, MODE);

	spiel();



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
	return EXIT_SUCCESS;
}
