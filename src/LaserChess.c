/*****************************************************************************/
/*  o o o o      Berner Fachhochschule                                       */
/*        :...o  Technik und Informatik                                      */
/*****************************************************************************/
/*  Module     : LaserChess/gfxmain                             Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : main()                                                      */
/*                                                                           */
/*  Procedures : create_figures(), menu(), set_figure_positons(),            */
/*               init game(), clear_map_array(), argument_handler, gfxmain() */
/*                                                                           */
/*  Author     : M. Bärtschi                                                 */
/*                                                                           */
/*  Email      : bartm9@bfh.ch                                               */
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
#include <ctype.h>
#include <string.h>
#include <time.h>

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
	char a = 0; // Auswahlvariable, wird mit 0 initialisiert, dass wenn scanf nichts in a schreibt, der default zweig ausgeführt wird
	char string[80];

	printf("\nEnter command: ");

	// jetzt einen String einlesen, der optional auch aus "%d %s" bestehen kann
	gets(string);
	if(isdigit(string[0]))		// Estes Zeichen eine Zahl?
	{
		a = string[0] - '0';	// String in Zahlenwert umrechnen
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
	case 4:		// Zum ein und ausschalten des Sounds
		if(STRINGS_EQUAL(string, "\x034\x067\x065\x077\x069\x06E\x06E\x074"))
		{
			MODE = EASTER_EGG1;
			return MODE;
		}
		else
		{
			Sound_On = !Sound_On;
			if(Sound_On)
			{
				printf("Sound ON\n");
				//Intro-Sound abspielen
				play_sound(Intro);
			}
			else
			{
				printf("Sound OFF\n");
				//Intro-Sound beenden
				StopContinuousSound();
			}
			MODE = INVALID_INPUT;
			return MODE;
		}
	case 5:
		if(STRINGS_EQUAL(string, "\x035\x06e\x061\x06B\x065"))
		{
			MODE = EASTER_EGG2;
			return MODE;
		}
		else if(STRINGS_EQUAL(string, "\x035\x067\x065\x077\x069\x06E\x06E\x074"))
		{
			MODE = EASTER_EGG3;
			return MODE;
		}
		else
		{
			MODE = EXIT;
			return MODE;
		}
	default:	// Wenn andere/ungültige Eingabe, -1 zurückgeben
		MODE = INVALID_INPUT;
		printf("Ungueltige Eingabe\n");
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

	printf("Next Figure: %s", "King");

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
					draw_rot_focus(mouse_pos);                  // Rotationsfokus drüber, damit Rotationsmodus ersichtlich
					map[mouse_pos.x][mouse_pos.y] = &figure[RED_FIG(i)];	// Figur auf Map setzen
				}
				else
				{
					figure[BLUE_FIG(i)].Pos.x = mouse_pos.x;
					figure[BLUE_FIG(i)].Pos.y = mouse_pos.y;
					draw_figure(&figure[BLUE_FIG(i)]);
					draw_rot_focus(mouse_pos);
					map[mouse_pos.x][mouse_pos.y] = &figure[BLUE_FIG(i)];
				}

				if(i+1 < ANZ_FIGURES)
				{
					if(figure[(i+1)/2].TYPE == KING)     printf("\r                     \rNext Figure: King");
					if(figure[(i+1)/2].TYPE == MIRROR)   printf("\r                     \rNext Figure: Mirror");
					if(figure[(i+1)/2].TYPE == SPLITTER) printf("\r                     \rNext Figure: Splitter");
					if(figure[(i+1)/2].TYPE == WALL)     printf("\r                     \rNext Figure: Wall");
					if(figure[(i+1)/2].TYPE == CANNON)   printf("\r                     \rNext Figure: Cannon");
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
					draw_figure(map[figure_pos.x][figure_pos.y]); // Figur nochmals zeichnen, da Rotationsfokus noch darüber gezeichnet ist
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
					draw_rot_focus(figure_pos);
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
			printf("\r                     \r"); //Ganze Zeile wieder loeschen
			destroy_images(); //Geladene Images aus Speicher loeschen
			CloseGraphic(); //Grafikfenster schliessen
			return -1;
		}
	}
	printf("\r                     \r"); //Ganze Zeile wieder loeschen
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
	if(init_images() == ERROR)
	{
		// wenn image load failed: error
		printf("Image loading failed\n");
		return 0;
	}



	if(MODE == SETMODE)
	{
		draw_playground();		//Spielfeld zeichnen
		// Figuren manuell setzen
		if(set_figure_positions(figure) == -1)
		{
			return 0;	// Wenn Figurensetzetn abgebrochen wurde
		}
	}
	else
	{
		// Figuren nach vordefinierter Aufstellung setzen
		if((MODE == OPEN) || MODE == STARTOPEN)
		{
			FILE  *fp;
			//File durch eingabe anfordern
			if(MODE == OPEN)
			{
				char file[100];
				printf("Enter Filename: ");
				scanf("%s", file);
				while(getchar() != '\n'); // Eingabebuffer löschen

				//Korrekte Endung
				if(map_extension_handler(file) == ERROR) return 0;

				// Aufstellung file öffnen
				char *p, *q; //path
				fp = fopen(p = path_handler(AppPath, q = path_handler(MAP_DIR"\\", file)), "r"); if(p!=NULL)free(p);if(q!=NULL)free(q);
			}
			//File wurde direkt mit LaserChess.exe geoeffnet
			else if(MODE == STARTOPEN)
			{
				fp = fopen(MapPath, "r");
			}
			if(!(fp == NULL))
			{
				//Erstes Zeichen/Zeile lesen, ob Kontrollzeichen
				char MapControl;
				fscanf(fp, "%c", &MapControl);

				if(MapControl == 'L') //Evtl erweitern zu LASERCHESSMAP
				{
					StopContinuousSound();

					if(MODE == STARTOPEN) printf("\n"); printf("Successful"); if(MODE == OPEN) printf("\n");
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
					printf("\nNot a mapfile");
					return 0;
				}
			}
			else
			{
				// Meldung wenn File nicht geöffnet werden konnte
				printf("Error: Cannot open file\n");
				return 0;	// Fehlerwert zurückgeben
			}

		}
		draw_playground();		//Spielfeld zeichnen
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
/*  Function   : easter_egg1                                    Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : ??                                                          */
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

void easter_egg1(void)
{
	MouseInfoType mouse_event;
	location new_mouse_pos, new_stone_position;
	int i, row_counter, check_loop;
	int figure_counter;
	enum Affiliation spieler = PLAYER_RED;
	pawn *actual_stone;

	// alle spielsteine generieren
	pawn figuren[PLAYGROUND_Y_MAX*PLAYGROUND_X_MAX / 2][2];

	// koeffizienten für die win_check schlaufe:
	location win_check_koeffizienten[4][2] = { {{-3,0}, {+1,0}}, {{0,-3}, {0,+1}}, {{-3,-3}, {+1,+1}}, {{-3,+3}, {+1,-1}} };

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
	if(init_images() == ERROR)
	{
		// wenn image load failed: error
		printf("Image loading failed\n");
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

			// sound abspielen
			play_sound(Reflection);

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
				// wenn unten angekommen: sound abspielen
				play_sound(Pling);
			}
			else
			{
				// wenn auf dem ersten Feld schon ein stein ist, darf nichts gemacht werden.
				continue;
			}

			//########################################################
			// check here, if someone in map[][] has 4 stones in a row

			// dafür wird immer gleich beim stein überprüft, ob dieser eine 4-er reihe ergibt.
			// der aktuell gesetzte Stein ist: actual_stone

			for(check_loop = 0; check_loop < 4; check_loop++)
			{
				row_counter = 0;
				for(i = 0; i < 7; i++)
				{
					location check_pos;
					pawn *check_stone;
					check_pos.x = actual_stone->Pos.x + win_check_koeffizienten[check_loop][0].x + win_check_koeffizienten[check_loop][1].x * i;
					check_pos.y = actual_stone->Pos.y + win_check_koeffizienten[check_loop][0].y + win_check_koeffizienten[check_loop][1].y * i;

					if(!is_inside_map(check_pos))
					{
						// wenn gar nicht auf der map:
						continue;
					}
					else
					{
						// wenn doch: beide zähler erhöhen
						check_stone = map[check_pos.x][check_pos.y];
						if(is_figure(check_pos) && check_stone->PLAYER == actual_stone->PLAYER)
						{
							// wenn dort ein stein derselben Farbe ist:
							if(++row_counter == 4)
							{
								// wenn schon 4 in einer reihe:
								// zuerst markieren:
								int j;

								// ich nehme einfach die gleiche routine wie fürs prüfen und laufe sie vom 4. Stein an rückwärts ab
								for(j = i; j >= (i-3); j--)
								{
									location focus_pos;
									focus_pos.x = actual_stone->Pos.x + win_check_koeffizienten[check_loop][0].x + win_check_koeffizienten[check_loop][1].x * j;
									focus_pos.y = actual_stone->Pos.y + win_check_koeffizienten[check_loop][0].y + win_check_koeffizienten[check_loop][1].y * j;
									draw_focus(focus_pos);
								}

								// Victorysound abspielen
								play_sound(Victory);
								WaitMs(4000);

								// KeyPress Buffer löschen
								while(IsKeyPressReady())
								{
									GetKeyPress();
								}
								destroy_images(); //Geladene Images aus Speicher loeschen
								CloseGraphic(); //Grafikfenster schliessen
								return;
							}
						}
						else
						{
							// wenn entweder fremder stein oder gar keiner:
							row_counter = 0;
						}
					}
				}
			}

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
			destroy_images(); //Geladene Images aus Speicher loeschen
			CloseGraphic(); //Grafikfenster schliessen
			return;
		}
	}
}


