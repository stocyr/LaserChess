#ifndef GRAFIK_H
#define GRAFIK_H

/*****************************************************************************/
/*  o o o o      Berner Fachhochschule                                       */
/*        :...o  Technik und Informatik                                      */
/*****************************************************************************/
/*  Header     : LaserChess/Grafik                              Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Header for graphics functions                               */
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
/*  File       : Grafik.h                                                    */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/

/*imports*/
#include <stdio.h>
#include <stdlib.h>

#include "window.h"
#include "LaserChess.h"
#include "Logik.h"
#include "Spiel.h"

/*Grundsätzliche Grafik Definitionen*/
#define FIELD_SIZE 100                            //Feldbreite in Pixel
#define FIELD_LINE_WIDTH 3                        //Breite der Spielfeldlinien in Pixel
#define LINE_COL COL_GREY                         //Linienfarbe
#define PLAYGROUND_COL COL_BLACK                  //Spielfeldfarbe
#define FOCUS_COL COL_GREEN                       //Fokusfarbe
#define FOCUS_IDENT 2                             //Einzurückende Pixel der Focusfunktion
#define LASER_COL COL_GREEN                       //Laserfarbe
#define LASER_DELAY 3                             //Verzoegerung beim Zeichnen des Lasers in ms
#define LASER_WIDTH 2                             //Dicke des Laserstrahls
#define IMG_DIR "\\img"                           //Ordnerpfad zu den Grafiken der Figuren (Pfad relativ zu *ApplicationPath)
#define SOUND_DIR "\\sounds"                      //Ordnerpfad zu den Spielsounds (Pfad relativ zu *ApplicationPath)
#define WIN_TEXT_FONT "Impact"                    //Schriftart des Gewinnner-Textes
#define WIN_TEXT_TOP "PLAYER"                     //Erste Zeile des Gewinner-Textes, naechste Zeile wird "RED" oder "BLUE" sein
#define WIN_TEXT_BOTTOM "WINS!"                   //Dritte/Letzte Zeile des Gewinner-Textes vorherige Zeile wird "RED" oder "BLUE" sein
#define PERCENT 0.01                              //Fuer die umrechnung Faktor <-> Prozent

/*Grafik Definitionen berechnet aus anderen Definitionen*/
#define PG_WIDTH PLAYGROUND_X_MAX*FIELD_SIZE      //Playground Breite
#define PG_HEIGHT PLAYGROUND_Y_MAX*FIELD_SIZE     //Playground Hoehe
#define DESTROY_DELAY (LASER_DELAY*5)             //Zerstoerungsverzoegerung, gleich schnell wie Laser waere zu schnell.
#define WIN_TEXT_SIZE (FIELD_SIZE/5)              //Schriftgroesse in points/pixel. (FIELD_SIZE/5) ergibt gerade richtige Groesse.

/*Rotations Definitionen*//*
#define PI 3.14159265358979323846                 //Kopiert aus math.h
#define RAD_TO_DEG(x) ((x) * 360/(2*PI))          //Radiant zu Grad umwandeln
#define DEG_TO_RAD(x) ((x) * (2*PI)/360)          //Grad zu Radiant umwandeln*/
#define DIR_TO_DEG(x) ((x) * -90.0)               //Dir in Grad CW und float umwandeln

/*Definitionen die mit Argumenten geaendert werden koennen*/
/*Standardwerte werden in argument_handler() in LaserChess.c gesetzt.*/
//int FIELD_SIZE;

//Groesse
typedef struct {
	int Width;
	int Height;
} size;

/*Image ID's*/
int Blue_king_img;
int Blue_mirror_img;
int Blue_splitter_img;
int Blue_wall_img;
int Blue_cannon_img;
int Red_king_img;
int Red_mirror_img;
int Red_splitter_img;
int Red_wall_img;
int Red_cannon_img;
int Fig_error_img;
int Rot_focus_img;

/*Prototypen*/
location pixel_to_map(location Mapkoordinaten);
location map_to_pixel(location Windowskoordinaten);
void draw_playground();
void draw_focus(location Field);
void draw_rot_focus(location Field);
void draw_empty_field(location pos);
void draw_laser (location pos, enum Direction dir);
void draw_angled_laser(location pos, enum Direction dir, enum Angle angle);
void destroy_images();
int init_images();
void draw_figure(pawn *figure);
void draw_figure_destroyed(pawn *figure);
void draw_invert_colors(int x, int y, int width, int height);
void draw_winner_text(pawn *figure);
char *path_handler(const char path[], char file[]);

#endif
