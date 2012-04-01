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
/*  Author     : J. Haldemann; N. Kaeser                                     */
/*                                                                           */
/*  Email      : haldj3@bfh.ch; kasen1@bfh.ch                                */
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


static void DrawTransformedImage(int x, int y, float Angle, float ScaleX, float ScaleY, int Image)
{
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

   int ImageWidth;
   int ImageHeight;

   /* Get dimensions of Image */
   GetImageSize(Image, &ImageWidth, &ImageHeight);

   ResetTransformations();

   /* Move coordinatesystem in the (assumed) centre of the immage */
   Translate(x, y);

   /* Scale and rotate the coordinatesystem */
   Scale(ScaleX, ScaleY);

   //Rotation in Grad
   Rotate(Angle);

   /* Move coordinatesystem back to origin */
   Translate(-ImageWidth/2.0, -ImageHeight/2.0);

   /* draw the image into the transformated coordinatesystem */
   /* results in a rotated and scaled image                  */
   DrawImage(Image, 0, 0);
   ResetTransformations();
}

/*****************************************************************************/
/*  Function   : draw_sharp_empty_rectangle                     Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Draws empty rectangle with sharp edges                      */
/*                                                                           */
/*  Input Para : int x, int y,                                               */
/*               int Width, int Height,                                      */
/*               ColorType Color,                                            */
/*               int LineWidth                                               */
/*                                                                           */
/*  Output     : -                                                           */
/*                                                                           */
/*  Author     : N. Kaeser                                                   */
/*                                                                           */
/*  Email      : kasen1@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/
void draw_sharp_empty_rectangle(int x, int y, int Width, int Height, ColorType Color, int LineWidth)
{
	int left = x;
	int right = x + Width;
	int top = y;
	int bottom = y + Height;
	DrawLine(left, top, right, top, Color, LineWidth);       //Top
	DrawLine(right, top, right, bottom, Color, LineWidth);   //Right
	DrawLine(right, bottom, left, bottom, Color, LineWidth); //Bottom
	DrawLine(left, bottom, left, top, Color, LineWidth);     //Left

}

/*Umrechnung Windowskoord. zu Mapposition*/
location pixel_to_map(location Windowskoordinaten)	//bekommt windowskoordinaten gibt mapkoordinaten zurück
{
	location Mapkoordinaten;

	if((Windowskoordinaten.x < 0) && (Windowskoordinaten.y < 0))	//Errorhandling (wenn falsche Koordinaten uebergeben wurden)
	{
		Mapkoordinaten.x = -1;
		Mapkoordinaten.y = -1;
		return Mapkoordinaten;
	}

	Mapkoordinaten.x = (int)(Windowskoordinaten.x / FIELD_SIZE);	// (x/100) nimmt Werte zwischen 0 und 7 an (da x von 0 bis 799)
	Mapkoordinaten.y =(PLAYGROUND_Y_MAX-1) - (int)(Windowskoordinaten.y / FIELD_SIZE);	//5 - (y-/100) nimmt Werte zwischen 5 und 0 an (da y von 0 bis 599)

	if(!is_inside_map(Mapkoordinaten)) //errorhandling (wenn x >= 800 oder y >= 600)
	{
		Mapkoordinaten.x = -1;
		Mapkoordinaten.y = -1;
	}

	return Mapkoordinaten;
}

/*Umrechnung Mapkoord. zu Windowskoord. ECKE LINKS OBEN!!!*/
location map_to_pixel(location Mapkoordinaten)	//bekommt mapkoordinaten gibt windowskoordinaten zurück
{
	location Windowskoordinaten;

	if((Mapkoordinaten.x < 0) && (Mapkoordinaten.y < 0)) //Errorhandling (wenn falsche Koordinaten uebergeben wurden)
	{
		Windowskoordinaten.x = -1;
		Windowskoordinaten.y = -1;
		return Windowskoordinaten;
	}

	Windowskoordinaten.x = Mapkoordinaten.x*FIELD_SIZE;	//(x*100) -> nimmt 0, 100, 200, 300, 400, 500, 600 oder 700 an
	Windowskoordinaten.y = (PLAYGROUND_Y_MAX*FIELD_SIZE-FIELD_SIZE)-(Mapkoordinaten.y*FIELD_SIZE);	//(500-(y*100)) 0=>500; 1=>400; 2=>300; 3=>200; 4=>100; 5=>0
	return Windowskoordinaten;
}

