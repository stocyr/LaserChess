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

void create_figures(pawn *figure) // Liefert Pointer auf Array der Spielfigren an Stelle 0
{
	// Definition aller Spielfiguren
	figure[0].PLAYER = PLAYER_RED;
	figure[0].TYPE = KING;
	figure[0].DIR = SOUTH;
	figure[0].Pos.x = 3;
	figure[0].Pos.y = 5;

	figure[1].PLAYER = PLAYER_RED;
	figure[1].TYPE = CANNON;
	figure[1].DIR = SOUTH;
	figure[1].Pos.x = 0;
	figure[1].Pos.y = 5;

	figure[2].PLAYER = PLAYER_RED;
	figure[2].TYPE = WALL;
	figure[2].DIR = NORTH;
	figure[2].Pos.x = 4;
	figure[2].Pos.y = 5;

	figure[3].PLAYER = PLAYER_RED;
	figure[3].TYPE = MIRROR;
	figure[3].DIR = SOUTH_WEST;
	figure[3].Pos.x = 2;
	figure[3].Pos.y = 5;

	figure[4].PLAYER = PLAYER_RED;
	figure[4].TYPE = MIRROR;
	figure[4].DIR = NORTH_EAST;
	figure[4].Pos.x = 4;
	figure[4].Pos.y = 3;

	figure[5].PLAYER = PLAYER_RED;
	figure[5].TYPE = MIRROR;
	figure[5].DIR = NORTH_EAST;
	figure[5].Pos.x = 0;
	figure[5].Pos.y = 2;

	figure[6].PLAYER = PLAYER_RED;
	figure[6].TYPE = MIRROR;
	figure[6].DIR = NORTH_EAST;
	figure[6].Pos.x = 2;
	figure[6].Pos.y = 1;

	figure[7].PLAYER = PLAYER_BLUE;
	figure[7].TYPE = KING;
	figure[7].DIR = NORTH;
	figure[7].Pos.x = 4;
	figure[7].Pos.y = 0;

	figure[8].PLAYER = PLAYER_BLUE;
	figure[8].TYPE = CANNON;
	figure[8].DIR = NORTH;
	figure[8].Pos.x = 7;
	figure[8].Pos.y = 0;

	figure[9].PLAYER = PLAYER_BLUE;
	figure[9].TYPE = WALL;
	figure[9].DIR = NORTH;
	figure[9].Pos.x = 3;
	figure[9].Pos.y = 0;

	figure[10].PLAYER = PLAYER_BLUE;
	figure[10].TYPE = MIRROR;
	figure[10].DIR = NORTH_EAST;
	figure[10].Pos.x = 5;
	figure[10].Pos.y = 0;

	figure[11].PLAYER = PLAYER_BLUE;
	figure[11].TYPE = MIRROR;
	figure[11].DIR = SOUTH_WEST;
	figure[11].Pos.x = 3;
	figure[11].Pos.y = 2;

	figure[12].PLAYER = PLAYER_BLUE;
	figure[12].TYPE = MIRROR;
	figure[12].DIR = SOUTH_WEST;
	figure[12].Pos.x = 7;
	figure[12].Pos.y = 3;

	figure[13].PLAYER = PLAYER_BLUE;
	figure[13].TYPE = MIRROR;
	figure[13].DIR = SOUTH_WEST;
	figure[13].Pos.x = 5;
	figure[13].Pos.y = 4;
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
	int a = 0; //Auswahlvariable
	printf(TITLE);

	printf("Welcome to Laserchess\n\nPress\n1 - To start normal mode\n2 - To start placing mode\n3 - Exit\n ");
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
				draw_figure(&figure[i]);								//!!!& hinzugefügt (jascha)
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

	// initialize graphics and load images:
	if(init_figure_images() == 0)
	{
		// wenn image load failed: error
		printf("Image loading failed. Exiting");
		return;
	}
	draw_playground();
	if(MODE == SETMODE)
	{
		set_figure_positions(figure);
	}
	else
	{
		for(i = 0; i < ANZ_FIGURES; i++)
		{
			printf("%d\n", ((figure[i]).Pos.x));
			map[figure[i].Pos.x][figure[i].Pos.y] = &figure[i];
			draw_figure(&figure[i]);
		}
	}
}

int gfxmain(int argc, char* argv[], const char *ApplicationPath)
{

	//////////////////////////////////
	enum Spielmodus MODE = menu();
	if(MODE == EXIT)
	{

		printf("BYEBYE!\n");

		system("pause");
		return EXIT_SUCCESS;
	}
	pawn figure[ANZ_FIGURES];
	create_figures(figure);

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
	system("pause");
	return EXIT_SUCCESS;
}
