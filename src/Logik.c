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
#include "Logik.h"
#include "LaserChess.h"


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

int laser(location pos, enum Direction dir)
{
    location next_pos = pos;

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
        pawn *next_pawn = map[next_pos.x][next_pos.y];
        int return_value, reflection;

        if(next_pawn == NULL)
        {
            // Leeres Feld: Linie zeichnen, sich selbst ausführen, linie wieder löschen
            draw_laser(next_pos, dir);
            return_value = laser(next_pos, dir);
            draw_empty_field(next_pos);
            return return_value;
        }
        else
        {
            // wenn eine Figur: was für eine?
            switch(next_pawn->TYPE)
            {
                case KING:
                    // König getroffen: Player negativ zurückgeben
                    draw_king_destroyed(next_pawn);
                    // SLEEP ca 2sek!
                    Sleep(2); // -> aus Ivos library?
                    return -(next_pawn->PLAYER);
                    break;

                case MIRROR:
                    // Spiegel getroffen: reflektion?
                    reflection = dir - next_pawn->DIR;
                    NORM(reflection);

                    switch(reflection)
                    {
                        case 0:
                        case 1:
                            // zerstörung: Spiegel positiv zurückgeben
                            draw_mirror_destroyed(next_pawn);
                            // SLEEP ca 2sek!
                            Sleep(2); // -> aus Ivos library?
                            return next_pawn->PLAYER;
                            break;

                        case 2:
                            // Reflektion um 90° nach rechts (CW)
                            ROTATE_RIGHT(dir);
                            // Linie zeichnen, angle = -1 (CW)
                            draw_angled_laser(next_pos, dir, -1);

                            // sich selbst ausführen und danach linie wieder löschen
                            return_value = laser(next_pos, dir);
                            draw_figure(next_pawn);
                            return return_value;
                            break;

                        case 3:
                            // Reflektion um 90° nach links (CCW)
                            ROTATE_LEFT(dir);
                            // Linie zeichnen, angle = +1 (CCW)
                            draw_angled_laser(next_pos, dir, 1);

                            // sich selbst ausführen und danach linie wieder löschen
                            return_value = laser(next_pos, dir);
                            draw_empty_field(next_pos);
                            draw_figure(next_pawn);
                            return return_value;
                            break;
                    }
            }
        }
    }

    return 0;
}
