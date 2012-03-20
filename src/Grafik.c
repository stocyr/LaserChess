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
/*  Author     : C. Stoller                                                  */
/*                                                                           */
/*  Email      : stolc2@bfh.ch                                               */
/*                                                                           */
/*  Creation   : 17.03.2012                                                  */
/*                                                                           */
/*  File       : Grafik.c                                                    */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/

#include "Grafik.h"
#include "LaserChess.h"


/*Umrechnung Windowskoord. zu Mapposition*/
/*
location pixel_to_map(location Mapkoordinaten)		//bekommt windowskoordinaten gibt mapkoordinaten zurück
{
	Mapkoordinaten.x = (x-(x%FIELD_SIZE))/FIELD_SIZE;				//nimmt Werte zwischen 0 und 7 an (da x von 0 bis 800)
	Mapkoordinaten.y = (PLAYGROUND_Y_MAX-1)-((y-(y%FIELD_SIZE))/FIELD_SIZE);			//nimmt Werte zwischen 0 und 5 an (da y von 0 bis 600)
	return Mapkoordinaten;
}
*/


/*Umrechnung Mapkoord. zu Windowskoord. Ecke links oben*/
/*
location map_to_pixel(location Windowskoordinaten)	//bekommt mapkoordinaten gibt windowskoordinaten zurück
{
	Windowskoordinaten.x *= FIELD_SIZE;					//0=>0; 1=>100; 2=>200; 3=>300; 4=>400; 5=>500; 6=>600; 7=>700
	Windowskoordinaten.y = (PLAYGROUND_Y_MAX-1)*FIELD_SIZE-(y*FIELD_SIZE);				//0=>500; 1=>400; 2=>300; 3=>200; 4=>100; 5=>0
	return Windowskoordinaten;
}
*/


/*Spielfeld zeichnen*/
void draw_playground()
{
	int i;
	InitGraphic(PLAYGROUND_X_MAX*FIELD_SIZE, PLAYGROUND_Y_MAX*FIELD_SIZE);								//initialisiert und öffnet ein 800*600 Grafikfenster
	DrawFilledRectangle(0, 0, PLAYGROUND_X_MAX*FIELD_SIZE, PLAYGROUND_Y_MAX*FIELD_SIZE,COL_BLACK, PLAYGROUND_Y_MAX - 1);		//zeichnet das schwarze Spielfeld
	DrawEmptyRectangle(0, 0, PLAYGROUND_X_MAX*FIELD_SIZE, PLAYGROUND_Y_MAX*FIELD_SIZE,COL_GREY, PLAYGROUND_Y_MAX - 1);		//zeichnet die Spielfeldumrandung

	for(i = 1; i < PLAYGROUND_Y_MAX; i++)
	{
		DrawLine(0, FIELD_SIZE*i, PLAYGROUND_X_MAX*FILED_SIZE, FIELD_SIZE*i, COL_GREY, 3);		//zeichnet die 5 grauen Horizontal-Linien
	}

	for(i = 1; i < PLAYGROUND_X_MAX; i++)
	{
		DrawLine(FIELD_SIZE*i, 0, FIELD_SIZE*i, PLAYGROUND_Y_MAX, COL_GREY, 3);					//zeichnet die 7 grauen Vertikal-Linien
	}
}
