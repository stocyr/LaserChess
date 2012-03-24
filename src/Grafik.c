/*****************************************************************************/
/*  o o o o      Berner Fachhochschule                                       */
/*        :...o  Technik und Informatik                                      */
/*****************************************************************************/
/*  Module     : LaserChess/Grafik                              Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Desc       : graphics functions                                          */
/*                                                                           */
/*  Procedures :                                                             */
/*                                                                           */
/*  Author     : J. Haldemann + N. Käser                                     */
/*                                                                           */
/*  Email      : haldj3@bfh.ch                                               */
/*                                                                           */
/*  Creation   : xx.03.2012                                                  */
/*                                                                           */
/*  File       : Grafik.c                                                    */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/

/*imports*/
#include "Grafik.h"

/*Umrechnung Windowskoord. zu Mapposition*/
location pixel_to_map(location Mapkoordinaten)	//bekommt windowskoordinaten gibt mapkoordinaten zurück
{
	Mapkoordinaten.x = (Mapkoordinaten.x-(Mapkoordinaten.x%FIELD_SIZE))/FIELD_SIZE;	//(x-(x%100)/100) nimmt Werte zwischen 0 und 7 an (da x von 0 bis 800)
	Mapkoordinaten.y = (PLAYGROUND_Y_MAX-1)-((Mapkoordinaten.y-(Mapkoordinaten.y%FIELD_SIZE))/FIELD_SIZE);	//(5-(y-(y%100)/100) nimmt Werte zwischen 0 und 5 an (da y von 0 bis 600)

	if(is_inside_map(Mapkoordinaten))	//errorhandling (wenn x genau 800 oder y genau 600)
	{
		return Mapkoordinaten;
	}
	else
	{
		Mapkoordinaten.x = -1;
		Mapkoordinaten.y = -1;
		return Mapkoordinaten;
	}
}

/*Umrechnung Mapkoord. zu Windowskoord. ECKE LINKS UNTEN!*/
location map_to_pixel(location Windowskoordinaten)	//bekommt mapkoordinaten gibt windowskoordinaten zurück
{
	Windowskoordinaten.x *= FIELD_SIZE;	//0=>0; 1=>100; 2=>200; 3=>300; 4=>400; 5=>500; 6=>600; 7=>700
	Windowskoordinaten.y = (PLAYGROUND_Y_MAX*FIELD_SIZE)-(Windowskoordinaten.y*FIELD_SIZE);	//(600-(y*100)) 0=>600; 1=>500; 2=>400; 3=>300; 4=>200; 5=>100
	return Windowskoordinaten;
}

/*Spielfeld zeichnen*/
void draw_playground()
{
	int i;	//Anzahl verschobene Felder
	InitGraphic(PLAYGROUND_X_MAX*FIELD_SIZE+2*FIELD_LINE_WIDTH, PLAYGROUND_Y_MAX*FIELD_SIZE+2*FIELD_LINE_WIDTH);			//initialisiert und öffnet ein 806*606 Grafikfenster
	DrawFilledRectangle(0, 0, PLAYGROUND_X_MAX*FIELD_SIZE, PLAYGROUND_Y_MAX*FIELD_SIZE, PLAYGROUND_COL, FIELD_LINE_WIDTH);	//zeichnet das schwarze Spielfeld
	DrawEmptyRectangle(0, 0, PLAYGROUND_X_MAX*FIELD_SIZE, PLAYGROUND_Y_MAX*FIELD_SIZE, LINE_COL, FIELD_LINE_WIDTH);			//zeichnet die Spielfeldumrandung

	for(i = 1; i < PLAYGROUND_Y_MAX; i++)
	{
		DrawLine(0, FIELD_SIZE*i, PLAYGROUND_X_MAX*FIELD_SIZE, FIELD_SIZE*i, LINE_COL, FIELD_LINE_WIDTH);	//zeichnet die 5 grauen Horizontal-Linien
	}

	for(i = 1; i < PLAYGROUND_X_MAX; i++)
	{
		DrawLine(FIELD_SIZE*i, 0, FIELD_SIZE*i, PLAYGROUND_Y_MAX*FIELD_SIZE, LINE_COL, FIELD_LINE_WIDTH);	//zeichnet die 7 grauen Vertikal-Linien
	}
}

