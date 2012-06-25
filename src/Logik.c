/*****************************************************************************/
/*  o o o o      Berner Fachhochschule                                       */
/*        :...o  Technik und Informatik                                      */
/*****************************************************************************/
/*  Module     : LaserChess/Logik                               Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Contains several logic and helper functions                 */
/*                                                                           */
/*  Procedures : laser(), is_inside_map(), is_figure(), move_figure(),       */
/*               destroy_figure(), mouseclick_to_map(), path_handler(),      */
/*               extension_handler(), play_sound()                           */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/*                                                                           */
/*  Email      : stolc2@bfh.ch                                               */
/*                                                                           */
/*  History    : 17.03.2012  File created                                    */
/*                                                                           */
/*  File       : Logik.c                                                     */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/

#include <string.h>
#include "Grafik.h"
#include "Logik.h"
#include "LaserChess.h"
#include "window.h"

/*****************************************************************************/
/*  Function   : laser                                          Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Draws the laser from the cannon across the whole playground */
/*               and calls all the other functions handling figure behavior  */
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
		destroy_images(); //Geladene Images aus Speicher loeschen
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
    	// ignore sound abspielen
		play_sound(Ignore);
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
            // nachdem der Laser irgendwo angestossen ist, linie wieder löschen, ausser wenn King getroffen wurde
            if(return_value >= 0)draw_empty_field(next_pos);
            return return_value;
        }
        else
        {
            // wenn eine Figur: was für eine?
            switch(next_pawn->TYPE)
            {
                case WALL:
                    // Mauer getroffen: aufhören, wie bei is_inside_map = 0
                	// ignore sound abspielen
					play_sound(Ignore);
                	WaitMs(LASER_FINISHED_WAIT_TIME);
                    return 0;

                case KING:
                	// König getroffen: Zerstörungssound
                	play_sound(Destruction);
                	//Zerstourung zeichnen
                    draw_figure_destroyed(next_pawn);

                    //Farben des gesamter Playgrounds invertieren
					draw_invert_colors(0, 0, PG_WIDTH, PG_HEIGHT);
					//Das letzte Stuendlein hat geschlagen :)
					play_sound(Bell);
					WaitMs(2100);

					//Victorysound abspielen
                	play_sound(Victory);

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
                        	//Zerstourungssound
                        	play_sound(Destruction);
                        	// Position des getroffenen Mirrors global speichern (da rekursion)
                        	Hit_mirror = next_pawn->Pos;
                        	// Zerstörung: Zerstörung zeichnen
                            draw_figure_destroyed(next_pawn);
                            // Spiegel aus der map löschen
                            destroy_figure(next_pawn);
                            WaitMs(LASER_FINISHED_WAIT_TIME);

                            // Spiegel positiv zurückgeben
                            return next_pawn->PLAYER+1;

                        case 2:
                            // Reflektion um 90° nach rechts (CW):
                        	// Reflection sound wird erst in der Grafik abgespielt
                            // Linie zeichnen, angle = -1 (CW)
                            draw_angled_laser(next_pos, dir, CW);
                            ROTATE_RIGHT(dir);

                            // sich selbst ausführen
                            return_value = laser(next_pos, dir);
                            // nachdem der Laser irgendwo angestossen ist, linie wieder löschen, ausser wenn King getroffen wurde
                            if(return_value == 0) // Wall
                            {
                            	draw_figure(next_pawn);
                            }
                            if(return_value > 0) // Mirror
                            {
                            	draw_figure(next_pawn);
                            	draw_empty_field(Hit_mirror); // Notlösung wenn getroffener Mirror beim Laser-Löschen wieder gezeichnet wird
                            }
                            return return_value;

                        case 3:
                            // Reflektion um 90° nach links (CCW):
                        	// Reflection sound wird erst in der Grafik abgespielt
                            // Linie zeichnen, angle = +1 (CCW)
                            draw_angled_laser(next_pos, dir, CCW);
                            ROTATE_LEFT(dir);

                            // sich selbst ausführen
                            return_value = laser(next_pos, dir);
                            // nachdem der Laser irgendwo angestossen ist, linie wieder löschen, ausser wenn King getroffen wurde
                            if(return_value == 0) // Wall
							{
								draw_figure(next_pawn);
							}
							if(return_value > 0) // Mirror
							{
								draw_figure(next_pawn);
								draw_empty_field(Hit_mirror); // Notlösung wenn getroffener Mirror beim Laser-Löschen wieder gezeichnet wird
							}
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

					// Reflection sound abspielen
					play_sound(Reflection);

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

                    // Jetzt erst wird der splitter wieder von den Laserlinien 'befreit', ausser wenn King getroffen wurde
                    if(return_value >= 0)draw_figure(next_pawn);

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
					// ignore sound abspielen
					play_sound(Ignore);
					WaitMs(LASER_FINISHED_WAIT_TIME);
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
/*  Input Para : figure pointer, new playground location                     */
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
/*  Output     : Returns location struct, of the field who was hit or ERROR  */
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
		pos.x = ERROR;
		pos.y = ERROR;
	}
	return pixel_to_map(pos);
}


