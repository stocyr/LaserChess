#ifndef GRAFIK_H
#define GRAFIK_H
/*****************************************************************************/
/*  o o o o      Berner Fachhochschule                                       */
/*        :...o  Technik und Informatik                                      */
/*****************************************************************************/
/*  Header     : LaserChess/Grafik                              Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Desc       : Header for graphics functions                               */
/*                                                                           */
/*  Procedures :                                                             */
/*                                                                           */
/*  Author     : J. Haldemann; N. Kaeser                                     */
/*                                                                           */
/*  Email      : haldj3@bfh.ch; kasen1@bfh.ch                                */
/*                                                                           */
/*  Creation   : xx.03.2012                                                  */
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

/*Rotations Definitionen*/
/*#define PI 3.14159265358979323846             //Kopiert aus math.h
#define RAD_TO_DEG(x) ((x) * 360/(2*PI))        //Radiant zu Grad umwandeln
#define DEG_TO_RAD(x) ((x) * (2*PI)/360)*/      //Grad zu Radiant umwandeln
#define DIR_TO_DEG(x) ((x) * -90.0)             //Dir in Grad CW und float umwandeln

/*Grundsätzliche Grafik Definitionen*/
#define FIELD_SIZE 100                          //Feldbreite in Pixel
#define PERCENT_FIELD_SIZE (FIELD_SIZE/10000.0) //Feldbreite in Prozent (.0, damit als float interpretiert)
#define PLAYGROUND_X_MAX 8                      //Anzahl Felder - Breite
#define PLAYGROUND_Y_MAX 6                      //Anzahl Felder - Höhe
#define PLAYGROUND_COL COL_BLACK                //Spielfeldfarbe
#define LINE_COL COL_GREY                       //Linienfarbe
#define FIELD_LINE_WIDTH 3                      //Breite der Spielfeldlinien in Pixel
#define FOCUS_COL COL_GREEN                     //Fokusfarbe
#define FOCUS_IDENT 3                           //Einzurückende Pixel der Focusfunktion
#define LASER_COL COL_GREEN                     //Laserfarbe
#define LASER_SPEED 100                         //Geschwindigkeit beim Zeichnen des Lasers in ms
#define DESTROY_SPEED 200                       //Zeit zwischen den Schritte der Zerstoerungsanimation in ms
#define IMG_DIR "\\img\\figures"                //Ordnerpfad zu den Grafiken der Figuren (Pfad relativ zu *ApplicationPath)

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
int Figure_error_img;

/*Prototypen*/
location pixel_to_map(location Mapkoordinaten);
location map_to_pixel(location Windowskoordinaten);
void draw_playground();
void draw_focus(location Field);
void draw_empty_field(location pos);
void draw_laser (location pos, enum Direction dir);
void draw_angled_laser(location pos, enum Direction dir, enum Angle angle);
char init_figure_images();
void destroy_figure_images();
void draw_figure(pawn *figure);
void draw_mirror_destroyed(pawn *figure);
void draw_king_destroyed(pawn *figure);

/*module type declaration*/

/*module data declaration*/

/*module procedure declaration*/

/*ALLE PROTOTYPEN DER GRAFIKFUNKTIONEN*/

/*****************************************************************************/
/*  End Header  : ErrorHandler                                               */
/*****************************************************************************/
#endif