/*****************************************************************************/
/*  Function   : easter_egg2                                    Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : ??                                                          */
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

void easter_egg2(void)
{
	const int max_length = PLAYGROUND_Y_MAX*PLAYGROUND_X_MAX;
	location new_food_pos, temp;
	location snake[max_length];
	int head = 0, tail = 0;
	int queue_length = 1;
	pawn food, old_snake;
	enum Direction dir, old_dir;
	enum Angle snake_angle;

	srand(time(NULL)); // benutze zeit in sekunden seit 01.01.1970 als seed für rand()

	// snake initialisieren
	snake[head].x = PLAYGROUND_X_MAX / 2;
	snake[head].y = 0;
	dir = UP;
	snake_angle = 0;

	// food initialisieren
	food.TYPE = WALL;
	food.PLAYER = PLAYER_BLUE; // egal
	food.DIR = 0;

	// old snake wird genutzt um die überstrichenen felder in der map zu kennzeichnen
	old_snake.TYPE = CANNON;

	// initialize graphics and load images:
	if(init_images() == ERROR)
	{
		// wenn image load failed: error
		printf("Image loading failed\n");
		return;
	}

	//Spielfeld zeichnen
	draw_playground();

	// Food generieren: dazu position in sein struct geschrieben, dann wird er gezeichnet.
	do
	{
		food.Pos.x = PLAYGROUND_X_MAX * rand() / RAND_MAX;
		food.Pos.y = PLAYGROUND_Y_MAX * rand() / RAND_MAX;
	}
	while(food.Pos.x == snake[head].x && food.Pos.y == snake[head].y); // solange, bis food auf leerem feld

	map[food.Pos.x][food.Pos.y] = &food;
	draw_figure(&food);

	while(FOREVER)
	{
		// Linie zeichnen -> entweder abgewinkelt oder gerade
		if(snake_angle != 0)
		{
			// wenn nicht nur geradeaus:
			draw_angled_laser(snake[head], old_dir, snake_angle);
			// winkeländerung wieder zurücksetzen
			snake_angle = 0;
		}
		else
		{
			// gerade linie zeichnen
			draw_laser(snake[head], dir);
		}

		// taste einlesen
		if(IsKeyPressReady())
		{
			// Taste einlesen
			switch(GetKeyPress())
			{
			case W_KEY_CURSOR_LEFT:
				// wenn nach links: nach links drehen
				snake_angle = CCW;
				break;

			case W_KEY_CURSOR_RIGHT:
				// wenn nach rechts: nach rechts drehen
				snake_angle = CW;
				break;

			case W_KEY_CLOSE_WINDOW:
				// wenn der user beenden will
				// KeyPress Buffer löschen
				while(IsKeyPressReady())
				{
					GetKeyPress();
				}
				destroy_images(); //Geladene Images aus Speicher loeschen
				CloseGraphic(); //Grafikfenster schliessen
				return;
			}
		}

		// nächstes feld ausfindig machen
		temp = snake[head];

		head = (head+1) % max_length;
		tail = (head + (max_length - queue_length)) % max_length;

		snake[head] = temp;

	    switch(dir)
	    {
	        case RIGHT:
	        	snake[head].x++;
	            break;

	        case UP:
	        	snake[head].y++;
	            break;

	        case LEFT:
	        	snake[head].x--;
	            break;

	        case DOWN:
	        	snake[head].y--;
	            break;
	    }

		// Zuerst fragen, ob das nächste Feld überhaupt noch im Spielfeld ist
		if(!is_inside_map(snake[head]))
		{
			// wenn nicht mehr im spielfeld, in eine wand gefahren.
			// ignore sound abspielen
			play_sound(Ignore);
			//############ GAME OVER #################
			WaitMs(2000);
			destroy_images(); //Geladene Images aus Speicher loeschen
			CloseGraphic(); //Grafikfenster schliessen
			return;
		}
		else
		{
			pawn *new_field = map[snake[head].x][snake[head].y];

			if(is_figure(snake[head]))
			{
				// wenn eine Figur da ist:
				if(new_field->TYPE == CANNON)
				{
					// wenn in sich selber reingefahren:
					// ignore sound abspielen
					play_sound(Ignore);
					//############ GAME OVER #################
					WaitMs(2000);
					destroy_images(); //Geladene Images aus Speicher loeschen
					CloseGraphic(); //Grafikfenster schliessen
					return;
				}
				else if(new_field->TYPE == WALL)
				{
					// wenn was gefressen wurde, schwanz verlängern und food verschieben
					queue_length++;

					// sound abspielen
					play_sound(Pling);

					// food an neue position verschieben: achtung: nicht auf die snake drauf!
					do
					{
						new_food_pos.x = PLAYGROUND_X_MAX * rand() / RAND_MAX;
						new_food_pos.y = PLAYGROUND_Y_MAX * rand() / RAND_MAX;
					}
					while(is_figure(new_food_pos)); // solange, bis new_food_pos auf leerem feld

					move_figure(&food, new_food_pos);
				}
			}
		}

		// wenn vorhin eine rechts- oder linkstaste eingelesen wurde: jetzt <dir> drehen.
		old_dir = dir;
		switch(snake_angle)
		{
		case CW:
			ROTATE_RIGHT(dir);
			break;

		case CCW:
			ROTATE_LEFT(dir);
			break;
		}

		// das gezeichnete Feld mit old_snake markieren:
		map[snake[head].x][snake[head].y] = &old_snake;

		// laser-schwanz löschen:
		draw_empty_field(snake[tail]);
		map[snake[tail].x][snake[tail].y] = NULL;
	}
}