/*Spielfeld zeichnen*/
void draw_playground()
{
	int i;	//Anzahl verschobene Felder
	InitGraphic(PLAYGROUND_X_MAX*FIELD_SIZE+FIELD_LINE_WIDTH/2, PLAYGROUND_Y_MAX*FIELD_SIZE+FIELD_LINE_WIDTH/2);		//initialisiert und öffnet ein 801*601 Grafikfenster (1 Pixel Rand)
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
	map_pos = map_to_pixel (pos);	//Umwandlung der Mapkoordinaten in Windowskoordinaten (Punkt links oben des ausgew. Feldes)

    switch(dir) 					//Ausgangsposiotion der jeweiligen Richtung berechnen und Laser zeichnen
    {
        case RIGHT:	//Strich von Links nach Rechts
        	map_pos.y = map_pos.y + (FIELD_SIZE/2);	//Mitte der Linken-Seite
            for(n=0; n<=FIELD_SIZE; n++)	//Pixel schrittweise zeichnen bis FIELD_SIZE erreicht
            {
            	DrawPixel(map_pos.x+n, map_pos.y, LASER_COL);	//x wird inkrementiert
            	WaitMs (LASER_DELAY);	//Wartet die gegebene Zeit in ms (Millisekunden) ab
            }
            break;

        case UP:	//Strich von Unten nach Oben
        	map_pos.x = map_pos.x + (FIELD_SIZE/2);
            map_pos.y = map_pos.y + FIELD_SIZE;		//Mitte der Unteren-Seite
            for(n=0; n<=FIELD_SIZE; n++)	//Pixel schrittweise zeichnen bis FIELD_SIZE erreicht
            {
            	DrawPixel(map_pos.x, map_pos.y-n, LASER_COL);	//y wird dekrementiert
               	WaitMs (LASER_DELAY);	//Wartet die gegebene Zeit in ms (Millisekunden) ab
            }
            break;

        case LEFT:	//Strich von Rechts nach Links
        	map_pos.x = map_pos.x + FIELD_SIZE;
        	map_pos.y = map_pos.y + (FIELD_SIZE/2);	//Mitte der Rechten-Seite
            for(n=0; n<=FIELD_SIZE; n++)	//Pixel schrittweise zeichnen bis FIELD_SIZE erreicht
            {
            	DrawPixel(map_pos.x-n, map_pos.y, LASER_COL);	//x wird dekrementiert
            	WaitMs (LASER_DELAY);	//Wartet die gegebene Zeit in ms (Millisekunden) ab
            }
            break;

        case DOWN:	//Strich von Oben nach Unten
        	map_pos.x = map_pos.x + (FIELD_SIZE/2);	//Mitte der Oberen-Seite
        	for(n=0; n<=FIELD_SIZE; n++)	//Pixel schrittweise zeichnen bis FIELD_SIZE erreicht
        	{
        		DrawPixel(map_pos.x, map_pos.y+n, LASER_COL);	//y wird inkrementiert
                WaitMs (LASER_DELAY);	//Wartet die gegebene Zeit in ms (Millisekunden) ab
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
	map_pos = map_to_pixel (pos);	//Umwandlung der Mapkoordinaten in Windowskoordinaten (Punkt links oben des ausgew. Feldes)

	switch(angle)
	{
		case CW:	//Winkel nach Rechts
			switch(dir)	//Ausgangsposiotion der jeweiligen Richtung berechnen und Laser in zwei Schritten zeichnen
			{
				case RIGHT:	//Strich von Links nach Mitte und von Mitte nach Unten
					map_pos.y = map_pos.y + (FIELD_SIZE/2);	//Mitte der Linken-Seite
					for(n=0; n<=(FIELD_SIZE/2); n++)	//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x+n, map_pos.y, LASER_COL);	//x wird inkrementiert
						WaitMs (LASER_DELAY);	//Wartet die gegebene Zeit in ms (Millisekunden) ab
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)	//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y+n, LASER_COL);	//y wird inkrementiert
						WaitMs (LASER_DELAY);	//Wartet die gegebene Zeit in ms (Millisekunden) ab
					}
					break;

				case DOWN:	//Strich von Oben nach Mitte und von Mitte nach Links
					map_pos.x = map_pos.x + (FIELD_SIZE/2);	//Mitte der Oberen-Seite
					for(n=0; n<=(FIELD_SIZE/2); n++)	//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y+n, LASER_COL);	//y wird inkrementiert
						WaitMs (LASER_DELAY);	//Wartet die gegebene Zeit in ms (Millisekunden) ab
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)		//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x-n, map_pos.y, LASER_COL);	//x wird dekrementiert
						WaitMs (LASER_DELAY);		//Wartet die gegebene Zeit in ms (Millisekunden) ab
					}
					break;

				case LEFT:	//Strich von Rechts nach Mitte und von Mitte nach Oben
					map_pos.x = map_pos.x + FIELD_SIZE;
					map_pos.y = map_pos.y + (FIELD_SIZE/2);	//Mitte der Rechten-Seite
					for(n=0; n<=(FIELD_SIZE/2); n++)	//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x-n, map_pos.y, LASER_COL);	//x wird dekrementiert
						WaitMs (LASER_DELAY);	//Wartet die gegebene Zeit in ms (Millisekunden) ab
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)	//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y-n, LASER_COL);	//y wird dekrementiert
						WaitMs (LASER_DELAY);	//Wartet die gegebene Zeit in ms (Millisekunden) ab
					}
					break;

				case UP:	//Strich von Unten nach Mitte und von Mitte nach Rechts
					map_pos.x = map_pos.x + (FIELD_SIZE/2);
					map_pos.y = map_pos.y + FIELD_SIZE;		//Mitte der Unteren-Seite
					for(n=0; n<=(FIELD_SIZE/2); n++)	//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y-n, LASER_COL); //y wird dekrementiert
						WaitMs (LASER_DELAY);	//Wartet die gegebene Zeit in ms (Millisekunden) ab
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)	//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x+n, map_pos.y, LASER_COL);	//x wird inkrementiert
						WaitMs (LASER_DELAY);	//Wartet die gegebene Zeit in ms (Millisekunden) ab
					}
					break;
			}
			break;

		case CCW:	//Winkel nach Links
			switch(dir) //Ausgangsposiotion der jeweiligen Richtung berechnen und Laser in zwei Schritten zeichnen
			{
				case RIGHT:	//Strich von Links nach Mitte und von Mitte nach Oben
					map_pos.y = map_pos.y + (FIELD_SIZE/2);	//Mitte der Linken-Seite
					for(n=0; n<=(FIELD_SIZE/2); n++)	//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x+n, map_pos.y, LASER_COL);	//x wird inkrementiert
						WaitMs (LASER_DELAY);	//Wartet die gegebene Zeit in ms (Millisekunden) ab
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)	//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y-n, LASER_COL);	//y wird dekrementiert
						WaitMs (LASER_DELAY);	//Wartet die gegebene Zeit in ms (Millisekunden) ab
					}
					break;

				case UP:	//Strich von Unten nach Mitte und von Mitte nach Links
					map_pos.x = map_pos.x + (FIELD_SIZE/2);
					map_pos.y = map_pos.y + FIELD_SIZE;	//Mitte der Unteren-Seite
					for(n=0; n<=(FIELD_SIZE/2); n++)	//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y-n, LASER_COL); //y wird dekrementiert
						WaitMs (LASER_DELAY);	//Wartet die gegebene Zeit in ms (Millisekunden) ab
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)	//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x-n, map_pos.y, LASER_COL);	//x wird dekrementiert
						WaitMs (LASER_DELAY);	//Wartet die gegebene Zeit in ms (Millisekunden) ab
					}
					break;

				case LEFT:	//Strich von Rechts nach Mitte und von Mitte nach Unten
					map_pos.x = map_pos.x + FIELD_SIZE;
					map_pos.y = map_pos.y + (FIELD_SIZE/2);	//Mitte der Rechten-Seite
					for(n=0; n<=(FIELD_SIZE/2); n++)	//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x-n, map_pos.y, LASER_COL);	//x wird dekrementiert
						WaitMs (LASER_DELAY);	//Wartet die gegebene Zeit in ms (Millisekunden) ab
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)	//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y+n, LASER_COL);	//y wird inkrementiert
						WaitMs (LASER_DELAY);	//Wartet die gegebene Zeit in ms (Millisekunden) ab
					}
					break;

				case DOWN:	//Strich von Oben nach Mitte und von Mitte nach Rechts
					map_pos.x = map_pos.x + (FIELD_SIZE/2);	//Mitte der Oberen Seite
					for(n=0; n<=(FIELD_SIZE/2); n++)	//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x, map_pos.y+n, LASER_COL);	//y wird inkrementiert
						WaitMs (LASER_DELAY);	//Wartet die gegebene Zeit in ms (Millisekunden) ab
					}
					for(n=0; n<=(FIELD_SIZE/2); n++)	//Pixel schrittweise zeichnen bis FIELD_SIZE/2 erreicht
					{
						DrawPixel(map_pos.x+n, map_pos.y, LASER_COL);	//x wird inkrementiert
						WaitMs (LASER_DELAY);	//Wartet die gegebene Zeit in ms (Millisekunden) ab
					}
					break;
			}
			break;
	}
}

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
void destroy_figure_images()
{
	/*Nur Images die wirklich geladen waren (also ID>0) entfernen*/
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

/*****************************************************************************/
/*  Function   : path_handler                                   Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Combines the two strings path and file after checking       */
/*               if there's enough memory available                          */
/*                                                                           */
/*  Input Para : const char path[] - String with the path of file            */
/*               char file[]       - String with the filename                */
/*                                                                           */
/*  Output     : Returns string with the complete path                       */
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

	char *buffer = malloc(size);
	if(buffer == NULL) return NULL; //Nicht genuegend Speicher vorhanden

	sprintf(buffer, "%s%s", path, file); //Kompletter Pfad in buffer speichern
	return buffer;
}

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
char init_figure_images()
{
	char error = -1;
	char success = 1;

	//Variable mit der Errors uebertragen werden
	//(Damit nur am Schluss einmal destroy_figure_images() aufgerufen werden muss)
	char test = 0;

	/*Image laden und ID uebergeben. Wuerde eine nicht gefunden error setzten.*/
	Blue_king_img     = LoadImage(path_handler(AppPath, IMG_DIR"\\blue_king.png"));     if(Blue_king_img < 0)     test = error;
	Blue_mirror_img   = LoadImage(path_handler(AppPath, IMG_DIR"\\blue_mirror.png"));   if(Blue_mirror_img < 0)   test = error;
	Blue_splitter_img = LoadImage(path_handler(AppPath, IMG_DIR"\\blue_splitter.png")); if(Blue_splitter_img < 0) test = error;
	Blue_wall_img     = LoadImage(path_handler(AppPath, IMG_DIR"\\blue_wall.png"));     if(Blue_wall_img < 0)     test = error;
	Blue_cannon_img   = LoadImage(path_handler(AppPath, IMG_DIR"\\blue_cannon.png"));   if(Blue_cannon_img < 0)   test = error;

	Red_king_img      = LoadImage(path_handler(AppPath, IMG_DIR"\\red_king.png"));      if(Red_king_img < 0)      test = error;
	Red_mirror_img    = LoadImage(path_handler(AppPath, IMG_DIR"\\red_mirror.png"));    if(Red_mirror_img < 0)    test = error;
	Red_splitter_img  = LoadImage(path_handler(AppPath, IMG_DIR"\\red_splitter.png"));  if(Red_splitter_img < 0)  test = error;
	Red_wall_img      = LoadImage(path_handler(AppPath, IMG_DIR"\\red_wall.png"));      if(Red_wall_img < 0)      test = error;
	Red_cannon_img    = LoadImage(path_handler(AppPath, IMG_DIR"\\red_cannon.png"));    if(Red_cannon_img < 0)    test = error;

	Figure_error_img  = LoadImage(path_handler(AppPath, IMG_DIR"\\figure_error.png"));  if(Figure_error_img < 0)  test = error;

	//Check, ob Alle korrekt geladen wurden.
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
void draw_figure(pawn *figure)
{
	int figure_img; //Fuer Image ID der figur
	float angle = DIR_TO_DEG(figure->DIR); //Rotation in Grad

	//Figur Position in Pixelkoordinaten, uebersichtlicher
	location fig_pos = map_to_pixel(figure->Pos);

	draw_empty_field(figure->Pos); //Feld erstmal leeren

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
			//Keine gueltige Figur.. Kann eigentlich nur vorkommen,
			//wenn dem TYPE-enum manuell ein Wert zugewiesen wurde.
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
			//Keine gueltige Figur.. Kann eigentlich nur vorkommen,
			//wenn dem TYPE-enum manuell ein Wert zugewiesen wurde.
			figure_img = Figure_error_img;
		break;
		}
	}

	//Image mit ID figure_img an fig_pos mit Rotation angle und scale auf Bildschirm zeichnen
	DrawTransformedImage(fig_pos.x+FIELD_SIZE/2, fig_pos.y+FIELD_SIZE/2, angle, 100*PERCENT_FIELD_SIZE, 100*PERCENT_FIELD_SIZE, figure_img);
	DrawEmptyRectangle(fig_pos.x, fig_pos.y, FIELD_SIZE, FIELD_SIZE, LINE_COL, FIELD_LINE_WIDTH); //Zeichnet den dazugehoerigen Rahmen

	/*
	//Platzhalter/Test-Rectangle
	if(figure->PLAYER == PLAYER_RED) DrawEmptyRectangle(fig_pos.x+25, fig_pos.y+25, 50, 50, COL_RED, 2*FIELD_LINE_WIDTH);
	else DrawEmptyRectangle(fig_pos.x+25, fig_pos.y+25, 50, 50, COL_BLUE, 2*FIELD_LINE_WIDTH);
	*/
}

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
void draw_mirror_destroyed(pawn *figure)
{
	/*
		88888 .d88b.    888b. .d88b.
		  8   8P  Y8    8   8 8P  Y8  w
		  8   8b  d8    8   8 8b  d8       Zerstoerungs-Grafik verbessern
		  8   `Y88P'    888P' `Y88P'  w
	 */

	//ColorType TEST_COL = PLAYGROUND_COL; TEST_COL.Alpha = 0x77;


	//Figur Position in Pixelkoordinaten, uebersichtlicher
	location fig_pos = map_to_pixel(figure->Pos);
	int offset, old_offset;
	int size, old_size;

	int i;
	int n = FIELD_SIZE/(2*FIELD_LINE_WIDTH); //Anzahl Linien die ins Feld passen
	for(i=1; i <= n; i++)
	{
		old_offset = (i-1)*FIELD_LINE_WIDTH;
		old_size = FIELD_SIZE - 2*old_offset;
		offset = i*FIELD_LINE_WIDTH;
		size = FIELD_SIZE - 2*offset;
		/*
		 __________ . <-- Pixelfehler wegen abgerundeten Ecken bei DrawEmptyRectangle
		|  ______  |
		| |      | |
		| |      | |  Field with DrawEmptyRectangle inside
		| |______| |
		|__________|
		,_,
		offset
		  ,______,
		  size
		*/

		//Immer ein kleineres Rechteck zeichnen
		DrawEmptyRectangle(fig_pos.x + offset, fig_pos.y + offset, size, size, LASER_COL, FIELD_LINE_WIDTH);

		//Altes Rechteck uebermalen mit scharfen Ecken, damit keine Pixel uebrig bleiben
		if(i>1)draw_sharp_empty_rectangle(fig_pos.x+old_offset, fig_pos.y+old_offset, old_size, old_size, PLAYGROUND_COL, FIELD_LINE_WIDTH);

		//Bereich ausserhalb uebermalen (keine Pixelfehler mehr)
		/*pixel_fixer_width = offset - FIELD_LINE_WIDTH; if(!IS_EVEN(pixel_fixer_width)) pixel_fixer_width += 1;
		if(i>1)draw_sharp_empty_rectangle(fig_pos.x + offset/2, fig_pos.y + offset/2, size+offset, size+offset, TEST_COL, pixel_fixer_width);*/

		WaitMs(DESTROY_DELAY);
	}

	draw_empty_field(figure->Pos); //Feld loeschen

	/*Spaeter Grafik von Zerstoerung (Feld trotzdem vorher leoschen)*/
}

