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


/*Umrechnung Windowskoord. zu Mapposition*/
/*
location pixel_to_map(location Mapkoordinaten)		//bekommt windowskoordinaten gibt mapkoordinaten zurück
{
	Mapkoordinaten.x = (x-(x%100))/100;				//nimmt Werte zwischen 0 und 7 an (da x von 0 bis 800)
	Mapkoordinaten.y = 5-((y-(y%100))/100);			//nimmt Werte zwischen 0 und 5 an (da y von 0 bis 600)
	return Mapkoordinaten;
}
*/


/*Umrechnung Mapkoord. zu Windowskoord. Ecke links oben*/
/*
location map_to_pixel(location Windowskoordinaten)	//bekommt mapkoordinaten gibt windowskoordinaten zurück
{
	Windowskoordinaten.x *= 100;					//0=>0; 1=>100; 2=>200; 3=>300; 4=>400; 5=>500; 6=>600; 7=>700
	Windowskoordinaten.y = 500-(y*100);				//0=>500; 1=>400; 2=>300; 3=>200; 4=>100; 5=>0
	return Windowskoordinaten;
}
*/


/*Spielfeld zeichnen*/
void draw_playground()
{
	InitGraphic (800,600);								//initialisiert und öffnet ein 800*600 Grafikfenster
	DrawFilledRectangle (0,0,800,600,COL_BLACK,5);		//zeichnet das schwarze Spielfeld
	DrawEmptyRectangle (0,0,800,600,COL_GREY,5);		//zeichnet die Spielfeldumrandung
	DrawLine(0,100,800,100,COL_GREY,3);					//zeichnet die 5 grauen Horizontal-Linien
	DrawLine(0,200,800,200,COL_GREY,3);
	DrawLine(0,300,800,300,COL_GREY,3);
	DrawLine(0,400,800,400,COL_GREY,3);
	DrawLine(0,500,800,500,COL_GREY,3);

	DrawLine(100,0,100,600,COL_GREY,3);					//zeichnet die 7 grauen Vertikal-Linien
	DrawLine(200,0,200,600,COL_GREY,3);
	DrawLine(300,0,300,600,COL_GREY,3);
	DrawLine(400,0,400,600,COL_GREY,3);
	DrawLine(500,0,500,600,COL_GREY,3);
	DrawLine(600,0,600,600,COL_GREY,3);
	DrawLine(700,0,700,600,COL_GREY,3);
}
