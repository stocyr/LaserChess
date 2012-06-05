/*****************************************************************************/
/*  o o o o      Berner Fachhochschule                                       */
/*        :...o  Technik und Informatik                                      */
/*****************************************************************************/
/*  Module     : LaserChess/Grafik                              Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : All the graphics functions                                  */
/*                                                                           */
/*  Procedures : DrawTransformedImage(), draw_sharp_empty_rectangle(),       */
/*               pixel_to_map(), map_to_pixel(), draw_playground(),          */
/*               scale_handler, draw_focus(), draw_rot_focus(),              */
/*               draw_empty_field(), draw_half_laser(), draw_laser(),        */
/*               draw_angled_laser(), destroy_images(), init_images(),       */
/*               draw_figure(), draw_figure_destroyed(),                     */
/*               draw_invert_colors(), draw_winner_text()                    */
/*                                                                           */
/*  Author     : J. Haldemann; N. Kaeser                                     */
/*                                                                           */
/*  Email      : haldj3@bfh.ch; kasen1@bfh.ch                                */
/*                                                                           */
/*  Hystory    : 12.03.2012  File created                                    */
/*                                                                           */
/*  File       : Grafik.c                                                    */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/

/*imports*/
#include "Grafik.h"


/*****************************************************************************/
/*  Procedure   : DrawTransformedImage                                       */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Draws the given Image scaled and rotated at the given      */
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
/*  Output Para : -                                                          */
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

   /* Rotation in Grad */
   Rotate(Angle);

   /* Scale the coordinatesystem */
   Scale(ScaleX, ScaleY);

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
/*  Input Para : x and y koord. in windowskoord.                             */
/*               int Width, int Height, ColorType Color, int LineWidth       */
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
	//Linie auf SquareCap einstellen
	SetQtOptions(Qt_PenCapStyle, 0x10);

	//Parameter berechnen
	int left = x;
	int right = x + Width;
	int top = y;
	int bottom = y + Height;

	DrawLine(left, top, right, top, Color, LineWidth);       //Top
	DrawLine(right, top, right, bottom, Color, LineWidth);   //Right
	DrawLine(right, bottom, left, bottom, Color, LineWidth); //Bottom
	DrawLine(left, bottom, left, top, Color, LineWidth);     //Left
}


