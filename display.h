#include <stdint.h>
#include "mem.h"


#ifndef _DISPLAY_INCL
#define _DISPLAY_INCL

uint8_t spi2PutByte(uint8_t data);
void initializeOled(void);
void updateOled(void);
void quicksleep( int );
void activatePixel(int, int);
void deactivatePixel(int, int);
int getPixel(int, int);

extern uint8_t displayBuffer[byteMemoryPages][byteColumns];

#endif