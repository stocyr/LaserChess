#ifndef COMMUNICATION_H
#define COMMUNICATION_H
/*****************************************************************************/
/*  Header     : Communication                                  Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : This module manages the Networkcommunication                */
/*                                                                           */
/*  Procedures : InitializeCommunication  Initialize the communication       */
/*               ShutdownCommunication    Shutdown the communication         */
/*               CreateTelegram           Creates an empty message           */
/*               DeleteTelegram           Deletes a Message                  */
/*               SendTelegramTo           Sends a Message to a host          */
/*               CheckForTelegram         Reveives any Messages              */
/*               FindServer               Finds server by broadcast          */
/*               ConnectTo                Connects to a host as Slave        */
/*               IsConnected              Checks if handle is connected      */
/*               Disconnect               Disconnects from host              */
/*               AcceptConnection         Accept connections as master, is   */
/*                                        bfferoverflow protected            */
/*                                                                           */
/*  Author     : I. Oesch                                                    */
/*                                                                           */
/*  History    : 04.04.2002  IO Created                                      */
/*               28.03.2004  IO Converted AcceptConnection() to              */
/*                              SecureAcceptConnection, does no longer       */
/*                              copy a fixed amount of characters with       */
/*                              strncpy, uses now a parameter                */
/*                              Corrected sleep() to Sleep() and included    */
/*                              windows.h                                    */
/*                              Corrected some Spellingerrors in errortexts  */
/*                              Added cpp compatibility in header            */
/*                                                                           */
/*               28.04.2004  IO Added support for arbitrary Telegrammlengths */
/*                              (MaxTelegramLength)                          */
/*                                                                           */
/*               22.10.2009  IO Ported to QT                                 */
/*                              Added support to find servers by broadcast   */
/*                              InitializeCommunication() now returns        */
/*                              pointer to array of local IP adresses        */
/*                                                                           */
/*  File       : communication.h                                             */
/*                                                                           */
/*****************************************************************************/
/* MagicSoft                                                                 */
/*****************************************************************************/

/* imports */

/* module constant declaration  */

/* Command for telegramms */
enum CommandEnum {
   CMD_NONE                  = 0,
   CMD_KEYSTROKE             = 1,
   CMD_SET_FIELD             = 2,
   CMD_INIT_FIELD            = 3,
   CMD_SHOW_MESSAGE          = 4,
   CMD_SHOW_STATUS           = 5,
   CMD_USER_DATA             = 9,
   CMD_DRAW_EMPTY_CIRCLE     = 10,
   CMD_DRAW_FILLED_CIRCLE    = 11,
   CMD_DRAW_EMPTY_RECTANGLE  = 12,
   CMD_DRAW_FILLED_RECTANGLE = 13,
   CMD_DRAW_PIXEL            = 14,
   CMD_DRAW_LINE             = 15,
   CMD_DRAW_TEXT             = 16,
   CMD_DRAW_SET_FONT         = 17,
   CMD_DRAW_CLEAR_ALL        = 18
};

/* module type declaration      */

/* Info for Colorvalues */
typedef struct NetColorType {
   unsigned char Red;
   unsigned char Green;
   unsigned char Blue;
   unsigned char Alpha;
} NetColorType;

/* Info for draw circle command (CMD_DRAW_EMPTY_CIRCLE CMD_DRAW_FILLED_CIRCLE) */
typedef struct DrawCircleData {
   int x;              /* x-Position des Kreises */
   int y;              /* y-Position des Kreises */
   int Width;          /* Breite des 'Kreises'      */
   int Height;         /* Hoehe des 'Kreises'      */
   NetColorType Color; /* Farbe des Kreises        */
} DrawCircleData;

/* Info for draw rectangle command (CMD_DRAW_EMPTY_RECTANGLE CMD_DRAW_FILLED_RECTANGLE) */
typedef struct DrawRectangleData {
   int x;              /* x-Position des Rechtecks */
   int y;              /* y-Position des Rechtecks */
   int Width;          /* Breite des Rechtecks */
   int Height;         /* Hoehe des Rechtecks */
   NetColorType Color; /* Farbe des Rechtecks */
} DrawRectangleData;

