/*
	This code was written to support the book, "ARM Assembly for Embedded Applications",
	by Daniel W. Lewis. Permission is granted to share this software without permnission
	provided that this notice is not removed. This software is intended to be used with
	a special run-time library written by the author for the EmBitz IDE, using the
	"Sample Program for the 32F429IDISCOVERY Board" as an example, and available for
	download from http://www.engr.scu.edu/~dlewis/book3.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <math.h>
#include "library.h"
#include "graphics.h"

// Functions to be implemented in assembly
extern float Discriminant(float a, float b, float c) ;
extern float Root1(float a, float b, float c) ;
extern float Root2(float a, float b, float c) ;
extern float Quadratic(float x, float a, float b, float c) ;

// Functions not callable from assembly
static int	Close(float a, float b) ;
static void	DrawXAxis(void) ;
static void	DrawYAxis(void) ;
static void	PlotQuadratic(float a, float b, float c) ;
static void	PlotRoot(float x) ;
static int	PutStringAt(int row, int col, char *fmt, ...) ;
static int	PutStatus(int row, int col, int ok) ;

#define	ENTRIES(a)	(sizeof(a)/sizeof(a[0]))

#define	GFXCOL1		0
#define	GFXCOLN		(XPIXELS-1)
#define	GFXCOLS		(GFXCOLN - GFXCOL1 + 1)

#define	GFXROW1		45
#define	GFXROWN		305
#define	GFXROWS		(GFXROWN - GFXROW1 + 1)

#define	AXISROW		(GFXROW1 + GFXROWS/2)
#define	AXISCOL		(GFXCOL1 + GFXCOLS/2)

#define	XMIN		-30.0
#define	XMAX		+30.0
#define	YMIN		-130.0
#define	YMAX		+130.0

#define	TXT_HEIGHT	15
#define	TXT_WIDTH	7

#define	PARAM_ROW1	(GFXROW1 + 10)
#define	VALUE_ROW1	(GFXROWN - 3*TXT_HEIGHT)

#define	LBL_COL		10
#define	STS_COL		(LBL_COL + 25*TXT_WIDTH)

#define	TICKRATE	20
#define	TICKSIZE	4

#define	PLOT_RAD	1
#define	ROOT_RAD	4

#define	COLOR_PLOT	COLOR_BLUE
#define	COLOR_ROOT	COLOR_RED
#define	COLOR_AXIS	COLOR_BLACK

int main(void)
	{
	typedef struct
		{
		float	a, b, c ;
		float	d ;
		float	r1, r2 ;
		} TESTCASE ;
	static TESTCASE testcase[] =
		{
		{+1.0,   0.0, -100.0, +400.0, +10.0, -10.0},	// 2 roots
		{-1.0, +30.0, -225.0,    0.0, +15.0, +15.0},	// 1 root
		{+1.0, +30.0, +240.0,  -60.0,   0.0,   0.0}		// Imaginary roots
		} ;
	float my_d, my_r1, my_r2 ;
	float a, b, c, d, r1, r2 ;
	int k, row ;

	InitializeHardware(HEADER, "Lab 8b: Floating Point Quadratics") ;

	k = 0 ;
	while (1)
		{
		ClearDisplay() ;

		a  = testcase[k].a ;
		b  = testcase[k].b ;
		c  = testcase[k].c ;
		d  = testcase[k].d ;
		r1 = testcase[k].r1 ;
		r2 = testcase[k].r2 ;

		row = PARAM_ROW1 ;
		row = PutStringAt(row, LBL_COL, "Coefficient A:%10.2f (x^2)", a) ;
		row = PutStringAt(row, LBL_COL, "Coefficient B:%10.2f (x^1)", b) ;
		row = PutStringAt(row, LBL_COL, "Coefficient C:%10.2f (x^0)", c) ;

		row = VALUE_ROW1 ;
		my_d = Discriminant(a, b, c) ;
		PutStringAt(row, LBL_COL, " Discriminant:%10.2f", my_d) ;
		row = PutStatus(row, STS_COL, Close(my_d, d)) ;

		if (my_d < 0)
			{
			PutStringAt(row, LBL_COL, "        Roots:%10s", "Imag") ;
			row = PutStatus(row, STS_COL, 1) ;
			}
		else if (my_d > 0)
			{
			my_r1 = Root1(a, b, c) ;
			PutStringAt(row, LBL_COL, "   First root:%10.2f", my_r1) ;
			row = PutStatus(row, STS_COL, Close(my_r1, r1)) ;

			my_r2 = Root2(a, b, c) ;
			PutStringAt(row, LBL_COL, "  Second root:%10.2f", my_r2) ;
			row = PutStatus(row, STS_COL, Close(my_r2, r2)) ;

			PlotRoot(my_r1) ;
			PlotRoot(my_r2) ;
			}
		else // if (my_d == 0)
			{
			my_r1 = Root1(a, b, c) ;
			PutStringAt(row, LBL_COL, "  Single root:%10.2f", my_r1) ;
			row = PutStatus(row, STS_COL, Close(my_r1, r1)) ;

			PlotRoot(my_r1) ;
			}

		PlotQuadratic(a, b, c) ;
		WaitForPushButton() ;
		k = (k + 1) % ENTRIES(testcase) ;
		}

	return 0 ;
	}

static void PlotQuadratic(float a, float b, float c)
	{
	int oldRow = 0 ;

	DrawXAxis() ;
	DrawYAxis() ;

	SetColor(COLOR_PLOT) ;
	for (int col = 0; col < GFXCOLS; col++)
		{
		float x, y ;
		int row ;

		x = XMIN + col / 4.0 ;
		y = Quadratic(x, a, b, c) ;

		row = 0.5 + GFXROWN + (YMIN - y) ;
		do
			{
			if (!oldRow) oldRow = row ;
			if (GFXROW1 <= oldRow && oldRow <= GFXROWN) FillCircle(col, oldRow, PLOT_RAD) ;
			if (oldRow < row) oldRow++ ;
			else if (oldRow > row) oldRow-- ;
			} while (row != oldRow) ;
		}
	}

static void PlotRoot(float x)
	{
	int col ;

	col = (int) (0.5 + 4.0*(x - XMIN)) ;

	if (col < ROOT_RAD || col > GFXCOLS - ROOT_RAD) return ;

	SetColor(COLOR_ROOT) ;
	FillCircle(col, AXISROW, ROOT_RAD) ;
	}

static void DrawXAxis(void)
	{
	int col, rowMin, rowMax ;

	SetColor(COLOR_AXIS) ;
	rowMin = AXISROW - TICKSIZE/2 ;
	rowMax = rowMin + TICKSIZE ;
	DrawLine(GFXCOL1, AXISROW, GFXCOLN, AXISROW) ;
	for (col = TICKRATE; col < GFXCOLS/2; col += TICKRATE)
		{
		DrawLine(AXISCOL + col, rowMin, AXISCOL + col, rowMax) ;
		DrawLine(AXISCOL - col, rowMin, AXISCOL - col, rowMax) ;
		}

	DisplayStringAt(AXISCOL - 4*TICKRATE - 12, AXISROW + 8, "-20") ;
	DisplayStringAt(AXISCOL - 2*TICKRATE - 12, AXISROW + 8, "-10") ;
	DisplayStringAt(AXISCOL + 2*TICKRATE - 12, AXISROW + 8, "+10") ;
	DisplayStringAt(AXISCOL + 4*TICKRATE - 12, AXISROW + 8, "+20") ;
	}

static void DrawYAxis(void)
	{
	int row, colMin, colMax ;

	SetColor(COLOR_AXIS) ;
	colMin = AXISCOL - TICKSIZE/2 ;
	colMax = colMin + TICKSIZE ;
	DrawLine(AXISCOL, GFXROW1, AXISCOL, GFXROWN) ;
	for (row = TICKRATE; row < GFXROWS/2; row += TICKRATE)
		{
		DrawLine(colMin, AXISROW + row, colMax, AXISROW + row) ;
		DrawLine(colMin, AXISROW - row, colMax, AXISROW - row) ;
		}

	DisplayStringAt(AXISCOL + 6, AXISROW - 2*TICKRATE - 5, "+40") ;
	DisplayStringAt(AXISCOL + 6, AXISROW + 2*TICKRATE - 5, "-40") ;
	}

static int PutStatus(int row, int col, int ok)
	{
	if (!ok)
		{
		SetForeground(COLOR_WHITE) ;
		SetBackground(COLOR_RED) ;
		}

	PutStringAt(row, col, "%s", ok ? "CORRECT" : " WRONG ") ;

	SetForeground(COLOR_BLACK) ;
	SetBackground(COLOR_WHITE) ;

	return row + TXT_HEIGHT ;
	}

static int PutStringAt(int row, int col, char *fmt, ...)
	{
	va_list args ;
	char text[100] ;

	va_start(args, fmt) ;
	vsprintf(text, fmt, args) ;
	va_end(args) ;

	DisplayStringAt(col, row, text) ;

	return row + TXT_HEIGHT ;
	}

static int Close(float a, float b)
	{
	float largest = fabs((fabs(a) > fabs(b)) ? a : b) ;
	float threshold = 0.001 * largest ;
	return fabs(a - b) <= threshold ;
	}

