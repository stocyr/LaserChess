#ifndef WINDOW_FUNCTIONS_H
#define WINDOW_FUNCTIONS_H
/*****************************************************************************/
/*  Header     : WindowFunctions                                Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : A collection of drawing and keyboard functions              */
/*               An interface to the QT library                              */
/*                                                                           */
/*                                                                           */
/*  Procedures : InitGraphic            Opens the graphic window             */
/*               CloseGraphic           Closes the graphic window            */
/*               SetAutoUpdate          Enables automatic update             */
/*               ClearWindow            Clears the window                    */
/*               SetDrawMode            Set hoe to draw (Transparent...)     */
/*               DrawFilledCircle       draws a filled circle                */
/*               DrawEmptyCircle        draws an empty circle                */
/*               DrawFilledRectangle    Draws a filled rectangle             */
/*               DrawEmptyRectangle     Draws an empty rectangle             */
/*               DrawLine               Draws a line                         */
/*               DrawPixel              Draws a single pixel/point           */
/*               DrawText               Draws a text                         */
/*               SelectFont             Selects the font for text to draw    */
/*               GetTextDimensions      Returns the space needed for text    */
/*               GetKeyPress            Waits for a pressed key and returns it*/
/*               IsKeyPressed           Checks if key has been pressed       */
/*               GetKeyEvent            Waits for a released or pressed      */
/*               IsKeyEventReady        Checks if key has been pressed/released*/
/*               GetMouseState          Get position and buttonstate of mouse*/
/*               GetMouseEvent          Returns position of last mouseevent  */
/*               WaitMs                 Waits the given time in ms           */
/*                                                                           */
/*  Advanced functions:                                                      */
/*                                                                           */
/*               CreateSubImage         Creates an copy of an image          */
/*               CreateImage            Creates an Imagebuffer               */
/*               LoadImage              Creates an Imagebuffer and Loads an Image*/
/*               DestroyImage           Releases an Imagebuffer              */
/*               SetEditedImage         Selects buffer for future drawings   */
/*               DrawImage              Draws the given imagebuffer          */
/*               CopyToImage            Copies part of an image to another   */
/*               GetImageSize           Delivers size of image               */
/*               Rotate                 Rotates future drawings              */
/*               Translate              Translates future drawings           */
/*               Scale                  Scales future Drawings               */
/*               ResetTransformations   Future drawings will be direct       */
/*                                                                           */
/*  Author     : I. Oesch                                                    */
/*                                                                           */
/*  History    : 02.04.2002  IO Created                                      */
/*               28.03.2004  IO Added cpp compatibility in header            */
/*               29.03.2004  IO Changed char to unsigned char in ColorType   */
/*               06.10.2010  IO Converted to QT as graphics library          */
/*                                                                           */
/*  File       : window.h                                                    */
/*                                                                           */
/*****************************************************************************/
/* MagicSoft                                                                 */
/*****************************************************************************/



/* imports */

/* module constant declaration  */
enum KeyCodes {
   W_KEY_CURSOR_UP    = 0x0100,
   W_KEY_CURSOR_DOWN  = 0x0101,
   W_KEY_CURSOR_LEFT  = 0x0102,
   W_KEY_CURSOR_RIGHT = 0x0103,

   W_KEY_F1          = 0x0110,
   W_KEY_F2          = 0x0111,
   W_KEY_F3          = 0x0112,
   W_KEY_F4          = 0x0113,
   W_KEY_F5          = 0x0114,
   W_KEY_F6          = 0x0115,
   W_KEY_F7          = 0x0116,
   W_KEY_F8          = 0x0117,
   W_KEY_F9          = 0x0118,
   W_KEY_F10         = 0x0119,
   W_KEY_F11         = 0x011A,
   W_KEY_F12         = 0x011B,

   W_KEY_MODIFIER    = 0x0200,
   W_KEY_SHIFT       = 0x0201,
   W_KEY_CTRL        = 0x0202,
   W_KEY_ALT         = 0x0203,
   W_KEY_ALTCTRL     = 0x0204,
   W_KEY_META        = 0x0205,