/*****************************************************************************/
/*  Function   : easter_egg3                                    Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : ??                                                          */
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

void easter_egg3(void)
{
	MouseInfoType mouse_event;
	location new_mouse_pos;
	int i, row_counter, check_loop;
	int figure_counter;
	enum Affiliation spieler = PLAYER_RED;
	pawn *actual_stone;

	// alle spielsteine generieren
	pawn figuren[PLAYGROUND_Y_MAX*PLAYGROUND_X_MAX / 2][2];

	// koeffizienten für die win_check schlaufe:
	location win_check_koeffizienten[4][2] = { {{-4,0}, {+1,0}}, {{0,-4}, {0,+1}}, {{-4,-4}, {+1,+1}}, {{-4,+4}, {+1,-1}} };

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
	if(init_images() == ERROR)
	{
		// wenn image load failed: error
		printf("Image loading failed\n");
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
				figuren[figure_counter][spieler].Pos.y = new_mouse_pos.y;
				map[actual_stone->Pos.x][actual_stone->Pos.y] = actual_stone;

				draw_figure(actual_stone);

				// sound abspielen
				play_sound(Pling);
			}
			else
			{
				// wenn auf diesem Feld schon ein stein ist, darf nichts gemacht werden.
				play_sound(Ignore);
				continue;
			}

			//########################################################
			// check here, if someone in map[][] has 5 stones in a row

			// dafür wird immer gleich beim stein überprüft, ob dieser eine 5-er reihe ergibt.
			// der aktuell gesetzte Stein ist: actual_stone

			for(check_loop = 0; check_loop < 4; check_loop++)
			{
				row_counter = 0;
				for(i = 0; i < 9; i++)
				{
					location check_pos;
					pawn *check_stone;
					check_pos.x = actual_stone->Pos.x + win_check_koeffizienten[check_loop][0].x + win_check_koeffizienten[check_loop][1].x * i;
					check_pos.y = actual_stone->Pos.y + win_check_koeffizienten[check_loop][0].y + win_check_koeffizienten[check_loop][1].y * i;

					if(!is_inside_map(check_pos))
					{
						// wenn gar nicht auf der map:
						continue;
					}
					else
					{
						// wenn doch: beide zähler erhöhen
						check_stone = map[check_pos.x][check_pos.y];
						if(is_figure(check_pos) && check_stone->PLAYER == actual_stone->PLAYER)
						{
							// wenn dort ein stein derselben Farbe ist:
							if(++row_counter == 5)
							{
								// wenn schon 5 in einer reihe:
								// zuerst markieren:
								int j;

								// ich nehme einfach die gleiche routine wie fürs prüfen und laufe sie vom 5. Stein an rückwärts ab
								for(j = i; j >= (i-4); j--)
								{
									location focus_pos;
									focus_pos.x = actual_stone->Pos.x + win_check_koeffizienten[check_loop][0].x + win_check_koeffizienten[check_loop][1].x * j;
									focus_pos.y = actual_stone->Pos.y + win_check_koeffizienten[check_loop][0].y + win_check_koeffizienten[check_loop][1].y * j;
									draw_focus(focus_pos);
								}

								// Victorysound abspielen
								play_sound(Victory);
								WaitMs(4000);

								// KeyPress Buffer löschen
								while(IsKeyPressReady())
								{
									GetKeyPress();
								}
								destroy_images(); //Geladene Images aus Speicher loeschen
								CloseGraphic(); //Grafikfenster schliessen
								return;
							}
						}
						else
						{
							// wenn entweder fremder stein oder gar keiner:
							row_counter = 0;
						}
					}
				}
			}

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
			destroy_images(); //Geladene Images aus Speicher loeschen
			CloseGraphic(); //Grafikfenster schliessen
			return;
		}
	}
}