/*****************************************************************************/
/*  Function   : pixel_to_map                                   Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Convert windowskoord. to map position                       */
/*                                                                           */
/*  Input Para : x and y as windowskoord.                                    */
/*                                                                           */
/*  Output     : -                                                           */
/*                                                                           */
/*  Author     : J. Haldemann                                                */
/*                                                                           */
/*  Email      : haldj3@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

location pixel_to_map(location Windowskoordinaten)	//bekommt windowskoordinaten gibt mapkoordinaten zurück
{
	location Mapkoordinaten;

	if((Windowskoordinaten.x < 0) && (Windowskoordinaten.y < 0))	//Errorhandling (wenn falsche Koordinaten uebergeben wurden)
	{
		Mapkoordinaten.x = ERROR;
		Mapkoordinaten.y = ERROR;
		return Mapkoordinaten;
	}

	Mapkoordinaten.x = (int)(Windowskoordinaten.x / FIELD_SIZE);	// (x/100) nimmt Werte zwischen 0 und 7 an (da x von 0 bis 799)
	Mapkoordinaten.y =(PLAYGROUND_Y_MAX-1) - (int)(Windowskoordinaten.y / FIELD_SIZE);	//5 - (y-/100) nimmt Werte zwischen 5 und 0 an (da y von 0 bis 599)

	if(!is_inside_map(Mapkoordinaten)) //errorhandling (wenn x >= 800 oder y >= 600)
	{
		Mapkoordinaten.x = ERROR;
		Mapkoordinaten.y = ERROR;
	}

	return Mapkoordinaten;
}


/*****************************************************************************/
/*  Function   : map_to_pixel                                   Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Convert mappositon to windowskoord. -> Point upper left!    */
/*                                                                           */
/*  Input Para : x and y as map position                                     */
/*                                                                           */
/*  Output     : -                                                           */
/*                                                                           */
/*  Author     : J. Haldemann                                                */
/*                                                                           */
/*  Email      : haldj3@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

location map_to_pixel(location Mapkoordinaten)	//bekommt mapkoordinaten gibt windowskoordinaten zurück
{
	location Windowskoordinaten;

	if((Mapkoordinaten.x < 0) && (Mapkoordinaten.y < 0)) //Errorhandling (wenn falsche Koordinaten uebergeben wurden)
	{
		Windowskoordinaten.x = ERROR;
		Windowskoordinaten.y = ERROR;
		return Windowskoordinaten;
	}

	Windowskoordinaten.x = Mapkoordinaten.x*FIELD_SIZE;	//(x*100) -> nimmt 0, 100, 200, 300, 400, 500, 600 oder 700 an
	Windowskoordinaten.y = (PLAYGROUND_Y_MAX*FIELD_SIZE-FIELD_SIZE)-(Mapkoordinaten.y*FIELD_SIZE);	//(500-(y*100)) 0=>500; 1=>400; 2=>300; 3=>200; 4=>100; 5=>0
	return Windowskoordinaten;
}


/*****************************************************************************/
/*  Function   : draw_playground                                Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Draws a playground (field and lines)                        */
/*                                                                           */
/*  Input Para : -                                                           */
/*                                                                           */
/*  Output     : -                                                           */
/*                                                                           */
/*  Author     : J. Haldemann                                                */
/*                                                                           */
/*  Email      : haldj3@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

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


/*****************************************************************************/
/*  Function   : scale_handler                                  Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Returns the percentage for scaling the image to field size. */
/*                                                                           */
/*  Input Para : Image_ID, a valid ID of a loaded Image file                 */
/*                                                                           */
/*  Output     : size scale, the x- and y-scalefactor                        */
/*               in percentage of the field size                             */
/*                                                                           */
/*  Author     : N. Kaeser                                                   */
/*                                                                           */
/*  Email      : kasen1@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

size scale_handler(int Image_ID)
{
	//Bildgroesse ermitteln und vorlaeufig in scale speichern
	size scale;
	GetImageSize(Image_ID, &scale.Width, &scale.Height);

	//Bildgroesse relativ zur Feldgroesse und in Prozent (damit float nicht noetig)
	scale.Width = 100 * FIELD_SIZE / scale.Width;
	scale.Height = 100 * FIELD_SIZE / scale.Height;

	return scale;
}


/*****************************************************************************/
/*  Function   : draw_focus                                     Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Draws a focus in the selected field                         */
/*                                                                           */
/*  Input Para : x and y as map position                                     */
/*                                                                           */
/*  Output     : -                                                           */
/*                                                                           */
/*  Author     : J. Haldemann                                                */
/*                                                                           */
/*  Email      : haldj3@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

void draw_focus(location pos) //bekommt Mapkoordinaten und schreibt sie ins struct location pos
{
	location map_pos;				//initialisieren: struct location map_pos
	map_pos = map_to_pixel(pos);	//Umwandlung der Mapkoordinaten in Windowskoordinaten
	DrawEmptyRectangle(map_pos.x+FOCUS_IDENT, map_pos.y+FOCUS_IDENT, FIELD_SIZE-2*FOCUS_IDENT, FIELD_SIZE-2*FOCUS_IDENT, FOCUS_COL, 2*FOCUS_IDENT);	//um 5 Pixel einrücken (x-5,y-5,90,90,Grün,2*5)
}


/*****************************************************************************/
/*  Function   : draw_rot_focus                                 Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Draws a rotation-image on the selected field                */
/*                                                                           */
/*  Input Para : x and y as map position                                     */
/*                                                                           */
/*  Output     : -                                                           */
/*                                                                           */
/*  Author     : N. Kaeser                                                   */
/*                                                                           */
/*  Email      : kasen1@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

void draw_rot_focus(location pos)
{
	//Position in Pixelkoordinaten
	location map_pos = map_to_pixel(pos);

	//Skalierungsfaktor ermitteln, damit Bildgroesse relativ zur Feldgroesse gezeichnet wird
	size scale = scale_handler(Rot_focus_img); //(in Prozent)

	//Image mit korrekt skalierter Groesse zeichnen
	DrawTransformedImage(map_pos.x+FIELD_SIZE/2, map_pos.y+FIELD_SIZE/2, 0, scale.Width*PERCENT, scale.Height*PERCENT, Rot_focus_img);
}


/*****************************************************************************/
/*  Function   : draw_empty_field                               Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Deletes the selected field (reset)                          */
/*                                                                           */
/*  Input Para : x and y as map position                                     */
/*                                                                           */
/*  Output     : -                                                           */
/*                                                                           */
/*  Author     : J. Haldemann                                                */
/*                                                                           */
/*  Email      : haldj3@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

void draw_empty_field(location pos)	//bekommt Mapkoordinaten und schreibt sie ins struct location pos
{
	location map_pos;				//initialisieren: struct location map_pos
	map_pos = map_to_pixel(pos);	//Umwandlung der Mapkoordinaten in Windowskoordinaten
	DrawFilledRectangle(map_pos.x, map_pos.y, FIELD_SIZE, FIELD_SIZE, PLAYGROUND_COL, FIELD_LINE_WIDTH);	//zeichnet gefülltes Viereck zum überdecken
	DrawEmptyRectangle(map_pos.x, map_pos.y, FIELD_SIZE, FIELD_SIZE, LINE_COL, FIELD_LINE_WIDTH);			//zeichnet den dazugehörigen Rahmen

	//DrawLine(map_pos.x,map_pos.y-5,map_pos.x,map_pos.y+10,COL_RED,1); //
	//DrawLine(map_pos.x-5,map_pos.y,map_pos.x+10,map_pos.y,COL_RED,1); //Added by kasen1 for testing
	//DrawLine(map_pos.x+FIELD_SIZE,map_pos.y-5,map_pos.x+FIELD_SIZE,map_pos.y,COL_RED,1); //
	//DrawLine(map_pos.x-5,map_pos.y+FIELD_SIZE,map_pos.x,map_pos.y+FIELD_SIZE,COL_RED,1); //
}


/*****************************************************************************/
/*  Function   : draw_half_laser                                Version 1.1  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Help-function for draw_laser and draw_angled_laser.         */
/*               Draws half the laser in the selected field                  */
/*               (v1.1: Laser now glowing)                                   */
/*                                                                           */
/*  Input Para : x and y as map position and direction                       */
/*                                                                           */
/*  Output     : -                                                           */
/*                                                                           */
/*  Author     : N. Kaeser                                                   */
/*                                                                           */
/*  Email      : kasen1@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

void draw_half_laser(location start_pos, enum Direction dir)
{
	//Linie auf FlatCap einstellen
	SetQtOptions(Qt_PenCapStyle, 0x00);

	//Laserfarbe leicht transparent machen fuer Glow
	ColorType glow_col = LASER_COL; glow_col.Alpha = 0x40;

	//Directions fuer x
	int dir_x;
	if(dir == 0) dir_x = 1;  //     0
	if(dir == 1) dir_x = 0;  // -1 -¦- 1
	if(dir == 2) dir_x = -1; //     0
	if(dir == 3) dir_x = 0;

	//Directions fuer y
	int dir_y;
	if(dir == 0) dir_y = 0;  //    -1
	if(dir == 1) dir_y = -1; //  0 -¦- 0
	if(dir == 2) dir_y = 0;  //     1
	if(dir == 3) dir_y = 1;

	//Pixelweise zeichnen bis FIELD_SIZE/2 erreicht
	//Also wird immer ein 2-Pixel kleineres Rechteck gezeichnet, bis Kantenlaenge = 0
	int n;
	for(n=1; n<=FIELD_SIZE/2; n++)
	{
		//Glow zeichnen:
		// --------                   -,
		// --------         -,         |
		// ======== =Laser   |Glow 1   |Glow 2
		// --------         -'         |
		// --------                   -'

		//Glow 1, zuerst
		DrawLine(start_pos.x+dir_x*n, start_pos.y+dir_y*n, start_pos.x+dir_x*(n+1), start_pos.y+dir_y*(n+1), glow_col, 2*LASER_WIDTH);
		//Laser darueber, mit Farbe Weiss wegen Glow (Laserschwert effekt :) )
		DrawLine(start_pos.x+dir_x*n, start_pos.y+dir_y*n, start_pos.x+dir_x*(n+1), start_pos.y+dir_y*(n+1), COL_WHITE, LASER_WIDTH);
		//Glow 2 ueber beide, damit Laser auch einwehnig Farbe hat
		DrawLine(start_pos.x+dir_x*n, start_pos.y+dir_y*n, start_pos.x+dir_x*(n+1), start_pos.y+dir_y*(n+1), glow_col, 3*LASER_WIDTH);

		WaitMs(LASER_DELAY);
	}
}


/*****************************************************************************/
/*  Function   : draw_laser                                     Version 1.1  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Draws the laser in the selected field                       */
/*               (v1.1 uses new function draw_angled_laser())                */
/*                                                                           */
/*  Input Para : x and y as map position and direction                       */
/*                                                                           */
/*  Output     : -                                                           */
/*                                                                           */
/*  Author     : J. Haldemann, N. Kaeser                                     */
/*                                                                           */
/*  Email      : haldj3@bfh.ch, kasen1@bfh.ch                                */
/*                                                                           */
/*****************************************************************************/