/*****************************************************************************/
/*  Function   : draw_winner_text                               Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Writes winner text on screen                                */
/*                                                                           */
/*  Input Para : pawn *hit_king                                                */
/*                                                                           */
/*  Output     : -                                                           */
/*                                                                           */
/*  Author     : N. Kaeser                                                   */
/*                                                                           */
/*  Email      : kasen1@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/
void draw_winner_text(pawn *hit_king)
{
	/*
		88888 .d88b.    888b. .d88b.
		  8   8P  Y8    8   8 8P  Y8  w
		  8   8b  d8    8   8 8b  d8       Keine magic-numbers: Textlaenge zu offset umrechnen
		  8   `Y88P'    888P' `Y88P'  w    Evtl. groessere Schrift.
	 */
	location fig_pos = map_to_pixel(hit_king->Pos);
	DrawTextXY(fig_pos.x + FIELD_SIZE/2 - 15, fig_pos.y + FIELD_SIZE/2 -5, COL_WHITE, "PLAYER");
	if(hit_king->PLAYER == PLAYER_BLUE)
	{
		DrawTextXY(fig_pos.x + FIELD_SIZE/2 - 8, fig_pos.y + FIELD_SIZE/2 + 5, COL_WHITE, "RED");
	}
	else //PLYER_RED
	{
		DrawTextXY(fig_pos.x + FIELD_SIZE/2 - 10, fig_pos.y + FIELD_SIZE/2 + 5, COL_WHITE, "BLUE");
	}
	DrawTextXY(fig_pos.x + FIELD_SIZE/2 - 12, fig_pos.y + FIELD_SIZE/2 + 15, COL_WHITE, "WINS");
}

