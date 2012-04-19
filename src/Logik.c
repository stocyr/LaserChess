/*****************************************************************************/
/*	o o o o      Berner Fachhochschule										 */
/*		  :...o  Technik und Informatik										 */
/*****************************************************************************/
/*  Module     : LaserChess/Logik                               Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Contains several logic and helper functions                 */
/*                                                                           */
/*  Procedures : laser(), is_inside_map(), is_figure, move_figure, 			 */
/* 				 destroy_figure()										     */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/* 																			 */
/*  Email	   : stolc2@bfh.ch  						                     */
/*                                                                           */
/*  History    : 17.03.2012  File created                                    */
/*                                                                           */
/*  File       : Logik.c                                                     */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/

#include "Grafik.h"
#include "Logik.h"
#include "LaserChess.h"
#include "window.h"

/*****************************************************************************/
/*  Function   : laser                                          Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Draws the laser from the cannon across the whole playground */
/* 				 and calls all the other functions handling figure behavior  */
/*                                                                           */
/*  Input Para : receives the field from which the laser shoot is done. this */
/*               field is not painted with laser anymore, but the field NEXT */
/*               to it, whose direction from the field is specified with dir */
/*                                                                           */
/*  Output     : if a wall or a cannon was hit, or the laser passes out of   */
/*               the playground, returns 0.                                  */
/*               If a king was hit: -1 for player_red, -2 for player_blue.   */
/*               If a mirror was hit: +1 for player_red, +2 for player_blue  */
/*               In case of a splitter being hit: then two laser paths are   */
/*               generated and the return value is the one with the higher   */
/*               priority (descending order): king, mirror, wall / cannon.   */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/*                                                                           */
/*  Email      : stolc2@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

int laser(location pos, enum Direction dir)	//enum Direction dir
{
	// Zuerst einmal wird das nächste Feld gesucht
    location next_pos = pos;

    // Bei jedem Feld nachfragen, ob der User das Fenster schliessen wollte
	if(IsKeyPressReady() && (GetKeyPress() == W_KEY_CLOSE_WINDOW)) //Fenster schliessen geklickt
	{
		// KeyPress Buffer löschen
		while(IsKeyPressReady())
		{
			GetKeyPress();
		}
		CloseGraphic(); //Grafikfenster schliessen
		return -3;	// -3 zurückgeben, dass Gamecontrol enum auf Exit gesetzt wird
	}

	// nächstes Feld berechnen
    switch(dir)
    {
        case RIGHT:
            next_pos.x++;
            break;

        case UP:
            next_pos.y++;
            break;

        case LEFT:
            next_pos.x--;
            break;

        case DOWN:
            next_pos.y--;
            break;
    }

    // Zuerst fragen, ob das nächste Feld überhaupt noch im Spielfeld ist
    if(!is_inside_map(next_pos))
    {
        // wenn nicht mehr im spielfeld, in eine wand gefahren. -> return 0
    	WaitMs(LASER_FINISHED_WAIT_TIME);
        return 0;
    }
    else
    {
    	// wenn noch im Spielfeld: nächstes Feld überprüfen
    	int return_value, return_value_splitter, reflection_angle;
        pawn *next_pawn = map[next_pos.x][next_pos.y];

        // ist auf dem nächsten Feld eine Figur?
        if(!is_figure(next_pos))
        {
            // Nein, nur ein leeres Feld

        	// Linie zeichnen
            draw_laser(next_pos, dir);
            // sich selbst ausführen
            return_value = laser(next_pos, dir);
            // nachdem der Laser irgendwo angestossen ist, linie wieder löschen
            draw_empty_field(next_pos);
            return return_value;
        }
        else
        {
            // wenn eine Figur: was für eine?
            switch(next_pawn->TYPE)
            {
                case WALL:
                    // Mauer getroffen: aufhören, wie bei is_inside_map = 0
                	WaitMs(LASER_FINISHED_WAIT_TIME);
                    return 0;

                case KING:
                    // König getroffen: Zerstörung zeichnen
                    draw_king_destroyed(next_pawn);

                	// (Player+1) negativ zurückgeben
                	// -> -1 für Player_Red, -2 für Player_Blue
                    return -(next_pawn->PLAYER+1);

                case MIRROR:
                    // Spiegel getroffen: Gibt es eine Reflektion?

                	// Auftrittswinkel auf den Spieler aus dessen Orientierung und der Laser-Richtung berechnen
                    reflection_angle = dir - next_pawn->DIR;
                    NORM(reflection_angle);

                    switch(reflection_angle)
                    {
                        case 0:
                        case 1:
                        	// Zerstörung: Zerstörung zeichnen
                            draw_mirror_destroyed(next_pawn);
                            // Spiegel aus der map löschen
                            destroy_figure(next_pawn);
                            WaitMs(LASER_FINISHED_WAIT_TIME);

                            // Spiegel positiv zurückgeben
                            return next_pawn->PLAYER+1;

                        case 2:
                            // Reflektion um 90° nach rechts (CW):
                            // Linie zeichnen, angle = -1 (CW)
                            draw_angled_laser(next_pos, dir, CW);
                            ROTATE_RIGHT(dir);

                            // sich selbst ausführen
                            return_value = laser(next_pos, dir);
                            // nachdem der Laser irgendwo angestossen ist, linie wieder löschen
                            draw_figure(next_pawn);
                            return return_value;

                        case 3:
                            // Reflektion um 90° nach links (CCW):
                            // Linie zeichnen, angle = +1 (CCW)
                            draw_angled_laser(next_pos, dir, CCW);
                            ROTATE_LEFT(dir);

                            // sich selbst ausführen
                            return_value = laser(next_pos, dir);
                            // nachdem der Laser irgendwo angestossen ist, linie wieder löschen
                            draw_figure(next_pawn);
                            return return_value;
                    }
                    break;

                case SPLITTER:
                    // Splitter getroffen: welche Reflektion? (keine zerstörung möglich)

                	// Zuerst wird der gerade pfad bearbeitet:
                	// dir bleibt gleich, einfach ein Feld weiter (wie bei einem leeren Feld).
                	// Linie zeichnen
					draw_laser(next_pos, dir);
                	// sich selbst ausführen
					return_value = laser(next_pos, dir);

					// Jetzt wird der abgewinkelte Pfad bearbeitet:
                    reflection_angle = dir - next_pawn->DIR;
                    NORM(reflection_angle);

                    // Welcher Reflektionswinkel?
                    switch(reflection_angle)
                    {
                        case 0:
                        case 2:
                            // Reflektion um 90° nach rechts (CW)
                            // Linie zeichnen
                            draw_angled_laser(next_pos, dir, CW);
                            ROTATE_RIGHT(dir);

                            // sich selbst ausführen
                            return_value_splitter = laser(next_pos, dir);
                            break;

                        case 1:
                        case 3:
                            // Reflektion um 90° nach links (CCW)
                            // Linie zeichnen, angle = +1 (CCW)
                            draw_angled_laser(next_pos, dir, CCW);
                            ROTATE_LEFT(dir);

                            // sich selbst ausführen
                            return_value_splitter = laser(next_pos, dir);
                            break;
                    }

                    // Jetzt erst wird der splitter wieder von den Laserlinien 'befreit'
                    draw_figure(next_pawn);

                    // und dannach der Wert zurückgegeben, der die höchste Priorität hat.
                    if(return_value < 0 || return_value_splitter < 0)
                    {
                    	// wenn ein könig getroffen wurde:
                    	// den king-down wert zurückgeben - der Player_Blue-King hat priorität
                    	return MIN(return_value, return_value_splitter);
                    }
                    else if(return_value > 0 || return_value_splitter > 0)
                    {
                    	// wenn ein mirror getroffen wurde:
                    	// den mirror-down wert zurückgeben - der Player_Blue-King hat priorität
                    	return MAX(return_value, return_value_splitter);
                    }
                    else
                    {
                    	// wenn von beiden Laserstrahlen nichts getroffen wurde: 0 zurückgeben.
                    	return 0;
                    }

				case CANNON:
					// Kanone getroffen: Nichts passiert.
					WaitMs(2000);
					return 0;
            }
        }
    }

    return 0;
}


/*****************************************************************************/
/*  Function   : is_inside_map                                  Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : checks if the given coordinates are inside the array        */
/*                                                                           */
/*  Input Para : given coordinates                                           */
/*                                                                           */
/*  Output     : if inside map (means, inside the range [0 - 7][0 - 5], then */
/*               it returns 1. Otherwise it returns 0.                       */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/*                                                                           */
/*  Email      : stolc2@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

int is_inside_map(location pos)
{
    // wenn innerhalb der definierten Array-grenzen:
    /*if((pos.x < PLAYGROUND_X_MAX-FIELD_LINE_WIDTH/2 && pos.x >= 0) &&
       (pos.y < PLAYGROUND_Y_MAX-FIELD_LINE_WIDTH/2 && pos.y >= 0))*/ //Geaendert von kasen1
    if((pos.x < PLAYGROUND_X_MAX && pos.x >= 0) &&
       (pos.y < PLAYGROUND_Y_MAX && pos.y >= 0))
    {
        // true zurückgeben
        return 1;
    }
    else
    {
        // false zurückgeben
        return 0;
    }

    // Python:
    // return 1 if (0 < pos.x < PLAYGROUND_X_MAX-FIELD_LINE_WIDTH) and (0 < pos.y < PLAYGROUND_Y_MAX-FIELD_LINE_WIDTH) else 0
    // # - just sayin'
    // # - Challenge accepted by kasen1, C:
    // return !((pos.x>PLAYGROUND_X_MAX-FIELD_LINE_WIDTH)||(pos.y>PLAYGROUND_Y_MAX-FIELD_LINE_WIDTH)||(pos.x<=0)||(pos.y<=0));
    // # - Like a Boss!
}


