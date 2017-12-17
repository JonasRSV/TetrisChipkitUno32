#include "mem.h"


#ifndef _PAINT_INCL

#define _PAINT_INCL

int getBlockActivation(int, int, const char*);
int getBlockActivationOnRoids(int, int, const char*);
int getPixelOnRoids(int, int);
void clearScreen( void );
void paintBorder( void );
void paintBanner( void );
void paintWorld( void );
void paintBlock(struct TetrisBlock*);
void clearBlock(struct TetrisBlock*);

#endif