/*****************************************************************************/
/*  Function   : draw_king_destroyed                          Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Draws/animates the destruction of the king.                 */
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
void draw_king_destroyed(pawn *figure)
{
	/*
		88888 .d88b.    888b. .d88b.
		  8   8P  Y8    8   8 8P  Y8  w
		  8   8b  d8    8   8 8b  d8       Zerstoerungs-Grafik
		  8   `Y88P'    888P' `Y88P'  w
	 */

	//Figur Position in Pixelkoordinaten, uebersichtlicher
	location fig_pos = map_to_pixel(figure->Pos);
	int offset, old_offset;
	int size, old_size;
	int speed = DESTROY_DELAY;

	int i;
	int n = 3*(FIELD_SIZE/(2*FIELD_LINE_WIDTH)); //Anzahl Linien die ins Feld passen *3 damits wieder groesser wird
	for(i=1; i <= n; i++)
	{
		if(i>=n/3)speed = DESTROY_DELAY/2; //Ab dem Zeitpunkt wo es wieder grösser wird, doppelte Geschwindigkeit

		old_offset = (i-1)*FIELD_LINE_WIDTH;
		old_size = FIELD_SIZE - 2*old_offset;
		offset = i*FIELD_LINE_WIDTH;
		size = FIELD_SIZE - 2*offset;
		/*
		 __________ . <-- Pixelfehler wegen abgerundeten Ecken bei DrawEmptyRectangle
		|  ______  |
		| |      | |
		| |      | |  Field with DrawEmptyRectangle inside
		| |______| |
		|__________|
		,_,
		offset
		  ,______,
		  size
		*/

		//Immer ein kleineres Rechteck zeichnen
		DrawEmptyRectangle(fig_pos.x + offset, fig_pos.y + offset, size, size, LASER_COL, FIELD_LINE_WIDTH);

		//Altes Rechteck uebermalen mit scharfen Ecken, damit keine Pixel uebrig bleiben
		if(i>1)draw_sharp_empty_rectangle(fig_pos.x+old_offset, fig_pos.y+old_offset, old_size, old_size, PLAYGROUND_COL, FIELD_LINE_WIDTH);

		//Bereich ausserhalb uebermalen (keine Pixelfehler mehr)
		/*pixel_fixer_width = offset - FIELD_LINE_WIDTH; if(!IS_EVEN(pixel_fixer_width)) pixel_fixer_width += 1;
		if(i>1)draw_sharp_empty_rectangle(fig_pos.x + offset/2, fig_pos.y + offset/2, size+offset, size+offset, TEST_COL, pixel_fixer_width);*/

		WaitMs(speed);
	}

	draw_winner_text(figure);
}