void draw_laser (location pos, enum Direction dir)	//bekommt Mapkoordinaten und schreibt sie ins struct location pos und enum Direction dir
{
	location map_pos = map_to_pixel(pos);
	location start_pos;

	//Start Position fuer x umrechnen
	int start_x = dir;
	if(dir == 3)start_x = 1;
	// x+__1__
	//  |  |  |
	// 0|  |  |2    *halbe Feldgroesse
	//  |__|__|
	//     1
	start_pos.x = map_pos.x + start_x * FIELD_SIZE/2;

	//Start Position fuer y umrechnen
	int start_y = dir+1;
	if(dir == 2)start_y = 1;
	if(dir == 3)start_y = 0;
	// y+__0__
	//  |     |
	// 1|-----|1    *halbe Feldgroesse
	//  |_____|
	//     2
	start_pos.y = map_pos.y + start_y * FIELD_SIZE/2;

	//Bis zur Feldmitte zeichnen
	draw_half_laser(start_pos, dir);

	//Feldmitte als neue Startposition
	start_pos.x = map_pos.x + FIELD_SIZE/2;
	start_pos.y = map_pos.y + FIELD_SIZE/2;

	//Von Feldmitte an in gleicher Richtung zeichnen
	draw_half_laser(start_pos, dir);

/*Version 1.0*/
    /*switch(dir) 					//Ausgangsposiotion der jeweiligen Richtung berechnen und Laser zeichnen
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
    }*/
}