/* Info for draw line command (CMD_DRAW_LINE) */
typedef struct DrawLineData {
   int x1;              /* Start-Position der Linie */
   int y1;              /* Start-Position der Linie */
   int x2;              /* End-Position der Linie */
   int y2;              /* End-Position der Linie */
   NetColorType Color;  /* Farbe der Linie */
   int Width;           /* Breite der Linie */
} DrawLineData;

/* Info for draw pixel command (CMD_DRAW_PIXEL) */
typedef struct DrawPixelData {
   int x;              /* x-Position des Pixels */
   int y;              /* y-Position des Pixels */
   NetColorType Color; /* Farbe des Kreises        */
} DrawPixelData;

/* Info for draw text command (CMD_DRAW_TEXT) */
typedef struct DrawTextData {
   int x;               /* Position des Textes */
   int y;               /* Position des Textes */
   NetColorType Color; /* Farbe des Rechtecks */
   unsigned int  Length; /* Länge des Textes in Bytes */
   char Text[1];        /* Längenvariables Textarray mit Text (Nullterminiert) */
} DrawTextData ;

/* Info for setfield (CMD_SET_FIELD) command */
typedef struct SetFieldData {
   unsigned int x;
   unsigned int y;
   unsigned int Color;
} SetFieldData;

/* Info for initfield (CMD_INIT_FIELD) command */
typedef struct InitFieldData {
   unsigned int Width;
   unsigned int Height;
} InitFieldData;

/* Info for showmessage (CMD_SHOW_MESSAGE) command */
typedef struct ShowMessageData {
   unsigned int  Length;
   char Text[1];
} ShowMessageData;

/* Info for showstatus (CMD_SHOW_STATUS) command */
typedef struct ShowStatusData {
   unsigned int  Line;
   unsigned int  Color;
   unsigned int  Length;
   char Text[1];
} ShowStatusData;

/* Info for free userdatas (CMD_USER_DATA) not command related*/
typedef struct UserData {
   unsigned int  Length;
   char          Data[1];
} UserData;

/* Unify all Infos */
typedef union MessageData {
   int               KeyCode;
   SetFieldData      SetField;
   InitFieldData     InitField;
   ShowMessageData   ShowMessage;
   ShowStatusData    ShowStatus;
   DrawCircleData    DrawCircle;
   DrawRectangleData DrawRectangle;
   DrawLineData      DrawLine;
   DrawTextData      DrawText;
   UserData          User;
} MessageData;


/* Messagestructure for telegramms */
typedef struct MessageType {
   enum CommandEnum Command;
   MessageData      Data;
} MessageType;

typedef struct ServerInfoType {
   char IPAddress[20];
   char Name[100];
} ServerInfoType;

/* module data declaration      */

/* module procedure declaration */

/* For compatibility (Old Versions did not allow to define a port)*/
#define InitializeCommunication(IP, TL) InitializeCommunicationWithPort(IP, TL, 0, 0)


#ifdef __cplusplus
extern "C" {
#endif
extern char ** InitializeCommunicationWithPort(char *MyIpAddress, unsigned int MaximumTelegramLength, unsigned int NewLocalPort, unsigned int NewRemotePort);
extern void ShutdownCommunication(void);
extern MessageType *CreateTelegram(unsigned int  AdditionalLength);
extern void DeleteTelegram(MessageType *Message);
extern void SendTelegramTo(int Handle, MessageType *Message);
extern MessageType *CheckForTelegram(int *Handle);
extern ServerInfoType *FindServer(unsigned int Timeout);
extern int  ConnectTo(char *Address, char *MyName, unsigned int Timeout);
extern int  IsConnected(int Handle);
extern void Disconnect(int Handle);
extern int  AcceptConnection(char *NameOfConnector, int MaxLength, char *MyName);
#ifdef __cplusplus
}
#endif

/*****************************************************************************/
/*  End Header  : Communication                                              */
/*****************************************************************************/
#endif

