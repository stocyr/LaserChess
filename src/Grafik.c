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
static void DrawTransformedImage(int x, int y, float Angle, float ScaleX, float ScaleY, int Image);


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
	InitGraphic(2*PLAYGROUND_X_MAX*FIELD_SIZE+FIELD_LINE_WIDTH, 2*PLAYGROUND_Y_MAX*FIELD_SIZE+FIELD_LINE_WIDTH);				//initialisiert und öffnet ein 806*606 Grafikfenster
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
	DrawEmptyRectangle(map_pos.x, map_pos.y, FIELD_SIZE, FIELD_SIZE, LINE_COL, FIELD_LINE_WIDTH);			//zeichnet den dazugehörigen Rahmen
}

/*Zeichnet Laser in der angegebenen Mapposition*/
void draw_laser (location pos, enum Direction dir)	//bekommt Mapkoordinaten und schreibt sie ins struct location pos und enum Direction dir
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
            	WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
            }
            break;

        case UP:
        	map_pos.x = map_pos.x + (FIELD_SIZE/2);
            for(n=0; n<=FIELD_SIZE; n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE erreicht
            {
            	DrawPixel(map_pos.x, map_pos.y+n, LASER_COL);
            	WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
            }
            break;

        case LEFT:
        	map_pos.x = map_pos.x + FIELD_SIZE;
        	map_pos.y = map_pos.y + (FIELD_SIZE/2);
            for(n=0; n<=FIELD_SIZE; n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE erreicht
            {
            	DrawPixel(map_pos.x-n, map_pos.y, LASER_COL);
            	WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
            }
            break;

        case DOWN:
        	map_pos.x = map_pos.x + (FIELD_SIZE/2);
        	map_pos.y = map_pos.y + FIELD_SIZE;
            for(n=0; n<=FIELD_SIZE; n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE erreicht
            {
            	DrawPixel(map_pos.x, map_pos.y-n, LASER_COL);
            	WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
            }
            break;
    }
}

/*Zeichnet 90°-Laser in der angegebenen Mapposition*/
void draw_angled_laser(location pos, enum Direction dir, enum Angle angle) //bekommt Mapkoordinaten und schreibt sie ins struct location pos,
//eine Richtung (enum Direction dir) und einen 90° Winkel (entweder -1 = rechts oder 1 = links)
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
						WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y-n, LASER_COL);	//von mitte nach unten bis ende
						WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
				break;

				case UP:
					map_pos.x = map_pos.x + (FIELD_SIZE/2);
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y+n, LASER_COL);	//von unten nach oben bis mitte
						WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x+n, map_pos.y, LASER_COL);	//von mitte nach rechts bis ende
						WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
				break;

				case LEFT:
					map_pos.x = map_pos.x + FIELD_SIZE;
					map_pos.y = map_pos.y + (FIELD_SIZE/2);
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x-n, map_pos.y, LASER_COL);	//von rechts nach links bis mitte
						WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y+n, LASER_COL);	//von mitte nach oben bis ende
						WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
				break;

				case DOWN:
					map_pos.x = map_pos.x + (FIELD_SIZE/2);
					map_pos.y = map_pos.y + FIELD_SIZE;
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y-n, LASER_COL); //von oben nach unten bis mitte
						WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x-n, map_pos.y, LASER_COL);	//von mitte nach links bis ende
						WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
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
						WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y+n, LASER_COL);	//von mitte nach oben bis ende
						WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
				break;

				case UP:
					map_pos.x = map_pos.x + (FIELD_SIZE/2);
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y+n, LASER_COL);	//von unten nach oben bis mitte
						WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x-n, map_pos.y, LASER_COL);	//von mitte nach links bis ende
						WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
				break;

				case LEFT:
					map_pos.x = map_pos.x + FIELD_SIZE;
					map_pos.y = map_pos.y + (FIELD_SIZE/2);
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x-n, map_pos.y, LASER_COL);	//von rechts nach links bis mitte
						WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y-n, LASER_COL);	//von mitte nach unten bis ende
						WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
				break;

				case DOWN:
					map_pos.x = map_pos.x + (FIELD_SIZE/2);
					map_pos.y = map_pos.y + FIELD_SIZE;
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y-n, LASER_COL); //von oben nach unten bis mitte
						WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x+n, map_pos.y, LASER_COL);	//von mitte nach rechts bis ende
						WaitMs (LASER_SPEED);		//Wartet die gegebene Zeit in ms (Milisekunden) ab.
					}
				break;
			}
		break;
	}
}

