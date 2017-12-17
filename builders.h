#include "mem.h"
#include "blocks.h"

#ifndef _BUILDERS_INCL

#define _BUILDERS_INCL

void buildBasicBlock(struct Coordinate*, struct TetrisBlock*);
void buildMediumBlock(struct Coordinate*, struct TetrisBlock*);
void buildMassiveBlock(struct Coordinate*, struct TetrisBlock*);
void buildZBlock(struct Coordinate*, struct TetrisBlock*);
void buildRZBlock(struct Coordinate*, struct TetrisBlock*);
void buildTinyRectangle(struct Coordinate*, struct TetrisBlock*);
void buildMediumRectangle(struct Coordinate*, struct TetrisBlock*);
void buildMassiveRectangle(struct Coordinate*, struct TetrisBlock*);
void buildTinyT(struct Coordinate*, struct TetrisBlock*);
void buildlBlock(struct Coordinate*, struct TetrisBlock*);
void buildlrBlock(struct Coordinate*, struct TetrisBlock*);

#endif