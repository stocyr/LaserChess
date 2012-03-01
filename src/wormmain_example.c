/* general control */

/*****************************************************************************/
/*  Module     : Mainmodule                                     Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : This is a short dmeo for the usage of the graphics module   */
/*                                                                           */
/*  Procedures : main   Mainprocedure for the demo                           */
/*                                                                           */
/*  Author     : I. Oesch                                                    */
/*                                                                           */
/*  History    : 03.05.2002  IO Created                                      */
/*                                                                           */
/*  File       : wormmain.c                                                  */
/*                                                                           */
/*****************************************************************************/
/* MagicSoft                                                                 */
/*****************************************************************************/

/* imports */
#include "error.h"
#include "window.h"
#include "communication.h"
//#include "ConsoleFunctions.h"


#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

/* module constant declaration */
#define PI 3.1416

/* module type declaration */
typedef struct ImageMap {
   int Height;
   int Width;
   int MapSizeInBytes;
   ColorType *BasePtr;
   ColorType **ImageMap;
} ImageMapType;


/* module data declaration */

/* module procedure declaration */
void DrawTransformedImage(int x, int y, float Angle, float ScaleX, float ScaleY, int Image);
ImageMapType *CreateImageMap(int MyImage);
void DestroyImageMap(ImageMapType * ImageMap);