/*Grüner Focus ("Umrandung") zeichnen*/
void draw_focus(location pos) //bekommt Mapkoordinaten und schreibt sie ins struct location pos
{
	location map_pos;				//initialisieren: struct location map_pos
	map_pos = map_to_pixel(pos);	//Umwandlung der Mapkoordinaten in Windowskoordinaten (Punkt links unten des ausgew. Feldes)
	DrawEmptyRectangle(map_pos.x+FOCUS_IDENT, map_pos.y+FOCUS_IDENT, FIELD_SIZE-2*FOCUS_IDENT, FIELD_SIZE-2*FOCUS_IDENT, FOCUS_COL, 2*FOCUS_IDENT);	//um 5 Pixel einrücken (x-5,y-5,90,90,Grün,2*5)
}

/*Überzeichnet (bzw. löscht) angegebene Mapposition*/
void draw_empty_field(location pos)	//bekommt Mapkoordinaten und schreibt sie ins struct location pos
{
	location map_pos;				//initialisieren: struct location map_pos
	map_pos = map_to_pixel(pos);	//Umwandlung der Mapkoordinaten in Windowskoordinaten (Punkt links unten des ausgew. Feldes)
	DrawFilledRectangle(map_pos.x, map_pos.y, FIELD_SIZE, FIELD_SIZE, PLAYGROUND_COL, FIELD_LINE_WIDTH);	//zeichnet gefülltes Viereck zum überdecken
}

/*Zeichnet Laser in der angegebenen Mapposition*/
void draw_laser (location pos, enum Direction dir)	//bekommt Mapkoordinaten und schreibt sie ins struct location pos
{
	int n;							//Aufzählvariable
	location map_pos;				//initialisieren: struct location map_pos
	map_pos = map_to_pixel (pos);	//Umwandlung der Mapkoordinaten in Windowskoordinaten (Punkt links unten des ausgew. Feldes)

    switch(dir) 					//Ausgangsposiotion der jeweiligen Richtung berechnen und Laser zeichnen
    {
        case RIGHT:
        	map_pos.y = map_pos.y + (FIELD_SIZE/2);
            for(n=0; n<=FIELD_SIZE; n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE erreicht
            {
            	DrawPixel(map_pos.x+n, map_pos.y, LASER_COL);
    //        	void WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
            }
            break;

        case UP:
        	map_pos.x = map_pos.x + (FIELD_SIZE/2);
            for(n=0; n<=FIELD_SIZE; n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE erreicht
            {
            	DrawPixel(map_pos.x, map_pos.y+n, LASER_COL);
      //      	void WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
            }
            break;

        case LEFT:
        	map_pos.x = map_pos.x + FIELD_SIZE;
        	map_pos.y = map_pos.y + (FIELD_SIZE/2);
            for(n=0; n<=FIELD_SIZE; n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE erreicht
            {
            	DrawPixel(map_pos.x-n, map_pos.y, LASER_COL);
       //     	void WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
            }
            break;

        case DOWN:
        	map_pos.x = map_pos.x + (FIELD_SIZE/2);
        	map_pos.y = map_pos.y + FIELD_SIZE;
            for(n=0; n<=FIELD_SIZE; n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE erreicht
            {
            	DrawPixel(map_pos.x, map_pos.y-n, LASER_COL);
       //     	void WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
            }
            break;
    }
}

/*Zeichnet 90°-Laser in der angegebenen Mapposition*/
void draw_angled_laser(location pos, enum Direction dir, int angle) //bekommt Mapkoordinaten und schreibt sie ins struct location pos,
//eine Richtung und einen 90° Winkel (entweder -1 = rechts oder 1 = links)
{
	int n;							//Aufzählvariable
	location map_pos;				//initialisieren: struct location map_pos
	map_pos = map_to_pixel (pos);	//Umwandlung der Mapkoordinaten in Windowskoordinaten (Punkt links unten des ausgew. Feldes)

	switch(angle)
	{
		case CW:	//Winkel nach Rechts
			switch(dir) 					//Ausgangsposiotion der jeweiligen Richtung berechnen und Laser in zwei Schritten zeichnen
			{
				case RIGHT:
					map_pos.y = map_pos.y + (FIELD_SIZE/2);
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x+n, map_pos.y, LASER_COL);	//von links nach rechts bis mitte
		//				void WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y-n, LASER_COL);	//von mitte nach unten bis ende
		//				void WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
				break;

				case UP:
					map_pos.x = map_pos.x + (FIELD_SIZE/2);
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y+n, LASER_COL);	//von unten nach oben bis mitte
		//				void WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x+n, map_pos.y, LASER_COL);	//von mitte nach rechts bis ende
		//				void WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
				break;

				case LEFT:
					map_pos.x = map_pos.x + FIELD_SIZE;
					map_pos.y = map_pos.y + (FIELD_SIZE/2);
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x-n, map_pos.y, LASER_COL);	//von rechts nach links bis mitte
		//				void WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y+n, LASER_COL);	//von mitte nach oben bis ende
		//				void WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
				break;

				case DOWN:
					map_pos.x = map_pos.x + (FIELD_SIZE/2);
					map_pos.y = map_pos.y + FIELD_SIZE;
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y-n, LASER_COL); //von oben nach unten bis mitte
			//			void WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x-n, map_pos.y, LASER_COL);	//von mitte nach links bis ende
			//			void WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
				break;
			}
		break;

		case CCW:	//Winkel nach Links
			switch(dir) 					//Ausgangsposiotion der jeweiligen Richtung berechnen und Laser in zwei Schritten zeichnen
			{
				case RIGHT:
					map_pos.y = map_pos.y + (FIELD_SIZE/2);
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x+n, map_pos.y, LASER_COL);	//von links nach rechts bis mitte
			//			void WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y+n, LASER_COL);	//von mitte nach oben bis ende
		//				void WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
				break;

				case UP:
					map_pos.x = map_pos.x + (FIELD_SIZE/2);
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y+n, LASER_COL);	//von unten nach oben bis mitte
			//			void WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x-n, map_pos.y, LASER_COL);	//von mitte nach links bis ende
		//				void WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
				break;

				case LEFT:
					map_pos.x = map_pos.x + FIELD_SIZE;
					map_pos.y = map_pos.y + (FIELD_SIZE/2);
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x-n, map_pos.y, LASER_COL);	//von rechts nach links bis mitte
		//				void WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y-n, LASER_COL);	//von mitte nach unten bis ende
		//				void WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
				break;

				case DOWN:
					map_pos.x = map_pos.x + (FIELD_SIZE/2);
					map_pos.y = map_pos.y + FIELD_SIZE;
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y-n, LASER_COL); //von oben nach unten bis mitte
			//			void WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x+n, map_pos.y, LASER_COL);	//von mitte nach rechts bis ende
		//				void WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
				break;
			}
		break;
	}
}