void destroy_figure_images()
{
	/*****************************************************************************/
	/*  Function   : destroy_figure_images                          Version 1.0  */
	/*****************************************************************************/
	/*                                                                           */
	/*  Function   : Deletes with init_figure_images() loaded images from memory */
	/*                                                                           */
	/*  Input Para : -                                                           */
	/*                                                                           */
	/*  Output     : -                                                           */
	/*                                                                           */
	/*  Author     : N. Kaeser                                                   */
	/*                                                                           */
	/*  Email      : kasen1@bfh.ch                                               */
	/*                                                                           */
	/*****************************************************************************/

	/*
		88888 .d88b.    888b. .d88b.       Abklaeren, ob LoadImage() bei erfolgreichem
		  8   8P  Y8    8   8 8P  Y8  w    Laden auch 0 zurueck geben kann, oder nur
		  8   8b  d8    8   8 8b  d8       Werte >0. Evtl dann anpassen.
		  8   `Y88P'    888P' `Y88P'  w    (Auch in init_figure_images())
	 */

	if (Blue_king_img > 0)     DestroyImage(Blue_king_img);
	if (Blue_mirror_img > 0)   DestroyImage(Blue_mirror_img);
	if (Blue_splitter_img > 0) DestroyImage(Blue_splitter_img);
	if (Blue_wall_img > 0)     DestroyImage(Blue_wall_img);
	if (Blue_cannon_img > 0)   DestroyImage(Blue_cannon_img);

	if (Red_king_img > 0)      DestroyImage(Red_king_img);
	if (Red_mirror_img > 0)    DestroyImage(Red_mirror_img);
	if (Red_splitter_img > 0)  DestroyImage(Red_splitter_img);
	if (Red_wall_img > 0)      DestroyImage(Red_wall_img);
	if (Red_cannon_img > 0)    DestroyImage(Red_cannon_img);

	if (Figure_error_img > 0)  DestroyImage(Figure_error_img);
}

