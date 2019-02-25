/* File: TOUCH.H */

#ifndef __TOUCH_H
#define __TOUCH_H

#ifndef __PIXELS
#define __PIXELS
#define  XPIXELS   240	// The left edge of the screen is at x = 0
#define  YPIXELS   320	// The top edge of the screen is at y = 0
#endif

void TS_Init(void) ;
int	TS_Touched(void) ;	// returns non-zero if touched
int	TS_GetX(void) ;		// returns 0 to XPIXELS - 1
int	TS_GetY(void) ;		// returns 0 to YPIXELS - 1

#endif