   W_KEY_CLOSE_WINDOW = 0x01FF,
   W_KEY_OTHER       = 0x0,

   W_KEY_RETURN      = 13,
   W_KEY_ESCAPE      = 27,
   W_KEY_TAB         =  9,
   W_KEY_RELEASED    =  0x2000,
   W_KEY_AUTOREPEAT  =  0x1000
};

enum MouseButtonCodes {
   W_BUTTON_NO_EVENT     =  0x0000,
   W_BUTTON_NONE         =  0x0000,
   W_BUTTON_LEFT         =  0x0001,
   W_BUTTON_MIDDLE       =  0x0002,
   W_BUTTON_RIGHT        =  0x0004,
   W_MOUSE_WHEEL_CHANGE  =  0x0008,
   W_BUTTON_PRESSED      =  0x1000,
   W_BUTTON_RELEASED     =  0x2000,
   W_BUTTON_DOUBLECLICK  =  0x4000,

};

enum MouseWheelKindEnum {
   MW_NONE       = 0x0000,
   MW_VERTICAL   = 0x0001,
   MW_HORIZONTAL = 0x0002
};

enum FontStyle {
   FONT_NORMAL = 0,
   FONT_BOLD   = 1,
   FONT_ITALIC = 2,
   FONT_BLACK  = 4
};

enum MaskMode {
   MSK_COLOR_IN  = 0,   /* Color is not masked out */
   MSK_COLOR_OUT = 1,   /* color is masked out */
   MSK_AUTO = 2         /* Heuristic mask from border */
};

enum DrawMode {
   DM_COPY      = 100,   /* Overwrite Destination (Ignore Transparency of source) */
   DM_COPYALPHA = 101,   /* Only copies the alphachannel to dest (Masks Dest with alpha from source)*/
   DM_OVER      = 102,   /* Using Alphachannel (Transparency) of source */
   DM_MIX       = 103,   /* The source pixel is blended on top of the destination, with the alpha of the source pixel reduced by the alpha of the destination pixel.*/
   DM_XOR       = 104,   /* Subtracts the darker of the colors from the lighter. Painting with white inverts the destination color, whereas painting with black leaves the destination color unchanged. */
   DM_MULTIPLY  = 105    /* Multiplies src with dst pixels */
};

enum ImageIDEnums {ID_WINDOW = -1};

/* module type declaration      */

typedef struct MouseInfo {
  int MousePosX;
  int MousePosY;
  int ButtonState;
  int MouseWheelKind;
  int MouseWheelDelta;
} MouseInfoType;


typedef struct ColorType {
   unsigned char Blue;
   unsigned char Green;
   unsigned char Red;
   unsigned char Alpha;
} ColorType;

typedef struct TextDimension {
  int Length;     /* Length of Text in Pixel */
  int Overhang; /* Extension to the left of starting point (possible with some italic fonts) */
  int Up;         /* Height from Baseline in Pixel */
  int Down;       /* Underlength from Baseline in Pixel (for Glyphes with underlength like gpqy) */
} TextDimensionType;


/* module data declaration      */

/* Some predefined colors for convenience */

static const ColorType COL_RED         = {0x00, 0x00, 0xFF, 0xFF};
static const ColorType COL_GREEN       = {0x00, 0xFF, 0x00, 0xFF};
static const ColorType COL_BLUE        = {0xFF, 0x00, 0x00, 0xFF};
static const ColorType COL_YELLOW      = {0x00, 0xFF, 0xFF, 0xFF};
static const ColorType COL_BROWN       = {0x13, 0x45, 0x8B, 0xFF};
static const ColorType COL_ORANGE      = {0x00, 0x8C, 0xFF, 0xFF};
static const ColorType COL_GREY        = {0x80, 0x80, 0x80, 0xFF};

