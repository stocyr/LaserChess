/*****************************************************************************/
/*	o o o o      Berner Fachhochschule										 */
/*		  :...o  Technik und Informatik										 */
/*****************************************************************************/
/*  Module     : LaserChess/gfxmain                             Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : main()                                                      */
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
/*  Function   : create_figures                                 Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Initializes all Figures from a received figure array. Sets  */
/*               Figures to the default Mapposition. Currently initializes   */
/*               14 Figures. (Optional: Splitter not defined in this version)*/
/*                                                                           */
/*  Input Para : Pointer to the original figure array in the main-procedure  */
/*                                                                           */
/*  Output     : None                                                        */
/*                                                                           */
/*  Author     : M. Bärtschi                                                 */
/*                                                                           */
/*  Email      : bartm9@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

void create_figures(pawn *figure)
{
	// Initialisierung aller Spielfiguren
	// Rote Spielfiguren
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
	figure[2].DIR = SOUTH;
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

	// Blaue Spielfiguren
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
/*  Function   : menu                                           Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : This is a minimal menu. User can choose between modes       */
/*               NORMAL, SETMODE and quit the game.                          */
/*                                                                           */
/*  Input Para : None                                                        */
/*                                                                           */
/*  Output     : Play mode enum, -1 if wrong keyboard input.                 */
/*                                                                           */
/*  Author     : M. Bärtschi                                                 */
/*                                                                           */
/*  Email      : bartm9@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

enum Spielmodus menu(void)
{
	enum Spielmodus MODE = NORMALMODE;
	int a = 0; // Auswahlvariable, wird mit 0 initialisiert, dass wenn scanf nichts in a schreibt, der default zweig ausgeführt wird

	printf("\n\nPress\n1 - To start normal mode\n2 - To start placing mode\n3 - Open Existing\n4 - Exit\n ");
	scanf("%d",&a);
	switch(a)
	{
	case 1:
		MODE = NORMALMODE;
		return MODE;
	case 2:
		MODE = SETMODE;
		return MODE;
	case 3:
		MODE = OPEN;
		return MODE;
	case 4:
		MODE = EXIT;
		return MODE;
	default:	// Wenn andere/ungültige Eingabe, Eingabebuffer löschen, -1 zurückgeben
		while(getchar() != '\n');
		MODE = -1;
		printf("Ungueltige Eingabe");
		return MODE;
	}
}



/*****************************************************************************/
/*  Function   : set_figure_positions                           Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : The Player can set his pawn freely on the map. The figures  */
/*               in the array are sorted by color. To toggle the player, I   */
/*               use i/2 for red and (i/2)+7 for blue.                       */
/*                                                                           */
/*  Input Para : Pointer to Array of all the figures                         */
/*                                                                           */
/*  Output     : none                                                        */
/*                                                                           */
/*  Author     : M. Bärtschi                                                 */
/*                                                                           */
/*  Email      : bartm9@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

int set_figure_positions(pawn *figure)
{
	int i = 0;								// Countervariable um Array durchzuzählen
	location mouse_pos, figure_pos;			// Zwei Position Structs, wo die letdzten zwei Mousecklicks gespeichert werden
	MouseInfoType MouseEvent;				// Struct wo Mouseevents gespeicert werden

	enum Affiliation PLAYER = PLAYER_RED;
	enum Zustand {READ_POS, ROTATE} STATE;
	STATE = READ_POS;

	while(i < ANZ_FIGURES)					// Das ganze Figurearray durchgehen
	{
		switch (STATE)
		{
		case READ_POS:
		// Hier wird die nächste Figur auf die Map gezeichnet
			mouse_pos = mouseclick_to_map();	//Holt Maus Status
			figure_pos = mouse_pos;			// Figure_pos ist die Figur die selektiert wird

			if(is_inside_map(mouse_pos) && !is_figure(mouse_pos))
			{
				//Playerunterscheiden wegen unterschiedlicher Addressierung im Figurearray
				if(PLAYER == PLAYER_RED)
				{
					figure[RED_FIG(i)].Pos.x = mouse_pos.x;		// Mapkoordinaten in der Figur speichern
					figure[RED_FIG(i)].Pos.y = mouse_pos.y;
					draw_figure(&figure[RED_FIG(i)]);			// Figur zeichnen
					map[mouse_pos.x][mouse_pos.y] = &figure[RED_FIG(i)];	// Figur auf Map setzen
				}
				else
				{
					figure[BLUE_FIG(i)].Pos.x = mouse_pos.x;
					figure[BLUE_FIG(i)].Pos.y = mouse_pos.y;
					draw_figure(&figure[BLUE_FIG(i)]);
					map[mouse_pos.x][mouse_pos.y] = &figure[BLUE_FIG(i)];
				}

				STATE = ROTATE;
			}
			break;
		case ROTATE:
		// Wenn 2. Mal auf die Figur gedrückt wird, ist der Zug beendet, wenn am mouserad gedreht wird, wird die Figur gedreht
			MouseEvent = GetMouseEvent();	// Holt Mouseevent

			if(MouseEvent.ButtonState & W_BUTTON_PRESSED)
			{
				mouse_pos.x = MouseEvent.MousePosX;
				mouse_pos.y = MouseEvent.MousePosY;
				mouse_pos = pixel_to_map(mouse_pos);
				// Wenn ein 2. Mal gültig gecklickt wird, figur auf Maparray speichern, Player Wechseln
				if(is_inside_map(mouse_pos))
				{
					PLAYER = !PLAYER;	// Player toggeln
					STATE = READ_POS;
					i++;				// Nächste Figur zum Setzen
				}
			}
			else
			{
				// Man kann so lange drehen, bis ein 2. mal geklickt wird
				if(MouseEvent.ButtonState & W_MOUSE_WHEEL_CHANGE)
				{
					if(MouseEvent.MouseWheelDelta > 0)
					{
						// Figur solange drehen bis Taste gedrückt
						ROTATE_LEFT(map[figure_pos.x][figure_pos.y]->DIR);
					}
					else
					{
						ROTATE_RIGHT(map[figure_pos.x][figure_pos.y]->DIR);
					}
					// Zeichnet die Figur neu, wenn sie gedreht wurde
					draw_figure(map[figure_pos.x][figure_pos.y]);
				}
			}
			break;
		}
		if(IsKeyPressReady() && (GetKeyPress() == W_KEY_CLOSE_WINDOW)) //Fenster schliessen geklickt
		{
			// KeyPress Buffer löschen
			while(IsKeyPressReady())
			{
				GetKeyPress();
			}
			CloseGraphic(); //Grafikfenster schliessen
			return -1;
		}
	}
	return 0;
}



/*****************************************************************************/
/*  Function   : init_game                                      Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Initializes the game. Draws the graphics and places the     */
/*               figures.                                                    */
/*                                                                           */
/*  Input Para : Array of all the figures, play mode (to decide whether to   */
/*               place all the figures to initialized state or let the users */
/*               place them alternating)                                     */
/*                                                                           */
/*  Output     : none                                                        */
/*                                                                           */
/*  Author     : M. Bärtschi                                                 */
/*                                                                           */
/*  Email      : bartm9@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

int init_game(pawn *figure, enum Spielmodus MODE)
{
	int i = 0;

	// initialize graphics and load images:
	if(init_figure_images() == -1)
	{
		// wenn image load failed: error
		printf("Image loading failed. Exiting\n");	//Exiting? xD
		return 0;
	}

	draw_playground();		//Spielfeld zeichnen

	if(MODE == SETMODE)
	{
		// Figuren manuell setzen
		if(set_figure_positions(figure) == -1)
		{
			return 0;
		}
	}
	else
	{
		// Figuren nach vordefinierter Aufstellung setzen
		if(MODE == OPEN)
		{
			FILE  *fp;
			fp = fopen(path_handler(AppPath, "\\maps\\Aufstellung.txt"), "r");
			if(!(fp == NULL))
			{
				for(i = 0; i < ANZ_FIGURES; i++)
				{
					fscanf(fp, "%u", &(figure[i].PLAYER));
					fscanf(fp, "%u", &(figure[i].TYPE));
					fscanf(fp, "%u", &(figure[i].DIR));
					fscanf(fp, "%d", &(figure[i].Pos.x));
					fscanf(fp, "%d", &(figure[i].Pos.y));
				}
				fclose(fp);
			}
			else
			{
				printf("Error: cannot open file");
				return 0;
			}

		}
		for(i = 0; i < ANZ_FIGURES; i++)
		{
			map[figure[i].Pos.x][figure[i].Pos.y] = &figure[i];
			draw_figure(&figure[i]);
		}
	}
	return 1;
}



/*****************************************************************************/
/*  Function   : clear_map_array                                Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : clears the map array (writes all positions to NULL)         */
/*                                                                           */
/*  Input Para : none                                                        */
/*                                                                           */
/*  Output     : none                                                        */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/*                                                                           */
/*  Email      : stolc2@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

void clear_map_array(void)
{
	int x, y;

	for(y = 0; y < PLAYGROUND_Y_MAX; y++)
	{
		for(x = 0; x < PLAYGROUND_X_MAX; x++)
		{
			map[x][y] = NULL;
		}
	}
}



/*****************************************************************************/
/*  Function   : gfxmain                                        Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Uber-main function. Will be called FIRST!                   */
/*                                                                           */
/*  Input Para : system console call parameters. (OS specific)               */
/*                                                                           */
/*  Output     : none                                                        */
/*                                                                           */
/*  Author     : M. Bärtschi                                                 */
/*                                                                           */
/*  Email      : bartm9@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

int gfxmain(int argc, char* argv[], const char *ApplicationPath)
{
	AppPath = ApplicationPath;	// EXE-Pfad uebergeben, damit global verwendbar

	int init_succeed = 0;
	enum Spielmodus MODE;
	pawn figure[ANZ_FIGURES];	// Structarray für die Figuren

	printf("\n"TITLE);
	printf("\nWelcome to Laserchess");

	while(FOREVER)
	{
		clear_map_array();

		do
		{
			MODE = menu();		// Bekommt einer der 3 Modes zurück
		}
		while( MODE < 0);

		if(MODE == EXIT)
		{

			printf("\nBYEBYE!!!\n");

			WaitMs (2000);	// 2 Sekunden warten bis Fenster schliesst
			return EXIT_SUCCESS;
		}

		create_figures(figure);
		init_succeed = init_game(figure, MODE);
		if(init_succeed)
		{
			spiel(figure);
		}
	}


	system("pause");
	return EXIT_SUCCESS;
}
