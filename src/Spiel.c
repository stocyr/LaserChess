/*****************************************************************************/
/*	o o o o      Berner Fachhochschule										 */
/*		  :...o  Technik und Informatik										 */
/*****************************************************************************/
/*  Module     : Spiel                                          Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : Steuert den Spielverlauf                                    */
/*                                                                           */
/*  Procedures : spiel()                                                     */
/*                                                                           */
/*  Author     : M. Bärtschi 												 */
/* 																			 */
/*  Email	   : bartm9@bfh.ch  						                     */
/*                                                                           */
/*  History    : 21.03.2012  File created                                    */
/*                                                                           */
/*  File       : Spiel.c                                                     */
/*                                                                           */
/*****************************************************************************/
/*  n00bSoft                                                                 */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "Grafik.h"
#include "window.h"
#include "LaserChess.h"
#include "Logik.h"


void spiel(void)
{
	enum Affiliation PLAYER = PLAYER_RED;

	switch (PLAYER)
	{
	case PLAYER_RED:

		PLAYER = PLAYER_BLUE;
		break;
	case PLAYER_BLUE:

		PLAYER = PLAYER_RED;
		break;
	}
}
