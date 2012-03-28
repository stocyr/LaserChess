/*****************************************************************************/
/*	o o o o      Berner Fachhochschule										 */
/*		  :...o  Technik und Informatik										 */
/*****************************************************************************/
/*  Module     : Spiel                                          Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Steuert den Spielverlauf                                    */
/*                                                                           */
/*  Procedures : spiel()                                                     */
/*                                                                           */
/*  Author     : M. Bärtschi 												 */
/* 																			 */
/*  Email	   : bartm9@bfh.ch  						                     */
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
/* 				 selected figure.                                            */
/*                                                                           */
/*  Input Para : location struct (X-y-cordinate of selected figure)          */
/*                                                                           */
/*  Output     :                                                             */
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
/*  End Function: create_focus                                               */
/*****************************************************************************/


/*****************************************************************************/
/*  Function   : clear_focus                                    Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Draw a empty field to all fields who were marked            */
/*                                                                           */
/*  Input Para : location struct (X-y-cordinate of deselected figure)        */
/*                                                                           */
/*  Output     :                                                             */
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
/*  End Function: clear-focus                                                */
/*****************************************************************************/

/*****************************************************************************/
/*  Function   : spiel                                          Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Handles the game, treats the mouse inputs                   */
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
void spiel(void)
{
	enum Affiliation PLAYER = PLAYER_RED;
	enum Game {SELECT_FIGURE, CHOOSE_MOVE} SPIELZUG;
	SPIELZUG = SELECT_FIGURE;


	MouseInfoType mouse_event;
	location new_mouse_pos;
	location old_mouse_pos;



	do
	{
		switch (SPIELZUG)
		{
		case SELECT_FIGURE:
			new_mouse_pos = mouseclick_to_map();
			if(is_inside_map(new_mouse_pos) && is_figure(new_mouse_pos) &&
			  (map[new_mouse_pos.x][new_mouse_pos.y]->PLAYER == PLAYER))
			{
				create_focus(new_mouse_pos);
				old_mouse_pos = new_mouse_pos;
				SPIELZUG = CHOOSE_MOVE;
			}
			break;
		case CHOOSE_MOVE:
			// Mausevent einlesen und auf map mappen
			mouse_event = GetMouseEvent();
			new_mouse_pos.x = mouse_event.MousePosX;
			new_mouse_pos.y = mouse_event.MousePosY;
			new_mouse_pos = pixel_to_map(new_mouse_pos);

			switch(mouse_event.ButtonState)
			{
			case W_BUTTON_NO_EVENT:
				break;
			case W_BUTTON_PRESSED:
				if(is_inside_map(new_mouse_pos))
				{
					// Selbe Figur geklickt --> Figur abwählen
					if((new_mouse_pos.x == old_mouse_pos.x) && (new_mouse_pos.y == old_mouse_pos.y))
					{
						clear_focus(new_mouse_pos);
						SPIELZUG = SELECT_FIGURE;
					}
					else
					{
						// Andere Figur angeklickt --> Fokus wechseln
						if(is_figure(new_mouse_pos) && (map[new_mouse_pos.x][new_mouse_pos.y]->PLAYER == PLAYER))
						{
							clear_focus(old_mouse_pos);
							create_focus(new_mouse_pos);
						}
						else
						{
							// Wenn an Figur anliegendes Feld geklickt --> Figur verschieben
							if((map[new_mouse_pos.x][new_mouse_pos.y] == NULL) &&
							  ((ABS(new_mouse_pos.x - old_mouse_pos.x)) <  2)  &&
							  ((ABS(new_mouse_pos.y - old_mouse_pos.y)) <  2))
							{
								move_figure(map[old_mouse_pos.x][old_mouse_pos.y], new_mouse_pos);
								clear_focus(new_mouse_pos);
								SPIELZUG = SELECT_FIGURE;
								PLAYER = !PLAYER;

							}
						}
					}
				}
				break;
			case W_MOUSE_WHEEL_CHANGE:
				if(mouse_event.MouseWheelDelta > 0)
				{
					map[old_mouse_pos.x][old_mouse_pos.y]->DIR = ROTATE_LEFT(map[old_mouse_pos.x][old_mouse_pos.y]->DIR);
				}
				else
				{
					map[old_mouse_pos.x][old_mouse_pos.y]->DIR = ROTATE_RIGHT(map[old_mouse_pos.x][old_mouse_pos.y]->DIR);

				}
				clear_focus(new_mouse_pos);
				draw_figure(&(map[old_mouse_pos.x][old_mouse_pos.y]));
				SPIELZUG = SELECT_FIGURE;
				PLAYER = !PLAYER;

				break;

			}
		}
	}
	while(1/*laser() >= 0*/);
}
/*****************************************************************************/
/*  End Function: spiel                                                      */
/*****************************************************************************/