static const ColorType COL_LIGHTRED    = {0x80, 0x80, 0xFF, 0xFF};
static const ColorType COL_LIGHTGREEN  = {0x80, 0xFF, 0x80, 0xFF};
static const ColorType COL_LIGHTBLUE   = {0xFF, 0x80, 0x80, 0xFF};
static const ColorType COL_LIGHTYELLOW = {0x80, 0xFF, 0xFF, 0xFF};
static const ColorType COL_WHITE       = {0xFF, 0xFF, 0xFF, 0xFF};

static const ColorType COL_DARKRED     = {0x80, 0x00, 0x00, 0xFF};
static const ColorType COL_DARKGREEN   = {0x00, 0x80, 0x00, 0xFF};
static const ColorType COL_DARKBLUE    = {0x80, 0x00, 0x00, 0xFF};
static const ColorType COL_DARKYELLOW  = {0x00, 0x80, 0x80, 0xFF};
static const ColorType COL_BLACK       = {0x00, 0x00, 0x00, 0xFF};

static const ColorType COL_TRANSPARENT = {0x00, 0x00, 0x00, 0x00};

/* module procedure declaration */

#ifdef __cplusplus
extern "C" {
#endif
extern void InitGraphic (int x, int y);
extern void CloseGraphic (void);
extern void SetAutoUpdate (int Mode);
extern void SetDrawMode(int Mode);
extern void DrawFilledCircle    (int x, int y, int Width, int Height, ColorType Color, int LineWidth);
extern void DrawEmptyCircle(int x, int y, int Width, int Height, ColorType Color, int LineWidth);
extern void DrawFilledRectangle (int x, int y, int Width, int Height, ColorType Color, int LineWidth);
extern void DrawEmptyRectangle (int x, int y, int Width, int Height, ColorType Color, int LineWidth);
extern void DrawLine (int x, int y, int tox, int toy, ColorType Color, int LineWidth);
extern void DrawPixel (int x, int y, ColorType Color);
extern ColorType GetPixel (int x, int y);
extern void DrawTextXY (int x, int y, ColorType Color, const char *Text);
extern void SelectFont(const char *FontName, int Points, enum FontStyle Style);
extern TextDimensionType GetTextDimensions (const char *Text);
//extern int  GetKey (void);
extern int  GetKeyPress (void);
extern int  GetKeyEvent (void);
//extern int  WaitForKeyEvent (void);
extern int  IsKeyPressReady (void);
extern int  IsKeyEventReady (void);
extern MouseInfoType GetMouseState (void);
extern MouseInfoType GetMouseEvent (void);

extern void WaitMs (int Time);
extern void ClearWindow(void);

extern int  CreateImage(int Width, int Height);
extern int  CreateSubImage(int SrcID, int x, int y, int Width, int Height);
extern int  LoadImage(const char *FileName);
extern void SaveImage(int Id, const char *FileName, const char *Format, int Quality);
extern void DestroyImage(int ImageId);

extern void SetEditedImage(int ImageId);
extern void DrawImage(int ImageId, int x, int y);
extern void CopyToImage(int x, int y, int Width, int Height, int ImageId);
extern void GetImageSize(int ImageId, int *Width, int *Height);
extern ColorType *GetPixelDataPointer(int ImageId, int *Length);
extern void AddAlphaMask(int ImageId, int Mode, ColorType Color);
extern void Rotate(float Angle);
extern void Translate(float dx, float dy);
extern void Scale(float Scalingx, float Scalingy);
extern void ResetTransformations(void);

extern void PlaySoundOnce (const char *FileName);
extern void PlaySoundContinuous(const char *FileName);
extern void StopContinuousSound (void);
extern void StartContinuousSound (void);

void StartTimer(int IntervalTime, void *Parameter, void (*Handler)(void *));
void StopTimer(void);



#ifdef __cplusplus
}
#endif


/*****************************************************************************/
/*  End Header  : WindowFunctions                                            */
/*****************************************************************************/
#endif

