/*****************************************************************************/
/*  o o o o      Berner Fachhochschule                                       */
/*        :...o  Technik und Informatik                                      */
/*****************************************************************************/
/*  Module     : Spiel                                          Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Controls the game                                           */
/*                                                                           */
/*  Procedures : spiel(), create_focus(), clear_focus()                      */
/*                                                                           */
/*  Author     : M. Bärtschi                                                 */
/*                                                                           */
/*  Email      : bartm9@bfh.ch                                               */
/*                                                                           */
/*  History    : 21.03.2012  File created                                    */
/*                                                                           */
/*  File       : Spiel.c                                                     */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "Grafik.h"
#include "window.h"
#include "LaserChess.h"
#include "Logik.h"

/*****************************************************************************/
/*  Function   : create_focus                                   Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Draw a green Background on all free Fields around the       */
/*               selected figure                                             */
/*                                                                           */
/*  Input Para : location struct (X-Y-cordinate of selected figure)          */
/*                                                                           */
/*  Output     : -                                                           */
/*                                                                           */
/*  Author     : M. Bärtschi                                                 */
/*                                                                           */
/*  Email      : bartm9@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

void create_focus(location pos)
{
	int k = 0;
	// Hilfswerte für Fokus
	location focus;
	// Rotation in CCW
	location rotate[ANZ_FOCUS_FIELDS] = {
			[0].x = -1,
			[0].y = -1,
			[1].x =  0,
			[1].y = -1,
			[2].x =  1,
			[2].y = -1,
			[3].x =  1,
			[3].y =  0,
			[4].x =  1,
			[4].y =  1,
			[5].x =  0,
			[5].y =  1,
			[6].x = -1,
			[6].y =  1,
			[7].x = -1,
			[7].y =  0
	};
	// Über die Figur selbst einen Rahmen zeichnen
	draw_focus(pos);
	// Falls Figur an pos rotierbar ist (kein King oder Wall), dann den Rotations-Fokus zeichnen
	if(!(map[pos.x][pos.y]->TYPE == KING) && !(map[pos.x][pos.y]->TYPE == WALL)) draw_rot_focus(pos);
	// Für alle Acht Felder um die Figur
	for(k = 0; k < ANZ_FOCUS_FIELDS; k++)
	{
		// Fokus um Gewählte Figur drehen lassen
		focus.x = pos.x + rotate[k].x;
		focus.y = pos.y + rotate[k].y;
		if(!is_figure(focus) && is_inside_map(focus))
		{
			draw_focus(focus);
		}
	}
}


/*****************************************************************************/
/*  Function   : clear_focus                                    Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Draw a empty field to all fields who were marked            */
/*                                                                           */
/*  Input Para : location struct (X-y-cordinate of deselected figure)        */
/*                                                                           */
/*  Output     : -                                                           */
/*                                                                           */
/*  Author     : M. Bärtschi                                                 */
/*                                                                           */
/*  Email      : bartm9@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

void clear_focus(location pos)
{
	int k = 0;
	// Hilfswerte für Fokus
	location focus;
	location rotate[ANZ_FOCUS_FIELDS] = {
			[0].x = -1,
			[0].y = -1,
			[1].x =  0,
			[1].y = -1,
			[2].x =  1,
			[2].y = -1,
			[3].x =  1,
			[3].y =  0,
			[4].x =  1,
			[4].y =  1,
			[5].x =  0,
			[5].y =  1,
			[6].x = -1,
			[6].y =  1,
			[7].x = -1,
			[7].y =  0
	};
	draw_figure(map[pos.x][pos.y]);
	for(k = 0; k < ANZ_FOCUS_FIELDS; k++)
	{
		// Fokus um Gewählte Figur drehen lassen
		focus.x = pos.x + rotate[k].x;
		focus.y = pos.y + rotate[k].y;
		if(!is_figure(focus) && is_inside_map(focus))
		{
			draw_empty_field(focus);
		}
	}
}


/*****************************************************************************/
/*  Function   : spiel                                          Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Handles the game, treats the mouse inputs, execute laser()  */
/*               Displays winner, Close Graphic                              */
/*                                                                           */
/*  Input Para : Figure Array (used for cannon position)                     */
/*                                                                           */
/*  Output     : -                                                           */
/*                                                                           */
/*  Author     : M. Bärtschi                                                 */
/*                                                                           */
/*  Email      : bartm9@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

void spiel(pawn *figure)

{
	enum Affiliation PLAYER = PLAYER_RED;
	enum Gamecontrol FIGURE_DEST = NONE;
	enum Game {SELECT_FIGURE, CHOOSE_MOVE} SPIELZUG;
	SPIELZUG = SELECT_FIGURE;
	int destroyed_figure = 0;
	int key_press = 0;
	MouseInfoType mouse_event;
	location new_mouse_pos;
	location old_mouse_pos;

	do
	{
		switch (SPIELZUG)
		{
		case SELECT_FIGURE:
			// Neuer Mouseklick einlesen
			new_mouse_pos = mouseclick_to_map();
			// Innerhalb der Map gecklickt, es ist eine Figur der momentanen Farbean der Position
			if(is_inside_map(new_mouse_pos) && is_figure(new_mouse_pos) &&
			  (map[new_mouse_pos.x][new_mouse_pos.y]->PLAYER == PLAYER))
			{
				create_focus(new_mouse_pos);	// Fokus zeichnen
				old_mouse_pos = new_mouse_pos;	// Position der gewählten Figur zwischenspeichern
				SPIELZUG = CHOOSE_MOVE;
			}
			break;
		case CHOOSE_MOVE:
			// Mausevent einlesen und auf map mappen
			mouse_event = GetMouseEvent();
			new_mouse_pos.x = mouse_event.MousePosX;
			new_mouse_pos.y = mouse_event.MousePosY;
			new_mouse_pos = pixel_to_map(new_mouse_pos);

			if(mouse_event.ButtonState & W_BUTTON_PRESSED)
			{
				if(is_inside_map(new_mouse_pos))
				{
					// Selbe Figur geklickt --> Figur abwählen
					if((new_mouse_pos.x == old_mouse_pos.x) && (new_mouse_pos.y == old_mouse_pos.y))
					{
						clear_focus(new_mouse_pos);
						SPIELZUG = SELECT_FIGURE;
					}

						// Andere Figur angeklickt --> Fokus wechseln
					else if(is_figure(new_mouse_pos) && (map[new_mouse_pos.x][new_mouse_pos.y]->PLAYER == PLAYER))
					{
						clear_focus(old_mouse_pos);
						create_focus(new_mouse_pos);
						old_mouse_pos = new_mouse_pos;		// Position der angeklickten Figur zwischenspeichern
					}

						// Wenn an Figur anliegendes Feld geklickt --> Figur verschieben
					else if((map[new_mouse_pos.x][new_mouse_pos.y] == NULL) &&
						  ((ABS(new_mouse_pos.x - old_mouse_pos.x)) <  2)  &&
						  ((ABS(new_mouse_pos.y - old_mouse_pos.y)) <  2))
					{
						clear_focus(old_mouse_pos);
						move_figure(map[old_mouse_pos.x][old_mouse_pos.y], new_mouse_pos);

						// Abschuss sound abspielen
						play_sound(Laser);

						destroyed_figure = laser(figure[PLAYER*(ANZ_FIGURES/2) + 1].Pos, figure[PLAYER*(ANZ_FIGURES/2) + 1].DIR);
						FIGURE_DEST = destroyed_figure + 3;
						SPIELZUG = SELECT_FIGURE;
						PLAYER = !PLAYER;

					}


				}
			}


				// Kein Button geklickt, aber Mausrad gedreht, Figure drehen (König und Mauer können nicht gedreht werden)
			else if((mouse_event.ButtonState & W_MOUSE_WHEEL_CHANGE) &&
				   !(map[old_mouse_pos.x][old_mouse_pos.y]->TYPE == KING) &&
				   !(map[old_mouse_pos.x][old_mouse_pos.y]->TYPE == WALL))
				{
					if(mouse_event.MouseWheelDelta > 0)
					{
						ROTATE_LEFT(map[old_mouse_pos.x][old_mouse_pos.y]->DIR);
					}
					else
					{
						ROTATE_RIGHT(map[old_mouse_pos.x][old_mouse_pos.y]->DIR);
					}
					clear_focus(old_mouse_pos);
					draw_figure(map[old_mouse_pos.x][old_mouse_pos.y]);
					SPIELZUG = SELECT_FIGURE;
					// Ruft die Funktion LASER für den jeweiligen Player auf

					// Abschuss sound abspielen
					play_sound(Laser);
					// gibt der Funktion die Pos und die Dir der Cannon mit
					destroyed_figure = laser(figure[PLAYER*(ANZ_FIGURES/2) + 1].Pos, figure[PLAYER*(ANZ_FIGURES/2) + 1].DIR);
					FIGURE_DEST = destroyed_figure + 3;
					PLAYER = !PLAYER;

				}

		}
		//key_press = GetKeyPress();
		if(IsKeyPressReady())
		{
			key_press = GetKeyPress();
			// Grafikfenster schliessen
			if((key_press == W_KEY_CLOSE_WINDOW)) //Fenster schliessen geklickt
			{
				// KeyPress Buffer löschen
				while(IsKeyPressReady())
				{
					GetKeyPress();
				}
				//Spiel beenden
				FIGURE_DEST = EXIT;
				destroy_images(); //Geladene Images aus Speicher loeschen
				CloseGraphic(); //Grafikfenster schliessen
				return;
			}

			// Spielstand speichern
			if(key_press == 's' || key_press == 'S')
			{
				char file[20];
				FILE  *fp;
				int i = 0;
				printf("Enter Filename: ");
				scanf("%s", file);
				while(getchar() != '\n'); // Eingabebuffer löschen

				if(map_extension_handler(file) == ERROR) fp = NULL;

				// Aufstellung file öffnen
				char *p, *q; //path
				fp = fopen(p = path_handler(AppPath, q = path_handler(MAP_DIR"\\", file)), "w"); if(p!=NULL)free(p);if(q!=NULL)free(q);
				if(!(fp == NULL))
				{
					//Kontrollbuchstaben auf erste Zeile schreiben
					fprintf(fp, "L\n");

					for(i = 0; i < ANZ_FIGURES; i++)	// Solange einlesen, bis alle Figuren Werte haben
					{
						fprintf(fp, "%u\n", (figure[i].PLAYER));
						fprintf(fp, "%u\n", (figure[i].TYPE));
						fprintf(fp, "%u\n", (figure[i].DIR));
						fprintf(fp, "%d\n", (figure[i].Pos.x));
						fprintf(fp, "%d\n", (figure[i].Pos.y));
					}
					fclose(fp);	// File schliessen
					printf("Saved\n");
				}
			}
		}
	}

	while(FIGURE_DEST > 2);

	// Gewinner anzeigen
	draw_winner_text(&figure[(-destroyed_figure - 1)*(ANZ_FIGURES/2)]);
	switch(-destroyed_figure - 1)
	{
	case PLAYER_RED:
		printf("\nPLAYER BLUE WINS!\n");
		break;
	case PLAYER_BLUE:
		printf("\nPLAYER RED WINS!\n");
		break;
	}

	WaitMs(4000);	//4-sek-delay für Victorysound
	destroy_images(); //Geladene Images aus Speicher loeschen
	CloseGraphic(); //Grafikfenster schliessen
	// KeyPress Buffer löschen
	while(IsKeyPressReady())
	{
		GetKeyPress();
	}
}