/*****************************************************************************/
/*  Procedure   : main                                                       */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Just a short demonstration for the usage of the graphic    */
/*                module                                                     */
/*                                                                           */
/*  Type        : Global                                                     */
/*                                                                           */
/*  Input Para  : argc           Number of commandline arguments from system */
/*                argv           Vectro with commandline arguments           */
/*                                                                           */
/*  Output Para : Errorcode to system, 0 on no error                         */
/*                                                                           */
/*  Author      : I. Oesch                                                   */
/*                                                                           */
/*  History     : 02.04.2002  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
int gfxmain(int argc, char* argv[], const char *ApplicationPath)
{
   /* procedure data */
   int x = 0;
   ColorType Col;
   ColorType ColBlack;
   ColorType ColRed;
   ColorType ColGreen;
   ColorType ColYellow;
   ColorType TempCol;

   TextDimensionType TextExtension;

   int LoadedImage;
   int MyImage;
   int SavedImage;
   int LastX, LastY;
   int Key;
   float ColorAngle = 0;

   /* procedure code */


   /* Set the color information */
   Col.Red   = 0xff;
   Col.Green = 0;
   Col.Blue  = 0;
   Col.Alpha = 0xff;

   ColRed.Red   = 0xff;
   ColRed.Green = 0;
   ColRed.Blue  = 0;
   ColRed.Alpha = 0xff;

   ColGreen.Red   = 0;
   ColGreen.Green = 0xff;
   ColGreen.Blue  = 0;
   ColGreen.Alpha = 0xff;

   ColYellow.Red   = 0xff;
   ColYellow.Green = 0xff;
   ColYellow.Blue  = 0;
   ColYellow.Alpha = 0xff;

   ColBlack.Red   = 0;
   ColBlack.Green = 0;
   ColBlack.Blue  = 0;
   ColBlack.Alpha = 0xff;

   // Just print the applicationpath for demonstration
   printf("ApplicationPath: %s\n", ApplicationPath);

   {
      int i = 0;
      for (i = 0; i < argc; i++) {
         printf("%d: >%s<\n", i, argv[i]);
      }
   }

   /* initialize and open the graphic window */
   InitGraphic(600, 400);
   //InitGraphic(-1, -1);  /* Negative Values gives full-screen window */

   /* Fill the whole area with grey */
   DrawFilledRectangle(0, 0, 600, 400, COL_GREY, 1) ;

   TempCol = GetPixel(110,110);
   printf("\n Color: <%d:%d:%d:%d>\n", TempCol.Red, TempCol.Green, TempCol.Blue, TempCol.Alpha);

   /* Draw a filled circle */
   DrawFilledCircle(90, 90, 40, 40, Col, 1);

   /* Get a pixel and print its color value */
   TempCol = GetPixel(110,110);
   printf("\n Color: <%d:%d:%d:%d>\n", TempCol.Red, TempCol.Green, TempCol.Blue, TempCol.Alpha);

   /* define a new color */
   Col.Red   = 0;
   Col.Green = 0xff;
   Col.Blue  = 0;

   /* Draw a filled rectangle */
   DrawFilledRectangle(70, 250, 60, 60, Col, 1) ;

   /* define a new color */
   Col.Red   = 0;
   Col.Green = 0;
   Col.Blue  = 0xFF;

   /* Draw a line */
   DrawLine(6, 6, 97, 34, Col, 2);

   /* Draw some text in selected font */
   SelectFont("Comic Sans MS", 12, FONT_NORMAL);
   DrawTextXY (30, 300, Col, "Just a Demo");

   /* define a new color */
   Col.Red   = 0;
   Col.Green = 0;
   Col.Blue  = 0xFF;

   /* Draw some text in selected font */
   SelectFont("Times", 8, FONT_NORMAL);
   DrawTextXY (200, 225, Col, "Blue@@");

   /* define a new color */
   Col.Red   = 0;
   Col.Green = 0xF0;
   Col.Blue  = 0;

   /* Draw some text in selected font, only change font attributes */
   SelectFont(NULL, 30, FONT_NORMAL);
   DrawTextXY (200, 250, Col, "Green@@");

   /* define a new color */
   Col.Red   = 0xf0;
   Col.Green = 0;
   Col.Blue  = 0;

   /* Draw some text in selected font, only change font attributes */
   SelectFont(NULL, 20, FONT_ITALIC);
   DrawTextXY (200, 275, Col, "Red@@");

   /* define a new color */
   Col.Red   = 0xf0;
   Col.Green = 0xf0;
   Col.Blue  = 0;

   /* Draw some text in selected font, only change font attributes */
   SelectFont(NULL, 12, FONT_BOLD);
   DrawTextXY (200, 300, Col, "Yellow@@");

   /* define a new color */
   Col.Red   = 0x0;
   Col.Green = 0xf0;
   Col.Blue  = 0xf0;

   /* Draw some text in selected font, only change font attributes */
   SelectFont(NULL, 12, FONT_NORMAL);

   /* Draw an orange backgroundrectangle for the text */
   TextExtension = GetTextDimensions("Cyan@@");
   DrawFilledRectangle(200 - TextExtension.Overhang, 325 - TextExtension.Up, TextExtension.Length + TextExtension.Overhang, TextExtension.Up + TextExtension.Down, COL_ORANGE, 1) ;
   DrawTextXY (200, 325, Col, "Cyan@@");

   /* Create a Image */
   MyImage = CreateImage(40, 60);

   /* Select this image for future Drawing */
   SetEditedImage(MyImage);

   /* Make a nice drawing... */
   /* Overwrite existing pixels with source pixels, inclusive alpha channel */
   SetDrawMode(DM_COPY);
   DrawFilledRectangle(0, 0, 40, 60, COL_BLACK, 1);
   DrawFilledRectangle(0, 0, 40, 60, COL_TRANSPARENT, 1) ;

   /* Respect transparency (Alpha channel) of source when drawing */
   SetDrawMode(DM_OVER);
   DrawLine(5, 10, 20, 15, Col, 2);
   DrawLine(35, 10, 20, 15, Col, 2);
   DrawEmptyCircle(15, 0, 10, 10, Col, 2);
   DrawLine(20, 10, 20, 30, Col, 2);
   DrawLine(5, 58,  20, 30, Col, 2);
   DrawLine(35, 58, 20, 30, Col, 2);


   /* Direct pixel access */
   {
      /* Get a pointer to the graphics data */
      ColorType *ImagePtr = GetPixelDataPointer(MyImage, NULL);
      int Height, Width;
      GetImageSize(MyImage, &Width, &Height);
      if (ImagePtr != NULL) {
         /* print some infos */
         printf("Image: %d, %d\n", Width, Height);
         printf("Image: %x \n", ((unsigned int *)ImagePtr)[0]);

         /* directly write into graphics array */
         ImagePtr[20 * Width + 5] = COL_ORANGE;
         ImagePtr[21 * Width + 6] = COL_ORANGE;
         ImagePtr[22 * Width + 7] = COL_ORANGE;
         ImagePtr[23 * Width + 8] = COL_ORANGE;
         ImagePtr[24 * Width + 9] = COL_ORANGE;
         ImagePtr[25 * Width + 10] = COL_ORANGE;

         /* Use ImageMap for simpler access */
         ImageMapType * ImageMap = CreateImageMap(MyImage);
         printf("ImageSize %d (%d Pixel)\n", ImageMap->MapSizeInBytes, ImageMap->MapSizeInBytes/4);

         if (ImageMap != NULL) {
            /* draw two horizontal lines */
            int x, y;
            y = 5;
            for (x = 5; x < ImageMap->Width-5; x++) {
               ImageMap->ImageMap[y][x] = COL_YELLOW;
            }
            y = ImageMap->Height-5;
            for (x = 5; x < ImageMap->Width-5; x++) {
               ImageMap->ImageMap[y][x] = COL_YELLOW;
            }
            DestroyImageMap(ImageMap);
         }
      }
   }


   /* Select main screen for future Drawing */
   SetEditedImage(ID_WINDOW);

   /* Draw our drawing onto screen at different positions */
   DrawImage(MyImage, 100, 100);
   DrawImage(MyImage, 200, 100);
   DrawImage(MyImage, 400, 200);

   /* Create a backup for moving image (Copy a part of main image into SavedImage)*/
   LastX = 0;
   LastY = 0;
   SavedImage = CreateSubImage(ID_WINDOW, LastX, LastY, 40, 60);

   /* do until user hits a key */
   while(!IsKeyPressReady()) {

      MouseInfoType MouseInfo;

      /* wait some time */
      WaitMs(20);

      SetAutoUpdate(0);
      /* delete the old rectangle (Draw it black) */
      DrawFilledRectangle(x+5, 50, 60, 60, ColBlack, 1) ;

      /* move the rectangle position */
      x = x + 1;
      if (x > 200) {
         x = 0;
      }

      /* Change Colors periodically */
      Col.Red   = (0.5 + 0.5*sin(ColorAngle + (0.0*PI/3.0)))*255;
      Col.Green = (0.5 + 0.5*sin(ColorAngle + (2.0*PI/3.0)))*255;
      Col.Blue  = (0.5 + 0.5*sin(ColorAngle + (4.0*PI/3.0)))*255;

      ColorAngle += 0.1;
      if (ColorAngle > 2*PI) {
         ColorAngle -= 2*PI;
      }

      /* draw the rectangle at the new position */
      DrawFilledRectangle(x + 5, 50, 60, 60, Col, 1) ;

      /* Get MousePosition */
      MouseInfo = GetMouseState();


      /* Restore Image at last mouseposition (And so delete our image) */
      SetDrawMode(DM_COPY);
      DrawImage(SavedImage, LastX, LastY);

      /* Make a backup of image part at current mose position */
      CopyToImage(MouseInfo.MousePosX, MouseInfo.MousePosY, 40, 60, SavedImage);
      SetDrawMode(DM_OVER);

      /* And draw our Image at current mouseposition */
      DrawImage(MyImage, MouseInfo.MousePosX, MouseInfo.MousePosY);
      LastX = MouseInfo.MousePosX;
      LastY = MouseInfo.MousePosY;

      /* Actualice drawing on screen */
      SetAutoUpdate(1);
   }

   /* Clear Key inputbuffer */
   while(IsKeyPressReady()) {
      Key = GetKeyPress();
      if ((Key == W_KEY_CLOSE_WINDOW) || (Key == 'Q') || (Key == 'q') || (Key == 'X') || (Key == 'x')) {
         /* End our application */
         /* close the graphicwindow and cleanup */
         CloseGraphic();
         return 0;
      }
   }

   /********************* Image handling demo (Loading, scaling, rotating and drawing) **************************/

   /* Load an Image from the Filesystem (NULL = Open Dialog for Name)*/
   //LoadedImage = LoadImage(NULL);
   {
      // Load image from application directory
      char FileNameBuffer[1000];

      // Concatenate Applicationpath (Location of .exe) with image file name
      sprintf(FileNameBuffer, "%s\\TestImage.png", ApplicationPath);

      // and load the image
      LoadedImage = LoadImage(FileNameBuffer);
   }

   /* Make borderpixels transparent */
   AddAlphaMask(LoadedImage, MSK_AUTO, ColBlack) ;

   {
      float Angle = 0;
      float ScalingFactor = 1.0;
      float ScalingMultiplier = 0.98;

      int ImageWidth;
      int ImageHeight;

      /* Get dimensions of Image */
      GetImageSize(LoadedImage, &ImageWidth, &ImageHeight);

   /* do until user hits a key */
   while(!IsKeyPressReady()) {

      MouseInfoType MouseEvent;

      /* wait some time */
      WaitMs(50);

      /* Disable all transformation */
      ResetTransformations();

      SetAutoUpdate(0);

      /* Draw a litle circle at position of mouse-events */
      MouseEvent = GetMouseEvent();

      /* Color depends on mouse event */
      if (MouseEvent.ButtonState & W_BUTTON_PRESSED) {
         DrawFilledCircle(MouseEvent.MousePosX, MouseEvent.MousePosY, 10, 10, ColRed, 1);
      }
      if (MouseEvent.ButtonState & W_BUTTON_RELEASED) {
         DrawFilledCircle(MouseEvent.MousePosX, MouseEvent.MousePosY, 10, 10, ColGreen, 1);
      }
      if (MouseEvent.ButtonState & W_BUTTON_DOUBLECLICK) {
         DrawFilledCircle(MouseEvent.MousePosX, MouseEvent.MousePosY, 10, 10, ColYellow, 1);
      }

#if 1
      //DrawTransformedImage(ImageWidth/2, ImageHeight/2, Angle, ScalingFactor, ScalingFactor, LoadedImage);
      DrawTransformedImage(100, 10, Angle, ScalingFactor, ScalingFactor, LoadedImage);
#else

      /* Move coordinatesystem in the (assumed) centre of the immage */
      Translate(ImageWidth/2, ImageHeight/2);

      /* Scale and rotate the coordinatesystem */
      Scale(ScalingFactor, ScalingFactor);
      Rotate(Angle);

      /* Move coordinatesystem back to origin */
      Translate(-ImageWidth/2, -ImageHeight/2);

      /* draw the image into the transformated coordinatesystem */
      /* results in a rotated and scaled image                  */
      DrawImage(LoadedImage, 0, 0);
#endif
      SetAutoUpdate(1);

      /* Update scaling factor and rotation angle */
      Angle = Angle + 2;
      ScalingFactor = ScalingFactor*ScalingMultiplier;
      if (ScalingFactor < 0.05) {
         ScalingMultiplier = 1.02;
      }
      if (ScalingFactor > 1.3) {
         ScalingMultiplier = 0.98;
      }



   }
   }

   /* Clear Key inputbuffer */
   while(IsKeyPressReady()) {
      Key = GetKeyPress();
      printf("Got a %x keycode\n", Key);
      if ((Key == W_KEY_CLOSE_WINDOW) || (Key == 'Q') || (Key == 'q') || (Key == 'X') || (Key == 'x')) {
         /* End our application */
         /* close the graphicwindow and cleanup */
         CloseGraphic();
         return 0;
      }
   }

   SaveImage(ID_WINDOW, "d:\\Testqttimage.png", NULL, 0);
   //SaveImage(ID_WINDOW, NULL, NULL, 0);

   /***************** Throw things around demo (Mouse Event handling) *****************/

   {
      const int TimeIntervall = 20;
      float SpeedX = 0.05;
      float SpeedY = -0.05;
      float PosX   = 300;
      float PosY   = 200;
      float StartTime = 0;
      float StartPosX   = 0;
      float StartPosY   = 0;
      float Gravity = 0.001;
      char Sound1NameBuffer[1000];
      char Sound2NameBuffer[1000];

      int MaxHeight = 0;
      int MaxWidth = 0;
      GetImageSize(ID_WINDOW, &MaxWidth, &MaxHeight);
      printf("[%d:%d]", MaxWidth, MaxHeight);

      /* Disable all transformation */
      ResetTransformations();

      /* Fill the whole area with black */
      //DrawFilledRectangle(0, 0, 600, 400, ColBlack, 1) ;
      ClearWindow();

      /* Draw some information */
      DrawTextXY (50, 50, ColGreen, "Klick and drag with mouse to throw object");
      DrawTextXY (50, 70, ColGreen, "Doubleclick to toggle gravity");

      // Concatenate Applicationpath (Location of .exe) with sound file name
      sprintf(Sound1NameBuffer, "%s\\sound1.wav", ApplicationPath);
      sprintf(Sound2NameBuffer, "%s\\sound2.wav", ApplicationPath);

      /* Start background sound */
      PlaySoundContinuous(Sound1NameBuffer);
      //PlaySoundOnce(Sound1NameBuffer);

   /* do until user hits a key */
   while(!IsKeyPressReady()) {

      MouseInfoType MouseEvent;

      /* wait some time */
      WaitMs(TimeIntervall);
      StartTime += TimeIntervall;

      /* Undraw old object */
      SetAutoUpdate(0);
      DrawFilledCircle(PosX, PosY, 10, 10, ColBlack, 1);


      /* Actualice speed acording to gravity */
      SpeedY += Gravity * TimeIntervall;

      /* Move object according to its velocity */
      PosX   += SpeedX * TimeIntervall;
      PosY   += SpeedY * TimeIntervall;

      /* Check if we hit a border, revert speed if so (Creates bouncing-effect) */
      if ((PosX < 10) && (SpeedX < 0)) {
         SpeedX = -SpeedX;
         PlaySoundOnce(Sound2NameBuffer);
      }
      if ((PosY < 10) && (SpeedY < 0)) {
         SpeedY = -SpeedY;
         PlaySoundOnce(Sound2NameBuffer);
      }
      if ((PosX > MaxWidth-10) && (SpeedX > 0)) {
         SpeedX = -SpeedX;
         PlaySoundOnce(Sound2NameBuffer);
      }
      if ((PosY > MaxHeight-10) && (SpeedY > 0)) {
         SpeedY = -SpeedY;
         PlaySoundOnce(Sound2NameBuffer);
      }


      /* Do not draw immediately */
      SetAutoUpdate(0);

      /* Get and analyze mouse-events */
      MouseEvent = GetMouseEvent();

      /* Save startposition and time of mouse-drag */
      if (MouseEvent.ButtonState & W_BUTTON_PRESSED) {
         StartPosX   = MouseEvent.MousePosX;
         StartPosY   = MouseEvent.MousePosY;
         PosX   = MouseEvent.MousePosX;
         PosY   = MouseEvent.MousePosY;
         StartTime   = 0;
      }

      /* calculate speed of mousemove */
      if (MouseEvent.ButtonState & W_BUTTON_RELEASED) {
         PosX   = MouseEvent.MousePosX;
         PosY   = MouseEvent.MousePosY;
         SpeedX = (PosX - StartPosX) / StartTime;
         SpeedY = (PosY - StartPosY) / StartTime;
      }

      if (MouseEvent.ButtonState & W_BUTTON_DOUBLECLICK) {
         /* toggle gravity on doubleclick */
         if (Gravity > 0) {
            Gravity = 0.0;
         } else {
            Gravity = 0.002;
         }
      }


      /* Get MousePosition, draw object at mouselocation if any button is pressed */
      MouseEvent = GetMouseState();
      if (MouseEvent.ButtonState != W_BUTTON_NONE) {
         PosX   = MouseEvent.MousePosX;
         PosY   = MouseEvent.MousePosY;
      }

      /* Draw our object at the current position */
      DrawFilledCircle(PosX, PosY, 10, 10, ColRed, 1);
      SetAutoUpdate(1);

   }
   }
   /* Stop background sound */
   StopContinuousSound();

   /* Clear Key inputbuffer */
   while(IsKeyPressReady()) {
      Key = GetKeyPress();
      if ((Key == W_KEY_CLOSE_WINDOW) || (Key == 'Q') || (Key == 'q') || (Key == 'X') || (Key == 'x')) {
         /* End our application */
         /* close the graphicwindow and cleanup */
         CloseGraphic();
         return 0;
      }
   }
   {
      char Sound2NameBuffer[1000];
      // Concatenate Applicationpath (Location of .exe) with sound file name
      sprintf(Sound2NameBuffer, "%s\\sound1.wav", ApplicationPath);

      PlaySoundContinuous(Sound2NameBuffer);
   }
   /**************  Magnetic Mouse Demo *****************/

   {
      float SpeedX = 0.5;
      float SpeedY = 0.5;
      float PosX   = 300;
      float PosY   = 200;
      float AccelerationX  = 0.01;
      float AccelerationY  = 0.01;
      float AbsoluteValue = 0;

      /* Disable all transformation */
      ResetTransformations();

      /* Fill the whole area with black */
      DrawFilledRectangle(0, 0, 600, 400, ColBlack, 1) ;



   /* do until user hits a key */
   while(!IsKeyPressReady()) {

      MouseInfoType MouseEvent;
      float dx, dy;

      /* wait some time */
      WaitMs(20);

      /* Undraw old object */
      SetAutoUpdate(0);
      DrawFilledCircle(PosX, PosY, 10, 10, ColBlack, 1);


      /* Move object according to its velocity */
      PosX   += SpeedX * 20;
      PosY   += SpeedY * 20;
      SpeedX   += AccelerationX * 20;
      SpeedY   += AccelerationY * 20;
      SpeedX   *= 0.9;
      SpeedY   *= 0.9;


      SetAutoUpdate(0);

      MouseEvent = GetMouseEvent();

      if (MouseEvent.ButtonState & W_BUTTON_DOUBLECLICK) {
         /* Reset Things on doubleclick */
         SpeedX = 0.5;
         SpeedY = 0.5;
         PosX   = 300;
         PosY   = 200;
         AccelerationX  = 0.001;
         AccelerationY  = 0.001;

      }

      /* Get MousePosition */
      MouseEvent = GetMouseState();

         /* Let Acceleration point in our Direction */
         dx = MouseEvent.MousePosX - PosX;
         dy = MouseEvent.MousePosY - PosY;

         /* Make UnitVector */
         AbsoluteValue = dx*dx + dy*dy;
         AbsoluteValue = sqrt(AbsoluteValue);
         if (AbsoluteValue > 0.001) {
            AccelerationX = 0.01*dx/AbsoluteValue;
            AccelerationY = 0.01*dy/AbsoluteValue;
         }

      /* Draw our object at the current position */
      DrawFilledCircle(PosX, PosY, 10, 10, ColRed, 1);
      SetAutoUpdate(1);

   }
   }
   StopContinuousSound();

   /* Clear Key inputbuffer */
   while(IsKeyPressReady()) {
      Key = GetKeyPress();
      if ((Key == W_KEY_CLOSE_WINDOW) || (Key == 'Q') || (Key == 'q') || (Key == 'X') || (Key == 'x')) {
         /* End our application */
         /* close the graphicwindow and cleanup */
         CloseGraphic();
         return 0;
      }
   }

   /*************** Networking Demo (Clients show same drawings as server) *********************/

   {

      ServerInfoType *AvaillableServers = NULL;
      char     **IpAdresses;
      char     IPAddress[200];
      int      ServerFound = 0;
      int      i;
      int      LokalPort;
      int      RemotePort;

      if (Key == 'S') {
         LokalPort = 6666;
         RemotePort = 6667;
      } else if (Key == 'C') {
         LokalPort = 6667;
         RemotePort = 6666;
      } else {
         LokalPort = 0;
         RemotePort = 0;
      }

      printf("Using local port %d, remote port %d\n", LokalPort, RemotePort);

      /* Startup networking, get list of local IP-addresses */
      IpAdresses = InitializeCommunicationWithPort(IPAddress, 500, LokalPort, RemotePort);

      for (i = 0; IpAdresses[i] != NULL; i++) {
         printf("Lokal Address %2d: %s\n", i+1, IpAdresses[i]);
      }

      printf("\nLooking for server...");

      /* look for 10 seconds for servers */
      AvaillableServers = FindServer(10000);

      /* check if valid server found */
      if (AvaillableServers != NULL) {
         while(AvaillableServers->IPAddress[0] != '\0') {
            printf("Server <%s> at %s found\n", AvaillableServers->Name, AvaillableServers->IPAddress);
            if (strcmp(AvaillableServers->Name, "ICH") != 0) {
               ServerFound = 1;
               break;
            }
            AvaillableServers++;
         }
      }

      if (ServerFound != 0) {
         /* We found a server, so we will be a client */
         int Handle;

         /* Connecting to server */
         printf("\nFound servers, connecting...");
         Handle = ConnectTo(AvaillableServers->IPAddress, "DemoClient", 3000);

         while(!IsKeyPressReady()) {
            int Sender;

            /* Do not draw immediately */
            SetAutoUpdate(0);

            MessageType *T;

            /* procedure code */

            /* check for a telegram from server */
            T = CheckForTelegram(&Sender);

            /* If we got a telegram, analyze it */
            if (T != NULL) {
               if (T->Command == CMD_DRAW_FILLED_CIRCLE) {
                  /* if we got a draw-circle-telegram, extract circle drawing information */

                  Col.Red   = T->Data.DrawCircle.Color.Red;
                  Col.Blue  = T->Data.DrawCircle.Color.Blue;
                  Col.Green = T->Data.DrawCircle.Color.Green;

                  /* and draw the circle */
                  DrawFilledCircle(T->Data.DrawCircle.x,
                                   T->Data.DrawCircle.y,
                                   T->Data.DrawCircle.Width,
                                   T->Data.DrawCircle.Height, Col, 0);
               }
               /* free telegramm resources */
               DeleteTelegram(T);
            }
            /* update screen */
            SetAutoUpdate(1);
         }
      } else {
         /* There were no valid server, so we will act as server */
         char Buffer[200];
         int  Connections[30];
         int NumberOfConnections = 0;
         printf("\nFound no servers, acting as server...");
         while(!IsKeyPressReady()) {

               MouseInfoType MouseEvent;

               /* check for a connection */
               int Remote = AcceptConnection(Buffer, 200, "BasisProjectDemo");

               /* If we got a connection, add it to our list of clients */
               if ( Remote >= 0) {
                  /* we got a connection */
                  printf("\nConnected by %s", Buffer);
                  Connections[NumberOfConnections++] = Remote;
                  if (NumberOfConnections > 15) {
                     NumberOfConnections = 15;
                  }

               }

               /* Do not draw immediately */
               SetAutoUpdate(0);

               /* Get and analyze mouse-events */
               MouseEvent = GetMouseEvent();

               /* if mouse was clicked, we must draw a circle at clicked position  */
               if (MouseEvent.ButtonState & W_BUTTON_PRESSED) {
                  int i;
                  int PosX, PosY;

                  /* Get Click-position */
                  PosX   = MouseEvent.MousePosX;
                  PosY   = MouseEvent.MousePosY;

                  /* Draw circle at clicked position */
                  DrawFilledCircle(PosX, PosY, 20, 20, COL_ORANGE, 1);

                  /* actualize drawing on screen */
                  SetAutoUpdate(1);

                  /* Send drawcommand to all our clients */
                  for(i = 0; i < NumberOfConnections; i++) {
                     MessageType *T;
                     T = CreateTelegram(0);

                     T->Data.DrawCircle.x = PosX;
                     T->Data.DrawCircle.y = PosY;
                     T->Data.DrawCircle.Width  = 20;
                     T->Data.DrawCircle.Height = 20;
                     T->Data.DrawCircle.Color.Red   = COL_ORANGE.Red;
                     T->Data.DrawCircle.Color.Blue  = COL_ORANGE.Blue;
                     T->Data.DrawCircle.Color.Green = COL_ORANGE.Green;
                     T->Command = CMD_DRAW_FILLED_CIRCLE;
                     SendTelegramTo(Connections[i], T);
                  }
                  }
               }
         }
      }



   /* close the graphicwindow and cleanup */
   CloseGraphic();

   /* report 'no error' to the system */
   return 0;
}
/*****************************************************************************/
/*  End         : main                                                       */
/*****************************************************************************/


