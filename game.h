#include "mem.h"

#ifndef _GAME_INCL

#define _GAME_INCL

/* Game Functions */
struct TetrisBlock* gameTick(struct TetrisBlock*);
struct TetrisBlock* playerTick(struct TetrisBlock*);
struct TetrisBlock* initializeGame( void );


#endif
