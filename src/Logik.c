/*****************************************************************************/
/*	o o o o      Berner Fachhochschule										 */
/*		  :...o  Technik und Informatik										 */
/*****************************************************************************/
/*  Module     : LaserChess/Logik                               Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   :                                                             */
/*                                                                           */
/*  Procedures : laser()  spiel()  some other helper tools                   */
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


#include <stdio.h>
#include <stdlib.h>

#include "Grafik.h"


/*****************************************************************************/
/*  Function   : laser                                          Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   :                                                             */
/*                                                                           */
/*  Input Para :                                                             */
/*                                                                           */
/*  Output     : if a wall was hit: 0. If a king was hit: -1 for player_red, */
/*               -2 for player_blue. If a mirror was hit: +1 for player_red, */
/*               +2 for player_blue                                          */
/*                                                                           */
/*  Author     : C. Stoller                                                  */
/*                                                                           */
/*  Email      : stolc2@bfh.ch                                               */
/*                                                                           */
/*****************************************************************************/

int laser(enum location pos, enum Direction dir)
{
    enum location next_pos = pos;
    
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
    
    
    if(!is_inside_map(next_pos))
    {
        // wenn nicht mehr im spielfeld, in eine wand gefahren. -> return 0
        return 0;
    }
    else
    {
        pawn *next_pawn = map[next_pos.x][next_pos.y]
    
        if(next_pawn == NULL)
        {
            int return_value;
            // wenn ein leeres Feld, linie zeichnen
            return_value = laser(next_pos, dir);
            // linie wieder auslöschen
            return return_value;
        }
        else
        {
            // wenn eine Figur: was für eine?
            switch(next_pawn->TYPE)
            {
                case KING:
                    // König getroffen: Player negativ zurückgeben
                    return -(next_pawn->PLAYER)
                    break;
                
                case MIRROR:
                    // Spiegel getroffen: reflektion?
                    
                    // Reflektion berechnen, dir ändern
                    int return_value;
                    // gewinkelte linie zeichnen
                    return_value = laser(next_pos, dir);
                    // linie wieder auslöschen
                    return return_value;
                    
                    // wenn keine reflektion: Spiegel positiv zurückgeben
                    return next_pawn->PLAYER
                    break;
            }
        }
    }
}