/*****************************************************************************/
/*  Procedure   : DrawTransformedImage                                       */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Draws the given Image skaled and rotated at the given      */
/*                position into the current image                            */
/*                                                                           */
/*  Type        : Global                                                     */
/*                                                                           */
/*  Input Para  : ImageId Handle of image to draw                            */
/*                x, y    Position to draw image at                          */
/*                Scalex  Scalingfactor for x axis (float value)             */
/*                Scaley  Scalingfactor for y axis (float value)             */
/*                Angle   Angle to rotate Image (in rad)                     */
/*                                                                           */
/*  Output Para : none                                                       */
/*                                                                           */
/*  Author      : I. Oesch                                                   */
/*                                                                           */
/*  History     : 06.01.2010  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
void DrawTransformedImage(int x, int y, float Angle, float ScaleX, float ScaleY, int Image)
{
   int ImageWidth;
   int ImageHeight;

   /* Get dimensions of Image */
   GetImageSize(Image, &ImageWidth, &ImageHeight);

   ResetTransformations();


   /* Move coordinatesystem in the (assumed) centre of the immage */
   Translate(x, y);

   /* Scale and rotate the coordinatesystem */
   Scale(ScaleX, ScaleY);

   Rotate(Angle);

   /* Move coordinatesystem back to origin */
   Translate(-ImageWidth/2.0, -ImageHeight/2.0);

   /* draw the image into the transformated coordinatesystem */
   /* results in a rotated and scaled image                  */
   DrawImage(Image, 0, 0);
   ResetTransformations();
}
/*****************************************************************************/
/*  End         : DrawTransformedImage                                       */
/*****************************************************************************/