/*****************************************************************************/
/*  Function   : is_figure                                      Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : checks if the given coordinates contains a figure           */
/*                                                                           */
/*  Input Para : given coordinates                                           */
/*                                                                           */
/*  Output     : if there is a figure, returns 1, if its an empty field,     */
/*               returns 0. (a wall is treatened as a figure)                */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/*                                                                           */
/*  Email      : stolc2@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

int is_figure(location pos)
{
    // wenn map dort einen NULL pointer enthält (= keine figure-Struktur):
    if(map[pos.x][pos.y] == NULL)
    {
        // false zurückgeben
        return 0;
    }
    else
    {
        // true zurückgeben
        return 1;
    }
}


/*****************************************************************************/
/*  Function   : move_figure                                    Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : moves a figure to the given location                        */
/*                                                                           */
/*  Input Para :                                                             */
/*                                                                           */
/*  Output     : none                                                        */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/*                                                                           */
/*  Email      : stolc2@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

void move_figure(pawn *figure, location new_pos)
{
    // zuerst die alte Position auf der Map löschen (Pointer NULL setzen)
	destroy_figure(figure);

	// dann an der neuen Position den figure-Pointer hinschreiben
	map[new_pos.x][new_pos.y] = figure;

	// auf dem SPielfeld das alte Feld läschen (grafisch)
    draw_empty_field(figure->Pos);

    // die Position der figure im Struct auf die neue Position umschreiben
    figure->Pos = new_pos;

    // die neue figure an der neuen Position zeichnen
    draw_figure(figure);
}


/*****************************************************************************/
/*  Function   : destroy_figure                                 Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : destroys a figure (deletes it from the map array)           */
/*                                                                           */
/*  Input Para : figure pointer                                              */
/*                                                                           */
/*  Output     : none                                                        */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/*                                                                           */
/*  Email      : stolc2@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

void destroy_figure(pawn *figure)
{
    // lösche figur aus der map[][]
	map[figure->Pos.x][figure->Pos.y] = NULL;
}


/*****************************************************************************/
/*  Function   : mouseclick_to_map()                            Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Get Mouse-Clicks and returns the Mapcoordinate.             */
/*                                                                           */
/*  Input Para :                                                             */
/*                                                                           */
/*  Output     : Returns location struct, of the field who was hit or -1     */
/*               when the click was beyond the map or there was no click.    */
/*  Author     : M. Bärtschi                                                 */
/*                                                                           */
/*  Email      : bartm9@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

location mouseclick_to_map(void)
{
	location pos;
	MouseInfoType mouse_event, old_mouse_event;
	//Get and analyze mouse-events
	mouse_event = GetMouseEvent();
	while(!(mouse_event.ButtonState == W_BUTTON_NO_EVENT))
	{
		old_mouse_event = mouse_event;
		mouse_event = GetMouseEvent();
	}

	if(old_mouse_event.ButtonState & W_BUTTON_PRESSED)
	{
		/* Get Click-position */
		pos.x   = old_mouse_event.MousePosX;
		pos.y   = old_mouse_event.MousePosY;
	}
	else
	{
		pos.x = -1;
		pos.y = -1;
	}
	return pixel_to_map(pos);
}
