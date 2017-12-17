#include "mem.h"

#ifndef _RULES_INCL

#define _RULES_INCL

struct TetrisBlock* randomBlock();
void blockCollision(struct TetrisBlock*);
int availableRotation(struct TetrisBlock*);
int* mapScanOffset( void );
void shiftMap(int*);

#endif