/*****************************************************************************/
/*  Function   : argument_handler                               Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Reads the start-arguments. If the EXE was started by        */
/*               opening a mapfile, we try to load it and start a game.      */
/*               If there are start-variables defined we set them.           */
/*               Unknown arguments are printed to screen.                    */
/*                                                                           */
/*  Input Para : int argn, number of arguments; char* args[], arguments;     */
/*               pawn *figure, figure-array needed to start a game           */
/*                                                                           */
/*  Output     : -                                                           */
/*                                                                           */
/*  Author     : N. Kaeser                                                   */
/*                                                                           */
/*  Email      : kasen1@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

void argument_handler(int argn, char* args[], pawn *figure)
{
	//Standardwerte der Variablen
	//Beispiel: FIELD_SIZE = 100;
	//Ende der Startwerte

	//Argument 0 = AppPath (Standardmaessig immer so)
	//Argument 1 = Dateipfad (Falls eine Datei mit LaserChess geoffnet wird)

	//Falls es nicht mehr als ein Argument (AppPath) gibt, abbrechen
	if(!(argn>1)) return;

	//Ist Argument 1 ein Pfad? (Datei wurde geoeffnet mit LaserChess.exe)
	//Also: Ist 2. Buchstabe ':', wie z.B. in "C:Map1.txt"?
	if(args[1][1] == ':')
	{
		printf("\nTrying to open file...");
		MapPath = args[1];

		create_figures(figure);
		if(init_game(figure, STARTOPEN))
		{
			spiel(figure); //Spiel starten/ausführen
		}
	}
	//Wenn im Eclipse gestartet (Argument 1 ist %*)
	else if(STRINGS_EQUAL(args[1], "%*"))
	{
		printf("\nStarted in Eclipse");
	}
	//Sonstige Argumente
	else
	{
		//Buffer fuer Werte
		//unsigned int buffer = 0;

		int i;
		for(i = 1; i<argn; i++)
		{
			/*Vorlage fuer Variablen (Bsp mit Field_size)
			//Bekannte Variable?
			if(STRINGS_EQUAL(args[i], "-Field_size"))
			{
				//Wert (naechstes Argument) vorhanden und keine variable?
				if((i+1<argn) && (args[i+1][0] != '-'))
				{
					//Falls Argument eine Zahl ist, wird diese hier in buffer kopiert
					//(Werte groesser als (2^32 - 1) geben einen Ueberlauf, 2^32 gibt also wieder 0)
					sscanf(args[i+1], "%u", &buffer);

					//Pruefen ob Argument eine gueltige Zahl war
					//(wenn nicht, dann hat buffer noch startwert 0)
					if(buffer != 0)
					{
						//Feldgroesse maximal 200 und minimal 20
						if(buffer > 200) buffer = 200;
						else if(buffer < 20) buffer = 20;

						FIELD_SIZE = buffer;
						printf("\nField_size set to %u", buffer);
					}
					else printf("\nInvalid parameter for %s: \"%s\"", args[i], args[i+1]);

					//Naechstes Argument ueberspringen, da wir das soeben als Wert gelesen haben (oder versucht).
					i++;
				}
				else printf("\nParameter for %s not found", args[i]);
			}
			Ende der Vorlage fuer Variablen

			else*/ printf("\nUnknown argument: \"%s\"", args[i]);
		}
	}
	printf("\n\n");
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
	Hit_mirror.x = -1;			// Globale Variable für getroffenen Spiegel initialisieren
	Hit_mirror.y = -1;
	enum Spielmodus MODE;
	pawn figure[ANZ_FIGURES];	// Structarray für die Figuren

	printf(""TITLE);
	printf("Welcome to Laserchess!\n\n");

	argument_handler(argc, argv, figure);

	printf("\nPress\n1 - To start normal mode\n2 - To start placing mode\n3 - Open Existing\n4 - Sound [ON/OFF]\n5 - Exit\n");

	while(FOREVER)
	{
		clear_map_array();

		//Intro-Sound abspielen
		play_sound(Intro);

		do
		{
			MODE = menu();		// Bekommt einen Mode zurück
		}
		while( MODE == INVALID_INPUT);

		//Intro-Sound beenden
		if(MODE != OPEN) StopContinuousSound();

		if(MODE == EXIT)
		{
			return EXIT_SUCCESS;
		}
		else if(MODE == EASTER_EGG1)
		{
			// Easter egg 1 wird ausgeführt
			easter_egg1();
			continue;
		}
		else if(MODE == EASTER_EGG2)
		{
			// Eater egg 2 wird ausgeführt
			easter_egg2();
			continue;
		}
		else if(MODE == EASTER_EGG3)
		{
			// Eater egg 3 wird ausgeführt
			easter_egg3();
			continue;
		}

		create_figures(figure);		// Figuren hier erstellen und initialisieren
		if(init_game(figure, MODE))
		{
			spiel(figure);		//Spiel starten/ausführen
		}
	}

	return EXIT_SUCCESS;
}