/*****************************************************************************/
/*  Procedure   : CreateImageMap                                             */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Creates an imagemap for an image, this allows direct       */
/*                to the image in a matrix like form                         */
/*                                                                           */
/*                Access to imagedata (Attention y IS first):                */
/*                                                                           */
/*                ImageMap->ImageMap[y][x] = Color;                          */
/*                if (ImageMap->ImageMap[y][x] == Color) {}                  */
/*                                                                           */
/*  Type        : Global                                                     */
/*                                                                           */
/*  Input Para  : ImageId Handle of image to create imagemap for             */
/*                                                                           */
/*  Output Para : Pointer to the ImageMap for the image, or NULL if failed.  */
/*                Must be deposed mit DestroyImageMap if no longer used      */
/*                                                                           */
/*  Author      : I. Oesch                                                   */
/*                                                                           */
/*  History     : 16.11.2011  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
ImageMapType *CreateImageMap(int MyImage)
{
   ImageMapType *ImageMapPtr = NULL;
   int ImageMapSize;
   int i;

   /* Get a pointer to the graphics data */
   ColorType *ImagePtr = GetPixelDataPointer(MyImage, &ImageMapSize);

   /* Get Imagesize */
   int Height = 0, Width = 0;
   GetImageSize(MyImage, &Width, &Height);

   /* Check for valid image */
   if (ImagePtr != NULL) {

      /* Allocate image info structure  */
      ImageMapPtr = malloc(sizeof(ImageMapType));
      if (ImageMapPtr != NULL) {

         /* Allocate Rowvector */
         ImageMapPtr->ImageMap = malloc(sizeof(ColorType *) * Height);
         if(ImageMapPtr->ImageMap != NULL) {

            /* Initialize Image structure */
            ImageMapPtr->Height  = Height;
            ImageMapPtr->Width   = Width;
            ImageMapPtr->MapSizeInBytes = ImageMapSize;
            ImageMapPtr->BasePtr = ImagePtr;

            /* Fill row vectors (Pointer to start of row) */
            for( i = 0; i < Height; i++) {
               ImageMapPtr->ImageMap[i] = ImagePtr + i*Width;
            }
         } else {
            /* release allocated resources */
            free(ImageMapPtr);
            ImageMapPtr = NULL;
         }
      }
   }
   return ImageMapPtr;
}
/*****************************************************************************/
/*  End         : CreateImageMap                                             */
/*****************************************************************************/

/*****************************************************************************/
/*  Procedure   : DestroyImageMap                                            */
/*****************************************************************************/
/*                                                                           */
/*  Function    : DestroyImageMap an imagemap                                */
/*                                                                           */
/*  Type        : Global                                                     */
/*                                                                           */
/*  Input Para  : IPointer to the ImageMap to be destroyed                   */
/*                                                                           */
/*  Output Para : None                                                       */
/*                                                                           */
/*  Author      : I. Oesch                                                   */
/*                                                                           */
/*  History     : 16.11.2011  IO  Created                                    */
/*                                                                           */
/*****************************************************************************/
void DestroyImageMap(ImageMapType * ImageMap)
{

   /* Check for valid image */
   if (ImageMap != NULL) {

      /* release resources */
      free(ImageMap->ImageMap);
      free(ImageMap);
   }
}
/*****************************************************************************/
/*  End         : DestroyImageMap                                            */
/*****************************************************************************/

/*****************************************************************************/
/*  End Module  : Mainmodule                                                 */
/*****************************************************************************/



