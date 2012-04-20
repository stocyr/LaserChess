/*****************************************************************************/
/*	o o o o      Berner Fachhochschule										 */
/*		  :...o  Technik und Informatik										 */
/*****************************************************************************/
/*  Module     : LaserChess/gfxmain                             Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : main()                                                      */
/*																			 */
/*  Procedures : create_figures(), menu(), set_figure_positons(), init game()*/
/*			     clear_map_array(), gfxmain()								 */
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
#include <string.h>
#include <ctype.h>

#include "Grafik.h"
#include "window.h"
#include "LaserChess.h"
#include "Spiel.h"
#include "Logik.h"


/*****************************************************************************/
/*  Function   : create_figures                                 Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Initializes all figures from a received figure array. Sets  */
/*               figures to the default mapposition. Currently initializes   */
/*               14 figures. (Optional: Splitter not defined in this version)*/
/*                                                                           */
/*  Input Para : Pointer to the original figure array in the main-procedure  */
/*                                                                           */
/*  Output     : -                                                           */
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
/*  Input Para : -                                                           */
/*                                                                           */
/*  Output     : Play mode enum                                              */
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
	char string[80];

	printf("\nEnter command: ");

	// jetzt einen String einlesen, der optional auch aus "%d %s" bestehen kann
	gets(string);
	if(isdigit(string[0]))
	{
		a = string[0] - '0';
	}

	switch(a)					// Eingabe unterscheiden
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
		if(strcmp(string, "\x034\x020\x067\x065\x077\x069\x06E\x06E\x074") == 0)
		{
			// Wenn "4 gewinnt" eingegeben wurde
			MODE = EASTER_EGG;
			return MODE;
		}
		else
		{
			Sound_On = !Sound_On;
			if(Sound_On)
			{
				printf("Sound ON");
			}
			else
			{
				printf("Sound OFF");
			}
			MODE = INVALID_INPUT;
			return MODE;
		}
	case 5:
		MODE = EXIT;
		return MODE;
	default:	// Wenn andere/ungültige Eingabe, -1 zurückgeben
		MODE = INVALID_INPUT;
		printf("Ungueltige Eingabe");
		return MODE;
	}
}


/*****************************************************************************/
/*  Function   : set_figure_positions                           Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : The player can set his pawn freely on the map. The figures  */
/*               in the array are sorted by color. To toggle the player, I   */
/*               use i/2 for red and (i/2)+7 for blue.                       */
/*                                                                           */
/*  Input Para : Pointer to Array of all the figures                         */
/*                                                                           */
/*  Output     : returns -1 if exit button is pressed, otherwise 0           */
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
/*  Output     : if wild failure appears, returns 0, otherwise returns 1     */
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
			return 0;	// Wenn Figurensetzetn abgebrochen wurde
		}
	}
	else
	{
		// Figuren nach vordefinierter Aufstellung setzen
		if(MODE == OPEN)
		{
			FILE  *fp;

			// Aufstellung file öffnen
			char *p; //path
			fp = fopen(p=path_handler(AppPath, "\\maps\\Aufstellung.txt"), "r"); if(p!=NULL)free(p);
			if(!(fp == NULL))
			{
				for(i = 0; i < ANZ_FIGURES; i++)	// Solange einlesen, bis alle Figuren Werte haben
				{
					fscanf(fp, "%u", &(figure[i].PLAYER));
					fscanf(fp, "%u", &(figure[i].TYPE));
					fscanf(fp, "%u", &(figure[i].DIR));
					fscanf(fp, "%d", &(figure[i].Pos.x));
					fscanf(fp, "%d", &(figure[i].Pos.y));
				}
				fclose(fp);	// File schliessen
			}
			else
			{
				// Meldung wenn File nicht geöffnet werden konnte
				printf("Error: cannot open file");
				return 0;	// Fehlerwert zurückgeben
			}

		}
		// Alle Figuren auf der Map "platzieren" und zeichnen
		for(i = 0; i < ANZ_FIGURES; i++)
		{
			map[figure[i].Pos.x][figure[i].Pos.y] = &figure[i];
			draw_figure(&figure[i]);
		}
	}
	return 1;	// Initialisierung erfolgreich
}