/*****************************************************************************/
/*  Function   : path_handler                                   Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Combines the two strings path and file after checking       */
/*               if there's enough memory available.                         */
/*               Path has to be freed after use.                             */
/*                                                                           */
/*  Input Para : const char path[] - String with the path of file            */
/*               char file[]       - String with the filename                */
/*                                                                           */
/*  Output     : returns string with the complete path                       */
/*                                                                           */
/*  Author     : N. Kaeser                                                   */
/*                                                                           */
/*  Email      : kasen1@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

char *path_handler(const char path[], char file[])
{
	//Komplete Laenge des Pfades ermitteln (+1 wegen Abschlusszeichen '\0')
	int size = snprintf(NULL, 0, "%s%s", path, file) + 1;

	//Speicher mit Groesse size allozieren
	char *buffer = malloc(size);
	//Wenn nicht genuegend Speicher vorhanden, NULL zurueckgeben
	if(buffer == NULL) return NULL;

	//Kompletter Pfad in buffer speichern
	sprintf(buffer, "%s%s", path, file);

	return buffer;
}


/*****************************************************************************/
/*  Function   : map_extension_handler                          Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Reads the extension of a filename (input string). If there  */
/*               is one, checks if it's MAP_EXT (return 0 if not). If there  */
/*               is no extension, MAP_EXT is added to the end.               */
/*                                                                           */
/*  Input Para : char file[]                                                 */
/*               (Has to be long enough to add MAP_EXT at the end!)          */
/*                                                                           */
/*  Output     : -1 ERROR, 1 SUCCESS                                         */
/*                                                                           */
/*  Author     : N. Kaeser                                                   */
/*                                                                           */
/*  Email      : kasen1@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

int map_extension_handler(char file[])
{
	//Nach letztem '.' im Filename suchen
	char *pchar = strrchr(file, '.');

	//Wenn nicht vorhanden, Pointer auf NULL
	if(pchar != NULL)
	{
		if(strstr(file, MAP_EXT) != pchar)
		{
			//Wird ausgeführt, wenn MAP_EXT in file nicht gefunden wurde (NULL), also andere Endung besitzt,
			//oder nicht an gleicher Adresse wie pchar ist (also nicht die Endung ist, sondern irgendwo sonst in file enthalten)

			printf("Error: Not a \""MAP_EXT"\" file\n");
			return ERROR;	// Fehlerwert zurückgeben
		}
	}
	else //Gar keine Endung eingegeben
	{
		//Eingabe mit Mapendung erweitern
		strcat(file, MAP_EXT);
	}
	return SUCCESS;
}


/*****************************************************************************/
/*  Function   : play_sound                                     Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Plays the sound of chosen enumeration. Switches all sounds  */
/*               off, if a sound was not found.                              */
/*                                                                           */
/*  Input Para : Laser, Reflexion, Destruction, Victory, Ignore, Intro,      */
/*               Music, Bling, Bell                                          */
/*                                                                           */
/*  Output     : -                                                           */
/*                                                                           */
/*  Author     : J. Haldemann                                                */
/*                                                                           */
/*  Email      : haldj3@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

void play_sound(enum Sound snd)
{
	char *p;		//path
	FILE *datei;    //für fopen

	if(!Sound_On) return;	//Wenn Sounds off, abbrechen

	switch(snd)
	{
		case Laser:
			p=path_handler(AppPath, SOUND_DIR"\\laser.wav");

			//Testen ob Datei vorhanden mit file-open
			datei = fopen(p,"r");
			if(datei!=NULL)
			{
				//Datei ist vorhanden, schliessen und Sound abspielen
				fclose(datei);
				PlaySoundOnce(p);
			}

			if(p!=NULL)	free(p);
			break;

		case Reflection:
			p=path_handler(AppPath, SOUND_DIR"\\reflection.wav");

			//Testen ob Datei vorhanden mit file-open
			datei = fopen(p,"r");
			if(datei!=NULL)
			{
				//Datei ist vorhanden, schliessen und Sound abspielen
				fclose(datei);
				PlaySoundOnce(p);
			}

			if(p!=NULL)	free(p);
			break;

		case Destruction:
			p=path_handler(AppPath, SOUND_DIR"\\destruction.wav");

			//Testen ob Datei vorhanden mit file-open
			datei = fopen(p,"r");
			if(datei!=NULL)
			{
				//Datei ist vorhanden, schliessen und Sound abspielen
				fclose(datei);
				PlaySoundOnce(p);
			}

			if(p!=NULL)	free(p);
			break;

		case Victory:
			p=path_handler(AppPath, SOUND_DIR"\\victory.wav");

			//Testen ob Datei vorhanden mit file-open
			datei = fopen(p,"r");
			if(datei!=NULL)
			{
				//Datei ist vorhanden, schliessen und Sound abspielen
				fclose(datei);
				PlaySoundOnce(p);
			}

			if(p!=NULL)	free(p);
			break;

		case Ignore:
			p=path_handler(AppPath, SOUND_DIR"\\ignore.wav");

			//Testen ob Datei vorhanden mit file-open
			datei = fopen(p,"r");
			if(datei!=NULL)
			{
				//Datei ist vorhanden, schliessen und Sound abspielen
				fclose(datei);
				PlaySoundOnce(p);
			}

			if(p!=NULL)	free(p);
			break;

		case Intro:
			p=path_handler(AppPath, SOUND_DIR"\\intro.wav");

			//Testen ob Datei vorhanden mit file-open
			datei = fopen(p,"r");
			if(datei!=NULL)
			{
				//Datei ist vorhanden, schliessen und Sound abspielen
				fclose(datei);
				PlaySoundContinuous(p);
			}

			if(p!=NULL)	free(p);
			break;

		case Music:
			/*p=path_handler(AppPath, SOUND_DIR"\\music.wav");

			//Testen ob Datei vorhanden mit file-open
			datei = fopen(p,"r");
			if(datei!=NULL)
			{
				//Datei ist vorhanden, schliessen und Sound abspielen
				fclose(datei);
				PlaySoundContinuous(p);
			}

			if(p!=NULL)	free(p);*/
			break;

		case Pling:
			p=path_handler(AppPath, SOUND_DIR"\\pling.wav");

			//Testen ob Datei vorhanden mit file-open
			datei = fopen(p,"r");
			if(datei!=NULL)
			{
				//Datei ist vorhanden, schliessen und Sound abspielen
				fclose(datei);
				PlaySoundOnce(p);
			}

			if(p!=NULL)	free(p);
			break;

		case Bell:
			p=path_handler(AppPath, SOUND_DIR"\\bell.wav");

			//Testen ob Datei vorhanden mit file-open
			datei = fopen(p,"r");
			if(datei!=NULL)
			{
				//Datei ist vorhanden, schliessen und Sound abspielen
				fclose(datei);
				PlaySoundOnce(p);
			}

			if(p!=NULL)	free(p);
			break;
	}

	//Datei war nicht vorhanden, alle Sounds ausschalten und Meldung ausgeben
	if(datei == NULL)
	{
		Sound_On = 0;
		printf("\nSoundfile not found\nSound OFF\n");
	}
}