/*****************************************************************************/
/*  Function   : draw_angled_laser                              Version 1.1  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Draws the angled laser in the selected field                */
/*               (v1.1 uses new function draw_angled_laser())                */
/*                                                                           */
/*  Input Para : pos in map-coordinates, direction and angle;                */
/*               dir, the direction of the laser                             */
/*               angle, for the reflection (-1 right, 1 left)                */
/*                                                                           */
/*  Output     : -                                                           */
/*                                                                           */
/*  Author     : J. Haldemann, N. Kaeser                                     */
/*                                                                           */
/*  Email      : haldj3@bfh.ch, kasen1@bfh.ch                                */
/*                                                                           */
/*****************************************************************************/

void draw_angled_laser(location pos, enum Direction dir, enum Angle angle)
{
	location map_pos = map_to_pixel(pos);
	location start_pos;

	//Start Position fuer x umrechnen
	int start_x = dir;
	if(dir == 3) start_x = 1;
	// x+__1__
	//  |  |  |
	// 0|  |  |2    *halbe Feldgroesse
	//  |__|__|
	//     1
	start_pos.x = map_pos.x + start_x * FIELD_SIZE/2;

	//Start Position fuer y umrechnen
	int start_y = dir+1;
	if(dir == 2) start_y = 1;
	if(dir == 3) start_y = 0;
	// y+__0__
	//  |     |
	// 1|-----|1    *halbe Feldgroesse
	//  |_____|
	//     2
	start_pos.y = map_pos.y + start_y * FIELD_SIZE/2;

	//Bis zur Feldmitte zeichnen
	draw_half_laser(start_pos, dir);

	//Reflection sound abspielen
	play_sound(Reflection);

	//Laserfarbe halbtransparent machen fuer Ecke
	ColorType glow_col = LASER_COL; glow_col.Alpha = 0x80;

	//Ecke mit gefuelltem Kreis abrunden. (Nicht moeglich mit Qt-Optionen, da einzelne Linien gezeichnet werden)
	DrawFilledCircle(start_pos.x-LASER_WIDTH, start_pos.y-LASER_WIDTH, 2*LASER_WIDTH, 2*LASER_WIDTH, glow_col, 1);

	//Feldmitte als neue Startposition
	start_pos.x = map_pos.x + FIELD_SIZE/2;
	start_pos.y = map_pos.y + FIELD_SIZE/2;

	//Neue Direction nach Ablenkung
	dir += angle; NORM(dir);

	//Von Feldmitte an in neuer Richtung zeichnen
	draw_half_laser(start_pos, dir);

/*Version 1.0*/
	/*switch(angle)
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
						DrawPixel(map_pos.x+(FIELD_SIZE/2), map_pos.y+n, LASER_COL);	//y wird inkrementiert
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
						DrawPixel(map_pos.x-n, map_pos.y+(FIELD_SIZE/2), LASER_COL);	//x wird dekrementiert
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
						DrawPixel(map_pos.x-(FIELD_SIZE/2), map_pos.y-n, LASER_COL);	//y wird dekrementiert
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
						DrawPixel(map_pos.x+n, map_pos.y-(FIELD_SIZE/2), LASER_COL);	//x wird inkrementiert
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
						DrawPixel(map_pos.x+(FIELD_SIZE/2), map_pos.y-n, LASER_COL);	//y wird dekrementiert
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
						DrawPixel(map_pos.x-n, map_pos.y-(FIELD_SIZE/2), LASER_COL);	//x wird dekrementiert
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
						DrawPixel(map_pos.x-(FIELD_SIZE/2), map_pos.y+n, LASER_COL);	//y wird inkrementiert
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
						DrawPixel(map_pos.x+n, map_pos.y+(FIELD_SIZE/2), LASER_COL);	//x wird inkrementiert
						WaitMs (LASER_DELAY);	//Wartet die gegebene Zeit in ms (Millisekunden) ab
					}
					break;
			}
			break;
	}*/
}


