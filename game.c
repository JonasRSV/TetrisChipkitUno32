#include <stdint.h>
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mem.h"
#include "paint.h"
#include "rules.h"
#include "input.h"


struct TetrisBlock* initializeGame( void ) {
    position.x = STARTX;
    position.y = STARTY;

    block0.bottomCollision = 0;
    block0.rightCollision = 0;
    block0.leftCollision = 0;
    
    block1.bottomCollision = 0;
    block1.rightCollision = 0;
    block1.leftCollision = 0;

    block2.bottomCollision = 0;
    block2.rightCollision = 0;
    block2.leftCollision = 0;

    block3.bottomCollision = 0;
    block3.rightCollision = 0;
    block3.leftCollision = 0;

    block0.id = 0;
    block1.id = 1;
    block2.id = 2;
    block3.id = 3;

    clearScreen();
    return randomBlock();
}


void gameOverHandler( void ) {
    int x;

    //Check if any block is at start, if so.. Clear screen and reset score.. and continue, cuz why not.
    for (x = wallOffset; x < gameWidth - wallOffset; x++) {
        if (getPixelOnRoids(x, STARTY)) {
            clearScreen();
            SCORE = 0;

            break;
        }
    }
}


struct TetrisBlock* nextBlockHandler() {
    position.x = STARTX;
    position.y = STARTY;

    int * offsets = mapScanOffset();
    shiftMap(offsets);


    gameOverHandler();
    paintWorld();
    PORTE = SCORE >> 1;

    updateTimerSpeed();

    return randomBlock();
}




struct TetrisBlock* blockRotationHandler(struct TetrisBlock *block) {

    struct TetrisBlock *next = block;
    while(BUTTON_3 > 0) {
        next = next->prev;
        BUTTON_3--;
    }

    while(BUTTON_4 > 0) {
        next = next->next;
        BUTTON_4--;
    }


    if (next->id != block->id &&
        availableRotation(next)) {
        
        block->bottomCollision = 0;     //Reset block collisions
        block->leftCollision = 0;
        block->rightCollision = 0;

        block = next;                   //Set next block & update Collision
    }

    return block;
}

struct TetrisBlock* playerMoveHandler(struct TetrisBlock *block) {
    int PREFERRED_DIRECTION = BUTTON_1 - BUTTON_2;

    if (PREFERRED_DIRECTION == 0) {
        return block;
    }
    
    if (PREFERRED_DIRECTION > 0 && !block->leftCollision) {
        block->position->x += FALLSPEED;
    }

    if (PREFERRED_DIRECTION < 0 && !block->rightCollision) {
        block->position->x -= FALLSPEED;
    }

    BUTTON_1 = 0;
    BUTTON_2 = 0;
    return block;
}



struct TetrisBlock* playerTick( struct TetrisBlock *block ) {

    clearBlock(block);

    blockCollision(block);

    block = blockRotationHandler(block);
    block = playerMoveHandler(block);

    blockCollision(block);

    paintBlock(block);

    return block;
}


// Overly  Complex function.. The paint is bound to the logic so one has to clearThe block before
//Doing blockCollision.. otherwise it can "Collide" with itself
int FALL_TERMINATION_ULTRON_VARIABLE = 0;
struct TetrisBlock* gameTick( struct TetrisBlock *block ) {

    if (FALL_TERMINATION_ULTRON_VARIABLE) {
        FALL_TERMINATION_ULTRON_VARIABLE = 0;
        paintBlock(block);
        return nextBlockHandler();
    }
    
    clearBlock(block);
    blockCollision(block);

    if (block->bottomCollision) {
        FALL_TERMINATION_ULTRON_VARIABLE = 1;
        return block;
    }

    FALL_TERMINATION_ULTRON_VARIABLE = 0;

    block->position->y += FALLSPEED;
    paintBlock(block);

    return block;
}
