#include <stdint.h>
#include "mem.h"
#include "blocks.h"

struct TetrisBlock block0;
struct TetrisBlock block1;
struct TetrisBlock block2;
struct TetrisBlock block3;
struct Coordinate position;

void buildBasicBlock(struct Coordinate *position, struct TetrisBlock *block) {
    block->geometry = basicBlock;
    block->next = block;
    block->prev = block;
    block->position = position;
}

void buildMediumBlock(struct Coordinate *position, struct TetrisBlock *block) {
    block->geometry = mediumBlock;
    block->next = block;
    block->prev = block;
    block->position = position;
}

void buildMassiveBlock(struct Coordinate *position, struct TetrisBlock *block) {
    block->geometry = massiveBlock;
    block->next = block;
    block->prev = block;
    block->position = position;
}

void buildZBlock(struct Coordinate *position, struct TetrisBlock *block) {
    block->geometry = zBlock0;
    block1.geometry = zBlock1;

    block->next = &block1;
    block->prev = &block1;
    
    block1.next = block;
    block1.prev = block;

    block->position = position;
    block1.position = position;
}

void buildRZBlock(struct Coordinate *position, struct TetrisBlock *block) {
    block->geometry = zrBlock0;
    block1.geometry = zrBlock1;

    block->next = &block1;
    block->prev = &block1;

    block1.next = block;
    block1.prev = block;

    block->position = position;
    block1.position = position;

}


void buildTinyRectangle(struct Coordinate *position, struct TetrisBlock *block) {
    block->geometry = tinyRectangle0;
    block1.geometry = tinyRectangle1;

    block->next = &block1;
    block->prev = &block1;

    block1.next = block;
    block1.prev = block;

    block->position = position;
    block1.position = position;
}

void buildMediumRectangle(struct Coordinate *position, struct TetrisBlock *block) {
    block->geometry = mediumRectangle0;
    block1.geometry = mediumRectangle1;

    block->next = &block1;
    block->prev = &block1;

    block1.next = block;
    block1.prev = block;

    block->position = position;
    block1.position = position;
}

void buildMassiveRectangle(struct Coordinate *position, struct TetrisBlock *block) {
    block->geometry = massiveRectangle0;
    block1.geometry = massiveRectangle1;

    block->next = &block1;
    block->prev = &block1;

    block1.next = block;
    block1.prev = block;

    block->position = position;
    block1.position = position;
}

void buildTinyT(struct Coordinate* position, struct TetrisBlock *block) {
    block->geometry = tinyT0;
    block1.geometry = tinyT1;
    block2.geometry = tinyT2;
    block3.geometry = tinyT3;

    block->next = &block1;
    block->prev = &block3;

    block1.next = &block2;
    block1.prev = block;

    block2.next = &block3;
    block2.prev = &block1;

    block3.next = block;
    block3.prev = &block2;

    block->position = position;
    block1.position = position;
    block2.position = position;
    block3.position = position;
}


void buildlBlock(struct Coordinate* position, struct TetrisBlock *block) {
    block->geometry = lBlock0;
    block1.geometry = lBlock1;
    block2.geometry = lBlock2;
    block3.geometry = lBlock3;

    block->next = &block1;
    block->prev = &block3;

    block1.next = &block2;
    block1.prev = block;

    block2.next = &block3;
    block2.prev = &block1;

    block3.next = block;
    block3.prev = &block2;

    block->position = position;
    block1.position = position;
    block2.position = position;
    block3.position = position;
}


void buildlrBlock(struct Coordinate* position, struct TetrisBlock *block) {
    block->geometry = lrBlock0;
    block1.geometry = lrBlock1;
    block2.geometry = lrBlock2;
    block3.geometry = lrBlock3;

    block->next = &block1;
    block->prev = &block3;

    block1.next = &block2;
    block1.prev = block;

    block2.next = &block3;
    block2.prev = &block1;

    block3.next = block;
    block3.prev = &block2;

    block->position = position;
    block1.position = position;
    block2.position = position;
    block3.position = position;
}