/*****************************************************************************/
/*  Function   : destroy_images                                 Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Deletes with init_images() loaded images from memory        */
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

void destroy_images()
{
	/*Nur Images die wirklich geladen waren (also ID>=0) entfernen*/
	if(Blue_king_img >= 0)     DestroyImage(Blue_king_img);
	if(Blue_mirror_img >= 0)   DestroyImage(Blue_mirror_img);
	if(Blue_splitter_img >= 0) DestroyImage(Blue_splitter_img);
	if(Blue_wall_img >= 0)     DestroyImage(Blue_wall_img);
	if(Blue_cannon_img >= 0)   DestroyImage(Blue_cannon_img);

	if(Red_king_img >= 0)      DestroyImage(Red_king_img);
	if(Red_mirror_img >= 0)    DestroyImage(Red_mirror_img);
	if(Red_splitter_img >= 0)  DestroyImage(Red_splitter_img);
	if(Red_wall_img >= 0)      DestroyImage(Red_wall_img);
	if(Red_cannon_img >= 0)    DestroyImage(Red_cannon_img);

	if(Fig_error_img >= 0)     DestroyImage(Fig_error_img);
	if(Rot_focus_img >= 0)     DestroyImage(Rot_focus_img);
}


/*****************************************************************************/
/*  Function   : init_images                                    Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Loads images from files into memory                         */
/*                                                                           */
/*  Input Para : -                                                           */
/*                                                                           */
/*  Output     : returns SUCCESS if successful, otherwise ERROR              */
/*                                                                           */
/*  Author     : N. Kaeser                                                   */
/*                                                                           */
/*  Email      : kasen1@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

int init_images()
{
	char *p; //path

	//Variable mit der Errors uebertragen werden
	//(Damit nur am Schluss einmal destroy_figure_images() aufgerufen werden muss)
	int test = 0;

	//Image laden und ID uebergeben. Pfad wieder freigeben. Wuerde eine nicht gefunden ERROR setzten.
	Blue_king_img     = LoadImage(p=path_handler(AppPath, IMG_DIR"\\blue_king.png"));    if(p!=NULL)free(p); if(Blue_king_img<0)    test=ERROR;
	Blue_mirror_img   = LoadImage(p=path_handler(AppPath, IMG_DIR"\\blue_mirror.png"));  if(p!=NULL)free(p); if(Blue_mirror_img<0)  test=ERROR;

	Blue_splitter_img = LoadImage(p=path_handler(AppPath, IMG_DIR"\\blue_splitter.png"));if(p!=NULL)free(p); if(Blue_splitter_img<0)test=ERROR;
	Blue_wall_img     = LoadImage(p=path_handler(AppPath, IMG_DIR"\\blue_wall.png"));    if(p!=NULL)free(p); if(Blue_wall_img<0)    test=ERROR;
	Blue_cannon_img   = LoadImage(p=path_handler(AppPath, IMG_DIR"\\blue_cannon.png"));  if(p!=NULL)free(p); if(Blue_cannon_img<0)  test=ERROR;

	Red_king_img      = LoadImage(p=path_handler(AppPath, IMG_DIR"\\red_king.png"));     if(p!=NULL)free(p); if(Red_king_img<0)     test=ERROR;
	Red_mirror_img    = LoadImage(p=path_handler(AppPath, IMG_DIR"\\red_mirror.png"));   if(p!=NULL)free(p); if(Red_mirror_img<0)   test=ERROR;
	Red_splitter_img  = LoadImage(p=path_handler(AppPath, IMG_DIR"\\red_splitter.png")); if(p!=NULL)free(p); if(Red_splitter_img<0) test=ERROR;
	Red_wall_img      = LoadImage(p=path_handler(AppPath, IMG_DIR"\\red_wall.png"));     if(p!=NULL)free(p); if(Red_wall_img<0)     test=ERROR;
	Red_cannon_img    = LoadImage(p=path_handler(AppPath, IMG_DIR"\\red_cannon.png"));   if(p!=NULL)free(p); if(Red_cannon_img<0)   test=ERROR;

	Fig_error_img     = LoadImage(p=path_handler(AppPath, IMG_DIR"\\figure_error.png")); if(p!=NULL)free(p); if(Fig_error_img<0)    test=ERROR;
	Rot_focus_img     = LoadImage(p=path_handler(AppPath, IMG_DIR"\\rot_focus.png"));    if(p!=NULL)free(p); if(Rot_focus_img<0)    test=ERROR;

	//Check, ob Alle korrekt geladen wurden.
	if(test == ERROR)
	{
		destroy_images(); //Falls einige Images trotzdem erfolgreich geladen wurden, korrekt entfernen.
		return ERROR;
	}
	else
	{
		return SUCCESS;
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
	//Fuer Image ID der figur
	int figure_img;
	//Rotation in Grad
	float angle = DIR_TO_DEG(figure->DIR);

	//Figur Position in Pixelkoordinaten, uebersichtlicher
	location fig_pos = map_to_pixel(figure->Pos);

	//Feld erstmal leeren
	draw_empty_field(figure->Pos);

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
			figure_img = Fig_error_img;
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
			figure_img = Fig_error_img;
		break;
		}
	}

	//Bildgroesse relativ zur Feldgroesse
	size scale = scale_handler(figure_img);

	//Image mit ID figure_img an fig_pos mit Rotation angle und scale auf Bildschirm zeichnen
	DrawTransformedImage(fig_pos.x+FIELD_SIZE/2, fig_pos.y+FIELD_SIZE/2, angle, scale.Width*PERCENT, scale.Height*PERCENT, figure_img);

	//Den dazugehoerigen Rahmen wieder zeichnen
	DrawEmptyRectangle(fig_pos.x, fig_pos.y, FIELD_SIZE, FIELD_SIZE, LINE_COL, FIELD_LINE_WIDTH);
}


/*****************************************************************************/
/*  Function   : draw_figure_destroyed                          Version 1.3  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Draws/animates the destruction of a mirror.                 */
/*               (V1.0, it only draws an empty field)                        */
/*               (V1.1, "Melting"-animation with rectangles)                 */
/*               (V1.2, offset increases always 1 pixel, not laser width)    */
/*               (V1.3, New animation, with glow)                            */
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

