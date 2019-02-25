/* File: GRAPHICS.H */

#ifndef __GRAPHICS_H
#define __GRAPHICS_H

void     BSP_LCD_SetTextColor(uint32_t Color);
void     BSP_LCD_SetBackColor(uint32_t Color);

uint32_t BSP_LCD_ReadPixel(uint16_t Xpos, uint16_t Ypos);
void     BSP_LCD_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint32_t pixel);
void     BSP_LCD_Clear(uint32_t Color);
void     BSP_LCD_ClearStringLine(uint32_t Line);
void     BSP_LCD_DisplayStringAtLine(uint16_t Line, uint8_t *ptr);
void     BSP_LCD_DisplayStringAt(uint16_t X, uint16_t Y, uint8_t *pText, int alignment);
void     BSP_LCD_DisplayChar(uint16_t Xpos, uint16_t Ypos, uint8_t Ascii);

void     BSP_LCD_DrawHLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length);
void     BSP_LCD_DrawVLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length);
void     BSP_LCD_DrawLine(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2);
void     BSP_LCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void     BSP_LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void     BSP_LCD_DrawEllipse(int Xpos, int Ypos, int XRadius, int YRadius);
void     BSP_LCD_DrawBitmap(uint32_t X, uint32_t Y, uint8_t *pBmp);

void     BSP_LCD_FillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void     BSP_LCD_FillCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void     BSP_LCD_FillTriangle(uint16_t X1, uint16_t X2, uint16_t X3, uint16_t Y1, uint16_t Y2, uint16_t Y3);
void     BSP_LCD_FillEllipse(int Xpos, int Ypos, int XRadius, int YRadius);

#ifndef __PIXELS
#define __PIXELS
#define  XPIXELS   240	// The left edge of the screen is at x = 0
#define  YPIXELS   320	// The top edge of the screen is at y = 0
#endif

#define  SetColor(Color)                            BSP_LCD_SetTextColor(Color)
#define  SetForeground(Color)						BSP_LCD_SetTextColor(Color)
#define  SetBackground(Color)						BSP_LCD_SetBackColor(Color)

#define  ReadPixel(Xpos, Ypos)                      BSP_LCD_ReadPixel(Xpos, Ypos)
#define  DrawPixel(Xpos, Ypos, pixel)               BSP_LCD_DrawPixel(Xpos, Ypos, pixel)
#define  ClearScreen(Color)							BSP_LCD_Clear(Color)
#define  ClearStringLine(Line)                      BSP_LCD_ClearStringLine(Line)
#define  DisplayStringAtLine(Line, ptr)             BSP_LCD_DisplayStringAtLine(Line, (uint8_t *) ptr)
#define  DisplayStringAt(X, Y, pText)               BSP_LCD_DisplayStringAt(X, Y, (uint8_t *) pText, 3)
#define  DisplayChar(Xpos, Ypos, Ascii)             BSP_LCD_DisplayChar(Xpos, Ypos, Ascii)

#define  DrawHLine(Xpos, Ypos, Length)              BSP_LCD_DrawHLine(Xpos, Ypos, Length)
#define  DrawVLine(Xpos, Ypos, Length)              BSP_LCD_DrawVLine(Xpos, Ypos, Length)
#define  DrawLine(X1, Y1, X2, Y2)                   BSP_LCD_DrawLine(X1, Y1, X2, Y2)
#define  DrawRect(Xpos, Ypos, Width, Height)        BSP_LCD_DrawRect(Xpos, Ypos, Width, Height)
#define  DrawCircle(Xpos, Ypos, Radius)             BSP_LCD_DrawCircle(Xpos, Ypos, Radius)
#define  DrawEllipse(Xpos, Ypos, XRadius, YRadius)  BSP_LCD_DrawEllipse(Xpos, Ypos, XRadius, YRadius)
#define  DrawBitMap(X, Y, pBmp)                     BSP_LCD_DrawBitmap(X, Y, pBmp)

#define  FillRect(Xpos, Ypos, Width, Height)        BSP_LCD_FillRect(Xpos, Ypos, Width, Height)
#define  FillCircle(Xpos, Ypos, Radius)             BSP_LCD_FillCircle(Xpos, Ypos, Radius)
#define  FillTriangle(X1, X2, X3, Y1, Y2, Y3)       BSP_LCD_FillTriangle(X1, X2, X3, Y1, Y2, Y3)
#define  FillEllipse(Xpos, Ypos, XRadius, YRadius)  BSP_LCD_FillEllipse(Xpos, Ypos, XRadius, YRadius)

#define COLOR_BLUE          0xFF0000FF
#define COLOR_GREEN         0xFF00FF00
#define COLOR_RED           0xFFFF0000
#define COLOR_CYAN          0xFF00FFFF
#define COLOR_MAGENTA       0xFFFF00FF
#define COLOR_YELLOW        0xFFFFFF00
#define COLOR_LIGHTBLUE     0xFF8080FF
#define COLOR_LIGHTGREEN    0xFF80FF80
#define COLOR_LIGHTRED      0xFFFF8080
#define COLOR_LIGHTCYAN     0xFF80FFFF
#define COLOR_LIGHTMAGENTA  0xFFFF80FF
#define COLOR_LIGHTYELLOW   0xFFFFFF80
#define COLOR_DARKBLUE      0xFF000080
#define COLOR_DARKGREEN     0xFF008000
#define COLOR_DARKRED       0xFF800000
#define COLOR_DARKCYAN      0xFF008080
#define COLOR_DARKMAGENTA   0xFF800080
#define COLOR_DARKYELLOW    0xFF808000
#define COLOR_WHITE         0xFFFFFFFF
#define COLOR_LIGHTGRAY     0xFFD3D3D3
#define COLOR_GRAY          0xFF808080
#define COLOR_DARKGRAY      0xFF404040
#define COLOR_BLACK         0xFF000000
#define COLOR_BROWN         0xFFA52A2A
#define COLOR_ORANGE        0xFFFFA500
#define COLOR_TRANSPARENT   0xFF000000

#endif

