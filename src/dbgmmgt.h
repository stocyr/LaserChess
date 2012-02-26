#ifndef DEBUG_MMGT_H
#define DEBUG_MMGT_H
/*****************************************************************************/
/*  Header     : DebugMemorymanagement                          Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : This module capsulates the systemmemorymanagement and       */
/*               catches errors in the memorymanagement of the user          */
/*               (Unallocated blocks, Memory leaks, overwritten blocks,      */
/*                wrongly freed blocks and more)                             */
/*                                                                           */
/*      ***                                                                  */
/*      ***                                                                  */
/*      ***      ATTENTION: Any modul wanting to use this module must        */
/*      ***                 include the header dbgmmgt.h AFTER all system    */
/*       *                  headers, otherwise it will not work !!!!!        */
/*                                                                           */
/*      ***                                                                  */
/*      ***                                                                  */
/*                                                                           */
/*  Procedures : MyMalloc                 Allocates a Block of Memory        */
/*               MyFree                   Frees a Block of Memory            */
/*               PrintMemoryStatistics    Gives infos about the current      */
/*                                        state of the memorymanagement      */
/*                                                                           */
/*               Attention, the header dbgmmgt will rereoute free and        */
/*               malloc to these functions, do not call them directly        */
/*               use malloc and free as usual and include dbgmmgt.h          */
/*               in your project                                             */
/*                                                                           */
/*  Author     : I. Oesch                                                    */
/*                                                                           */
/*  History    : 04.02.1997  IO  Created                                     */
/*               28.03.2004  IO  Modified for usage in C                     */
/*                                                                           */
/*  File       : dbgmmgt.h                                                   */
/*                                                                           */
/*****************************************************************************/
/* MagicSoft                                                                 */
/*****************************************************************************/

/* the following define must be enabled to activate the debug memorymanagement */
/* may also be defined in compileroptions */
/* #define USE_DEBUG_MEMORYMANAGEMENT  */ 
#ifdef USE_DEBUG_MEMORYMANAGEMENT

/* imports */
#include <stdlib.h>

/* module constant declaration  */


/* Just redirect calls to memory allocation functions */
/* to our special memory management                   */

/* !!! This file must be included after stdlib !!!    */

/* ATTENTION calloc and realloc are not redirected, if You use  */
/*           those in Your application You must also            */
/*           write a debugversion of those functions            */


#define malloc(x) MyMalloc(x, __FILE__, __LINE__)
#define free(x)   MyFree(x, __FILE__, __LINE__)
#define calloc(x, y) __Calloc_Not_Availlable_IN_Debug_MMGT(x, y)
#define realloc(x, y) __Realloc_Not_Availlable_IN_Debug_MMGT(x, y)

/* Prototypes of our new memorymanagement functions    */
#ifdef __cplusplus
extern "C" {
#endif
extern void *MyMalloc(size_t Size, char *Name, int LineNumber);
extern void MyFree(void *Block, char *Name, int LineNumber);
extern void PrintMemoryStatistics(void); 

/* some usefull helper functions */
extern long GetBlocksInUse(void);
extern long GetMaxBlocksInUse(void);
extern long GetUsedMemory (void);
extern long GetMaxUsedMemory (void);
extern long GetLowestFreeMem (void);

#ifdef __cplusplus
}
#endif

#else
/* disable all statisticfunctions */
#define PrintMemoryStatistics() 
#define GetBlocksInUse()           0
#define GetMaxBlocksInUse()        0
#define GetUsedMemory ()           0
#define GetMaxUsedMemory ()        0
#define GetLowestFreeMem ()        0

#endif
#endif