void draw_figure_destroyed(pawn *figure)
{
	//Farbe erstellen, Playground-Farbe aber mit leichter Transparenz
	ColorType col_alpha_playground = PLAYGROUND_COL; col_alpha_playground.Alpha = 0x20;

	//Figur Position in Pixelkoordinaten, uebersichtlicher
	location fig_pos = map_to_pixel(figure->Pos);

	int offset, start_offset, size, space_width, space_offset;
	int destroy_line_width = 2; //Bei Aenderung, nur zu geradem Wert, da Ungerade zur Leserlichkeit nicht umgerechnet werden!

	//Halbe Feldlinienbreite aufrunden, damit nicht eine Pixelline & -zeile der Umrandung ueberzeichnet wird
	int half_fieldline_width = (FIELD_LINE_WIDTH + !IS_EVEN(FIELD_LINE_WIDTH)) / 2;

	//Startoffset berechnen, mit korrekt gerundeten Werten.
	//So, dass innere Kante von Feldlinie genau aeussere Kante des Rechtecks beruehrt
	start_offset = half_fieldline_width + destroy_line_width/2;

	//Immer ein kleineres Rechteck zeichnen
	for(offset=start_offset; offset < FIELD_SIZE/2; offset++) //Von innerhalb der Feldlinie bis zur Feldmitte
	{
		//Aktuelle Groesse des Rechtecks berechnen
		size = FIELD_SIZE - 2*offset;// +!IS_EVEN(FIELD_LINE_WIDTH);

		//Rechteck mit aktuellem offset & size zeichen
		draw_sharp_empty_rectangle(fig_pos.x + offset, fig_pos.y + offset, size, size, LASER_COL, destroy_line_width);


		//Flaeche(Leeres Rechteck) zwischen Feldlinien-Innenkannte und Rechteck-Aussenkannte berechnen
		space_width = offset - half_fieldline_width - destroy_line_width/2;
		space_offset = half_fieldline_width + space_width/2;

		//Flaeche mit leicht transparentem Rechteck uebermalen
		if(offset>start_offset) //Beim erstenmal nicht, da noch gar keine Flaeche zwischen Rand und Rechteck vorhanden ist
			draw_sharp_empty_rectangle(	fig_pos.x + space_offset, fig_pos.y + space_offset,
										FIELD_SIZE - 2*space_offset - IS_EVEN(FIELD_LINE_WIDTH),
										FIELD_SIZE - 2*space_offset - IS_EVEN(FIELD_LINE_WIDTH),
										col_alpha_playground, space_width);

		WaitMs(DESTROY_DELAY);
	}

	draw_empty_field(figure->Pos); //Feld noch komplett loeschen

/*Version 1.2*/
/*
	//Figur Position in Pixelkoordinaten, uebersichtlicher
	location fig_pos = map_to_pixel(figure->Pos);
	int offset, start_offset, old_offset, size, old_size;

	//Halbe Linienbreite aufrunden, da bei rectangle ausserhalb Distanz nach innen wichtig ist
	int half_field_line = (FIELD_LINE_WIDTH+!IS_EVEN(FIELD_LINE_WIDTH)) / 2;
	//Halbe Laserdicke abrunden, da bei rectangle innerhalb Distanz nach aussen wichtig ist
	int half_laser_line = (LASER_WIDTH - !IS_EVEN(LASER_WIDTH)) / 2;

	//Startoffset berechnen, mit korrekt gerundeten Werten.
	//So, dass innere Kante von Feldlinie genau aeussere Kante des Rechtecks beruehrt
	start_offset = half_field_line+half_laser_line;

	//Immer ein kleineres Rechteck zeichnen und altes uebermalen
	for(offset=start_offset; offset < FIELD_SIZE/2; offset++) //Von innerhalb der Feldlinie bis zur Feldmitte
	{
		//  __________
		// |  ______. | <-- Pixelfehler wegen abgerundeten Ecken bei DrawEmptyRectangle
		// | |      | |
		// | |      | | Feld mit DrawEmptyRectangle drin
		// | |______| |
		// |__________|
		// ,_,
		// offset
		// ,______,
		// size
		//
		//offset rechts(oben) nicht immer gleich wie links(unten), aufgrund gerader/ungerader Pixelanzahl
		size = FIELD_SIZE - 2*offset -!IS_EVEN(LASER_WIDTH) +!IS_EVEN(FIELD_LINE_WIDTH);

		//Altes offset und alte size
		old_offset = offset - 1;
		//offset rechts(oben) nicht immer gleich wie links(unten), aufgrund gerader/ungerader Pixelanzahl
		old_size = FIELD_SIZE - 2*old_offset -!IS_EVEN(LASER_WIDTH) +!IS_EVEN(FIELD_LINE_WIDTH);

		//Altes Rechteck uebermalen, das erstemal nicht
		if(offset>start_offset)draw_sharp_empty_rectangle(fig_pos.x + old_offset, fig_pos.y + old_offset, old_size, old_size, PLAYGROUND_COL, LASER_WIDTH);
		//if(offset>start_offset)draw_sharp_empty_rectangle(fig_pos.x + old_offset/2, fig_pos.y + old_offset/2, FIELD_SIZE-old_offset, FIELD_SIZE-old_offset, TEST_COL, old_offset-5);

		//Pixelfehler in den Ecken verhindern
		draw_sharp_empty_rectangle(fig_pos.x + offset, fig_pos.y + offset, size, size, PLAYGROUND_COL, LASER_WIDTH);

		//Rechteck mit aktuellem offset zeichen
		DrawEmptyRectangle(fig_pos.x + offset, fig_pos.y + offset, size, size, LASER_COL, LASER_WIDTH);

		WaitMs(DESTROY_DELAY);
	}

	draw_empty_field(figure->Pos); //Feld loeschen
*/
/*Version 1.1*/
/*
	//Figur Position in Pixelkoordinaten, uebersichtlicher
	location fig_pos = map_to_pixel(figure->Pos);
	int offset, old_offset, size, old_size;
	int half_field_line = FIELD_LINE_WIDTH/2 + !IS_EVEN(FIELD_LINE_WIDTH); //Halbe Linienbreite, aufrunden

	//Immer ein kleineres Rechteck zeichnen und altes uebermalen
	int i;
	int n = FIELD_SIZE/(2*LASER_WIDTH); //Anzahl Linien die ins Feld passen
	for(i=0; i < n; i++)
	{
		/
		 __________
		|  ______. |  <-- Pixelfehler wegen abgerundeten Ecken bei DrawEmptyRectangle
		| |      | |
		| |      | |  Feld mit DrawEmptyRectangle drin
		| |______| |
		|__________|
		,_,
		offset
		  ,______,
		  size
		/
		offset = half_field_line + i*LASER_WIDTH + LASER_WIDTH/2;
		size = FIELD_SIZE - 2*offset +IS_EVEN(LASER_WIDTH);

		//Altes offset und size genau gleich, einfach mit (i-1)
		old_offset = half_field_line + (i-1)*LASER_WIDTH + LASER_WIDTH/2;
		old_size = FIELD_SIZE - 2*old_offset +IS_EVEN(LASER_WIDTH);

		//Immer ein kleineres Rechteck zeichnen
		draw_sharp_empty_rectangle(fig_pos.x + offset, fig_pos.y + offset, size, size, PLAYGROUND_COL, LASER_WIDTH); //Damit Pixel in den Ecken weg sind
		DrawEmptyRectangle(fig_pos.x + offset, fig_pos.y + offset, size, size, LASER_COL, LASER_WIDTH);

		//Altes Rechteck uebermalen mit scharfen Ecken, damit keine Pixel uebrig bleiben
		if(i>0)draw_sharp_empty_rectangle(fig_pos.x + old_offset, fig_pos.y + old_offset, old_size, old_size, PLAYGROUND_COL, LASER_WIDTH);

		WaitMs(DESTROY_DELAY);
	}

	draw_empty_field(figure->Pos); //Feld loeschen*/
}