void draw_figure(pawn *figure)
{
	/*****************************************************************************/
	/*  Function   : draw_figure                                    Version 1.0  */
	/*****************************************************************************/
	/*                                                                           */
	/*  Function   : Draws figure at its location with its rotation/direction    */
	/*                                                                           */
	/*  Input Para : pawn *figure                                                */
	/*                                                                           */
	/*  Output     : -                                                           */
	/*                                                                           */
	/*  Author     : N. Kaeser                                                   */
	/*                                                                           */
	/*  Email      : kasen1@bfh.ch                                               */
	/*                                                                           */
	/*****************************************************************************/

	/*if(figure.Affiliation == PLAYER_RED)
	{

	}
	else //PLAYER_BLUE
	{
	}*/
}
void draw_mirror_destroyed(pawn *figure)
{
	/*****************************************************************************/
	/*  Function   : draw_mirror_destroyed                          Version 1.0  */
	/*****************************************************************************/
	/*                                                                           */
	/*  Function   : Draws/animates the destruction of a mirror.                 */
	/*               (For now, @V1.0, it only draws an empty field.)             */
	/*                                                                           */
	/*  Input Para : pawn *figure                                                */
	/*                                                                           */
	/*  Output     : -                                                           */
	/*                                                                           */
	/*  Author     : N. Kaeser                                                   */
	/*                                                                           */
	/*  Email      : kasen1@bfh.ch                                               */
	/*                                                                           */
	/*****************************************************************************/

	draw_empty_field(figure->Pos); //Feld löschen
	//Später evtl. Grafik von Zerstörung (Feld trotzdem vorher löschen)
}
void draw_king_destroyed(pawn *figure)
{
	/*****************************************************************************/
	/*  Function   : draw_king_destroyed                          Version 1.0  */
	/*****************************************************************************/
	/*                                                                           */
	/*  Function   : Draws/animates the destruction of the king.                 */
	/*               (For now, @V1.0, it only draws an empty field.)             */
	/*                                                                           */
	/*  Input Para : pawn *figure                                                */
	/*                                                                           */
	/*  Output     : -                                                           */
	/*                                                                           */
	/*  Author     : N. Kaeser                                                   */
	/*                                                                           */
	/*  Email      : kasen1@bfh.ch                                               */
	/*                                                                           */
	/*****************************************************************************/

	draw_empty_field(figure->Pos); //Feld löschen
	//Später evtl. Grafik von Zerstörung (Feld trotzdem vorher löschen)
}
