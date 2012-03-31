#ifndef ERROR_H
#define ERROR_H
/*****************************************************************************/
/*  Header     : ErrorHandler                                   Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : This Module provides some mocros and functionality for      */
/*               errorhandling                                               */
/*                                                                           */
/*  Macros     : CODING_ERROR()         Displays given Errormessage and      */
/*                                      further information, halts program   */
/*               REJECT_NULLPOINTER()   Displays Errormessage if given       */
/*                                      pointer is a NULL pointer            */
/*               RUNTIME_ERROR()        Displays given Errormessage and      */
/*                                      further information, exits program   */
/*                                      if errorlevel is fatal               */
/*               ASSURE_MEMORY_AVAILLABLE()  Displays out of memory if given */
/*                                      pointer is a NULL pointer            */
/*                                                                           */
/*  Author     : I. Oesch                                                    */
/*                                                                           */
/*  History    : 09.04.2002  IO Created                                      */
/*               28.03.2004  IO Added cpp compatibility in header            */
/*                                                                           */
/*  File       : error.h                                                     */
/*                                                                           */
/*****************************************************************************/
/* MagicSoft                                                                 */
/*****************************************************************************/



/* imports */

/* module constant declaration  */
#define ERR_FATAL     3
#define ERR_NON_FATAL 2
#define ERR_WARNING   1

/* 199409L signifies the 1989 C standard                 */
/* 199901L signifies the 1999 revision of the C standard */
#if __STDC_VERSION__ > 199901L
#define CURRENT_FUNC_NAME __func__
#else
#ifdef __GNUC__
#define CURRENT_FUNC_NAME __FUNCTION__
#else
#define CURRENT_FUNC_NAME "unknown"
#endif
#endif

/* module macro declaration  */
#define CODING_ERROR(x) ErrorHandler((x), __FILE__, __LINE__, CURRENT_FUNC_NAME, ERR_FATAL)
#define RUNTIME_ERROR(x, L) ErrorHandler((x), __FILE__, __LINE__, CURRENT_FUNC_NAME, (L))
#define REJECT_NULLPOINTER(p) {if (p == 0) { CODING_ERROR("Nullpointer"); }}
#define ASSURE_MEMORY_AVAILLABLE(p) {if (p == 0) { CODING_ERROR("Out of memory"); }}

/* module type declaration      */

/* module data declaration      */

/* module procedure declaration */
#ifdef __cplusplus
extern "C" {
#endif

extern void ErrorHandler(char *Message, const char *FileName, int LineNumber, const char *FunctionName, int Level);

#ifdef __cplusplus
}
#endif

/*****************************************************************************/
/*  End Header  : ErrorHandler                                               */
/*****************************************************************************/
#endif