/*****************************************************************************/
/*  Function   : draw_invert_colors                             Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Inverts the colors of the defined part.                     */
/*                                                                           */
/*  Input Para : x and y for start position; width and height for the size   */
/*                                                                           */
/*  Output     : -                                                           */
/*                                                                           */
/*  Author     : N. Kaeser                                                   */
/*                                                                           */
/*  Email      : kasen1@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

void draw_invert_colors(int x, int y, int width, int height)
{
	//Im XOR-Modus ein weisses Rechteck ueber gesammten Playground zeichnen.
	//Farbwerte werden somit mit OxFF XOR verknuepft -> invertiert
	SetDrawMode(DM_XOR);
	DrawFilledRectangle(x, y, width, height, COL_WHITE,0);
	//Wieder normaler Modus
	SetDrawMode(DM_OVER);
}


/*****************************************************************************/
/*  Function   : draw_winner_text                               Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Writes winner text on screen                                */
/*                                                                           */
/*  Input Para : pawn *hit_king                                              */
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
	//Figur Position in Pixelkoordinaten
	/*location fig_pos = map_to_pixel(hit_king->Pos);
	fig_pos.x += FIELD_SIZE/2; //Verschieben zu Mitte des Feldes
	fig_pos.y += FIELD_SIZE/2 + WIN_TEXT_SIZE/2; //So verschieben, dass Text in Mitte des Feldes*/

	//Position in Playgroundmitte
	location fig_pos = {PG_WIDTH/2, PG_HEIGHT/2};

	//Popup-Flaeche mit Rahmen
	DrawFilledRectangle(fig_pos.x-FIELD_SIZE, fig_pos.y-FIELD_SIZE, FIELD_SIZE*2, FIELD_SIZE*2, COL_BLACK, FIELD_LINE_WIDTH);
	DrawEmptyRectangle(fig_pos.x-FIELD_SIZE, fig_pos.y-FIELD_SIZE, FIELD_SIZE*2, FIELD_SIZE*2, LASER_COL, FIELD_LINE_WIDTH);

	//Schrift Optionen
	SelectFont(WIN_TEXT_FONT, WIN_TEXT_SIZE, FONT_BOLD);

	//Text-Informationen erhalten
	TextDimensionType a_text = GetTextDimensions(WIN_TEXT_TOP);     //Erste Zeile
	TextDimensionType b_text = GetTextDimensions("BLUE");           //Zweite Zeile: Blau
	TextDimensionType r_text = GetTextDimensions("RED");            //Zweite Zeile: Rot
	TextDimensionType c_text = GetTextDimensions(WIN_TEXT_BOTTOM);  //Dritte Zeile

	//Offsets, berechnet durch Stringlaenge & Schriftgroesse
	int a_offset = a_text.Length/2;
	int b_offset = b_text.Length/2;
	int r_offset = r_text.Length/2;
	int c_offset = c_text.Length/2;
	int text_size = a_text.Up;
	int text_space = a_text.Up / 3;

	//Erste Zeile mit Offset zeichnen
	DrawTextXY(fig_pos.x - a_offset, fig_pos.y - (text_size/2 + text_space), COL_WHITE, WIN_TEXT_TOP);

	//Zweite Zeile mit Offset und korrektem Text zeichnen
	if(hit_king->PLAYER == PLAYER_BLUE)
	{
		DrawTextXY(fig_pos.x - r_offset, fig_pos.y + text_size/2, COL_RED, "RED");
	}
	else //PLYER_RED
	{
		DrawTextXY(fig_pos.x - b_offset, fig_pos.y + text_size/2, COL_BLUE, "BLUE");
	}

	//Dritte Zeile mit Offset zeichnen
	DrawTextXY(fig_pos.x - c_offset, fig_pos.y + (text_size*1.5 + text_space), COL_WHITE, WIN_TEXT_BOTTOM);
}