char init_figure_images()
{
	/*****************************************************************************/
	/*  Function   : init_figure_images                             Version 1.0  */
	/*****************************************************************************/
	/*                                                                           */
	/*  Function   : Loads images of figures from files into memory              */
	/*                                                                           */
	/*  Input Para : -                                                           */
	/*                                                                           */
	/*  Output     : Returns 1 if successful, otherwise 0                        */
	/*                                                                           */
	/*  Author     : N. Kaeser                                                   */
	/*                                                                           */
	/*  Email      : kasen1@bfh.ch                                               */
	/*                                                                           */
	/*****************************************************************************/

	/*
		88888 .d88b.    888b. .d88b.       Abklaeren, ob LoadImage() bei erfolgreichem
		  8   8P  Y8    8   8 8P  Y8  w    Laden auch 0 zurueck geben kann, oder nur
		  8   8b  d8    8   8 8b  d8       Werte >0. Evtl dann anpassen.
		  8   `Y88P'    888P' `Y88P'  w    (Auch in destroy_figure_images())
	 */

	char error = -1;
	char success = 1;

	//Variable, mit der Errors uebertragen werden
	//(Damit nur am Schluss einmal destroy_figure_images() aufgerufen werden muss)
	char test = 0;

	Blue_king_img     = LoadImage(IMG_PATH "blue_king.gif");     if(Blue_king_img < 0)     test = error;
	Blue_mirror_img   = LoadImage(IMG_PATH "blue_mirror.gif");   if(Blue_mirror_img < 0)   test = error;
	Blue_splitter_img = LoadImage(IMG_PATH "blue_splitter.gif"); if(Blue_splitter_img < 0) test = error;
	Blue_wall_img     = LoadImage(IMG_PATH "blue_wall.gif");     if(Blue_wall_img < 0)     test = error;
	Blue_cannon_img   = LoadImage(IMG_PATH "blue_cannon.gif");   if(Blue_cannon_img < 0)   test = error;

	Red_king_img      = LoadImage(IMG_PATH "red_king.gif");     if(Red_king_img < 0)       test = error;
	Red_mirror_img    = LoadImage(IMG_PATH "red_mirror.gif");   if(Red_mirror_img < 0)     test = error;
	Red_splitter_img  = LoadImage(IMG_PATH "red_splitter.gif"); if(Red_splitter_img < 0)   test = error;
	Red_wall_img      = LoadImage(IMG_PATH "red_wall.gif");     if(Red_wall_img < 0)       test = error;
	Red_cannon_img    = LoadImage(IMG_PATH "red_cannon.gif");   if(Red_cannon_img < 0)     test = error;

	Figure_error_img  = LoadImage(IMG_PATH "figure_error.gif");   if(Figure_error_img < 0) test = error;

	if(test == error)
	{
		destroy_figure_images(); //Falls einige Images trotzdem erfolgreich geladen wurden, korrekt entfernen.
		return error;
	}
	else
	{
		return success;
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

	/*
		88888 .d88b.    888b. .d88b.
		  8   8P  Y8    8   8 8P  Y8  w    Rotation: Fehlermeldungen sind wegen
		  8   8b  d8    8   8 8b  d8       SetEditedImage(figure_img) entstanden
		  8   `Y88P'    888P' `Y88P'  w    (bei SetEditedImage(ID_WINDOW) alles ok)
	 */

	draw_empty_field(figure->Pos);

	int figure_img; //Fuer Image ID der figur
	//float angle = figure->DIR * PI/2; //Rotation in Radiant

	/*figure_img die richtigen Image ID zuweisen.*/
	if(figure->PLAYER == PLAYER_RED)
	{
		switch(figure->TYPE)
		{
		case KING:
			figure_img = Red_king_img;
		break;
		case MIRROR:
			figure_img = Red_mirror_img;
		break;
		case SPLITTER:
			figure_img = Red_splitter_img;
		break;
		case WALL:
			figure_img = Red_wall_img;
		break;
		case CANNON:
			figure_img = Red_cannon_img;
		break;
		default:
			//Keine gueltige Figur..
			figure_img = Figure_error_img;
		break;
		}
	}
	else //PLAYER_BLUE
	{
		switch(figure->TYPE)
		{
		case KING:
			figure_img = Blue_king_img;
		break;
		case MIRROR:
			figure_img = Blue_mirror_img;
		break;
		case SPLITTER:
			figure_img = Blue_splitter_img;
		break;
		case WALL:
			figure_img = Blue_wall_img;
		break;
		case CANNON:
			figure_img = Blue_cannon_img;
		break;
		default:
			//Keine gueltige Figur..
			figure_img = Figure_error_img;
		break;
		}
	}

	/*Bild im Speicher drehen, damit es mit richtiger DIR auf Bildschirm gezeichnet wird.*/
	//SetEditedImage(figure_img);
	//Rotate(angle);
	//SetEditedImage(ID_WINDOW);

	//GetPixel(1,1);
	//printf("%d ",ID_WINDOW);
	printf("%d (%d)",figure_img, figure->TYPE);

	DrawImage(figure_img, 10, 10);
	//DrawImage(figure_img, map_to_pixel(figure->Pos).x, map_to_pixel(figure->Pos).y);
	//DrawTransformedImage(map_to_pixel(figure->Pos).x,  map_to_pixel(figure->Pos).y,  20, 1, 1, figure_img);
	//DrawEmptyRectangle(map_to_pixel(figure->Pos).x, map_to_pixel(figure->Pos).y, FIELD_SIZE, FIELD_SIZE, LINE_COL, FIELD_LINE_WIDTH);	//zeichnet den dazugehörigen Rahmen

	/*Bild im Speicher zurueckdrehen in originale Ausrichtung.*/
	/*SetEditedImage(figure_img);
	Rotate(-angle);
	SetEditedImage(ID_WINDOW);*/
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

	/*
		88888 .d88b.    888b. .d88b.
		  8   8P  Y8    8   8 8P  Y8  w
		  8   8b  d8    8   8 8b  d8       Zerstoerungs-Grafik
		  8   `Y88P'    888P' `Y88P'  w
	 */

	draw_empty_field(figure->Pos); //Feld loeschen

	/*Spaeter Grafik von Zerstoerung (Feld trotzdem vorher leoschen)*/
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

	/*
		88888 .d88b.    888b. .d88b.
		  8   8P  Y8    8   8 8P  Y8  w
		  8   8b  d8    8   8 8b  d8       Zerstoerungs-Grafik
		  8   `Y88P'    888P' `Y88P'  w
	 */

	draw_empty_field(figure->Pos); //Feld loeschen

	/*Spaeter Grafik von Zerstoerung (Feld trotzdem vorher loeschen)*/
}

/*****************************************************************************/
/*  Procedure   : DrawTransformedImage                                       */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Draws the given Image skaled and rotated at the given      */
/*                position into the current image                            */
/*                                                                           */
/*  Type        : Global                                                     */
/*                                                                           */
/*  Input Para  : ImageId Handle of image to draw                            */
/*                x, y    Position to draw image at                          */
/*                Scalex  Scalingfactor for x axis (float value)             */
/*                Scaley  Scalingfactor for y axis (float value)             */
/*                Angle   Angle to rotate Image (in rad)                     */
/*                                                                           */
/*  Output Para : none                                                       */
/*                                                                           */
/*  Author      : I. Oesch                                                   */
/*                                                                           */
/*  History     : 06.01.2010  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
static void DrawTransformedImage(int x, int y, float Angle, float ScaleX, float ScaleY, int Image)
{
   int ImageWidth;
   int ImageHeight;

   /* Get dimensions of Image */
   GetImageSize(Image, &ImageWidth, &ImageHeight);

   ResetTransformations();


   /* Move coordinatesystem in the (assumed) centre of the immage */
   Translate(x, y);

   /* Scale and rotate the coordinatesystem */
   Scale(ScaleX, ScaleY);

   Rotate(Angle);

   /* Move coordinatesystem back to origin */
   Translate(-ImageWidth/2.0, -ImageHeight/2.0);

   /* draw the image into the transformated coordinatesystem */
   /* results in a rotated and scaled image                  */
   DrawImage(Image, 0, 0);
   ResetTransformations();
}
/*****************************************************************************/
/*  End         : DrawTransformedImage                                       */
/*****************************************************************************/