/*****************************************************************************/
/*  Function   : clear_map_array                                Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Clears the map array (writes all positions to NULL)         */
/*                                                                           */
/*  Input Para : -                                                           */
/*                                                                           */
/*  Output     : -                                                           */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/*                                                                           */
/*  Email      : stolc2@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

void clear_map_array(void)
{
	int x, y;
	// Alle Felder der Map durchgehen
	for(y = 0; y < PLAYGROUND_Y_MAX; y++)
	{
		for(x = 0; x < PLAYGROUND_X_MAX; x++)
		{
			map[x][y] = NULL;	// Mit Nullpointer initialisieren
		}
	}
}


/*****************************************************************************/
/*  Function   : vier_gewinnt                                   Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : führt ein vier gewinnt spiel aus. (easter egg)    )         */
/*                                                                           */
/*  Input Para : -                                                           */
/*                                                                           */
/*  Output     : -                                                           */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/*                                                                           */
/*  Email      : stolc2@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

void easter_egg(void)
{
	MouseInfoType mouse_event;
	location new_mouse_pos, new_stone_position;
	int i;
	int figure_counter;
	enum Affiliation spieler = PLAYER_RED;
	pawn *actual_stone;

	// alle spielsteine generieren
	pawn figuren[PLAYGROUND_Y_MAX*PLAYGROUND_X_MAX / 2][2];

	// spielsteine auf typ [WALL] umsetzen
	for(i = 0; i < PLAYGROUND_Y_MAX*PLAYGROUND_X_MAX / 2; i++)
	{
		// spieler rot:
		figuren[i][PLAYER_RED].TYPE = WALL;
		figuren[i][PLAYER_RED].PLAYER = PLAYER_RED;
		figuren[i][PLAYER_RED].DIR = 0;
		// spieler blau:
		figuren[i][PLAYER_BLUE].TYPE = WALL;
		figuren[i][PLAYER_BLUE].PLAYER = PLAYER_BLUE;
		figuren[i][PLAYER_BLUE].DIR = 0;
	}

	// initialize graphics and load images:
	if(init_figure_images() == -1)
	{
		// wenn image load failed: error
		printf("Image loading failed. Exiting\n");	//Exiting? xD
		return;
	}

	//Spielfeld zeichnen
	draw_playground();

	figure_counter = 0;

	while(FOREVER)
	{
		// Mausevent einlesen und auf map mappen
		mouse_event = GetMouseEvent();
		new_mouse_pos.x = mouse_event.MousePosX;
		new_mouse_pos.y = mouse_event.MousePosY;
		new_mouse_pos = pixel_to_map(new_mouse_pos);
		new_mouse_pos.y = PLAYGROUND_Y_MAX - 1;		// schon auf dem obersten feld fixiert

		if(mouse_event.ButtonState & W_BUTTON_PRESSED)
		{
			// wenn eine maustaste gedrückt wurde:
			// der spieler hat zeile {new_mouse_pos.x} wurde angeklickt. -> dort ein stein setzen

			actual_stone = &figuren[figure_counter][spieler];

			if(!is_figure(new_mouse_pos))
			{
				// wenn auf dem obersten feld nicht schon ein stein ist, den stein setzen
				// dazu wird zuerst seine position in sein struct geschrieben, dann wird er gezeichnet.
				figuren[figure_counter][spieler].Pos.x = new_mouse_pos.x;
				figuren[figure_counter][spieler].Pos.y = PLAYGROUND_Y_MAX - 1;
				map[actual_stone->Pos.x][actual_stone->Pos.y] = actual_stone;

				draw_figure(actual_stone);
				WaitMs(100);

				// den stein von dort fallen lassen
				for(i = 0; i < PLAYGROUND_Y_MAX - 1; i++)
				{
					// von oben nach unten fallen lassen, bis er entweder ganz unten ist,
					// oder dort schon eine figur steht ( -> is_figure() == 1)
					new_stone_position.x = actual_stone->Pos.x;
					new_stone_position.y = actual_stone->Pos.y - 1;

					if(is_figure(new_stone_position) == 1)
					{
						// wenn dort schon ein stein ist, aufhören.
						break;
					}
					else
					{
						// wenn nicht: figur nach unten verschieben, delay.
						move_figure(actual_stone, new_stone_position);
						WaitMs(100);
					}
				}
			}
			else
			{
				// wenn auf dem ersten Feld schon eine stein ist, darf nicht gemacht werden.
				continue;
			}

			//########################################################
			// check here, if someone in map[][] has 4 stones in a row
			//########################################################

			// spieler toggeln:
			spieler = !spieler;
			// jedes 2. mal, wen wieder spieler Rot dran ist, wird der figure counter erhöht
			if(spieler == PLAYER_RED)
			{
				figure_counter++;
			}

			// schlussendlich wird noch der mouse event buffer gelöscht, damit während dem
			// spielzug keine weiteren spielzüge im voraus getätigt werden können.
			while(GetMouseEvent().ButtonState);
		}

		// will der user das spiel beenden?
		if(IsKeyPressReady() && (GetKeyPress() == W_KEY_CLOSE_WINDOW)) //Fenster schliessen geklickt
		{
			// KeyPress Buffer löschen
			while(IsKeyPressReady())
			{
				GetKeyPress();
			}
			CloseGraphic(); //Grafikfenster schliessen
			return;
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
/*  Output     : -                                                           */
/*                                                                           */
/*  Author     : M. Bärtschi                                                 */
/*                                                                           */
/*  Email      : bartm9@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

int gfxmain(int argc, char* argv[], const char *ApplicationPath)
{
	AppPath = ApplicationPath;	// EXE-Pfad uebergeben, damit global verwendbar
	Sound_On = 1;

	enum Spielmodus MODE;
	pawn figure[ANZ_FIGURES];	// Structarray für die Figuren

	printf("\n"TITLE);
	printf("\nWelcome to Laserchess");

	printf("\n\nPress\n1 - To start normal mode\n2 - To start placing mode\n3 - Open Existing\n4 - Sound [ON/OFF]\n5 - Exit\n");

	while(FOREVER)
	{
		clear_map_array();

		do
		{
			MODE = menu();		// Bekommt einer der 3 Modes zurück
		}
		while( MODE == INVALID_INPUT);

		if(MODE == EXIT)
		{

			printf("\nBYEBYE!!!\n");

			//WaitMs (2000);	// 2 Sekunden warten bis Fenster schliesst
			return EXIT_SUCCESS;
		}

		if(MODE == EASTER_EGG)
		{
			// Vier Gewinnt wird hier ausgeführt
			easter_egg();
			continue;
		}

		create_figures(figure);
		if(init_game(figure, MODE))
		{
			spiel(figure);
		}
	}

	system("pause");
	return EXIT_SUCCESS;
}
