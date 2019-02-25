/* File: LIBRARY.H */

#ifndef __LIBRARY_H
#define __LIBRARY_H

#define	HEADER		NULL
#define	ERROR_FLAG	"ERR"

void		ClearDisplay(void) ;
void		ClearScreen(int color) ;
void		DisplayHeader(char *header) ;
void		DisplayFooter(char *footer) ;
uint32_t	GetClockCycleCount(void) ;
uint32_t	GetRandomNumber(void) ;
void		InitializeHardware(char *header, char *footer) ;
unsigned	PrintBits(int bin[]) ;
void		PrintByte(uint8_t byte) ;
int			PushButtonPressed(void) ;
void		WaitForPushButton(void) ;

#define		asm		__asm

#endif
