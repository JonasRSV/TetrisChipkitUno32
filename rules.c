#include <stdint.h>
#include <pic32mx.h>
#include "mem.h"
#include "builders.h"
#include "paint.h"
#include "display.h"
#include "input.h"

#define BasicBlockId 0
#define MediumBlockId 1
#define MassiveBlockId 2
#define ZBlockId 3
#define RZBlockId 4
#define TinyRectangleId 5
#define MediumRectangleId 6
#define MassiveRectangleId 7
#define TinyTId 8
#define LRBlock 9
#define LBlock 10

//InitilaizeRandomGenerator

struct TetrisBlock* randomBlock() {
    //Real random function declared in random.S does not work, since syscall hangs the shit or something.. 
    //Another shit upon a multitude encountered with chipkitshit
    int blockId = mipsPseudoBadRandom(11); 
    // int blockId = 7;

    // activatePixel(20, 30);
    switch (blockId) {
        case BasicBlockId: buildBasicBlock(&position, &block0);
            break;
        case MediumBlockId: buildMediumBlock(&position, &block0);
            break;
        case MassiveBlockId: buildMassiveBlock(&position, &block0);
            break;
        case ZBlockId: buildZBlock(&position, &block0);
            break;
        case RZBlockId: buildRZBlock(&position, &block0);
            break;
        case TinyRectangleId: buildTinyRectangle(&position, &block0);
            break;
        case MediumRectangleId: buildMediumRectangle(&position, &block0);
            break;
        case MassiveRectangleId: buildMassiveRectangle(&position, &block0);
            break;
        case TinyTId: buildTinyT(&position, &block0);
            break;
        case LRBlock: buildlrBlock(&position, &block0);
            break;
        case LBlock: buildlBlock(&position, &block0);
            break;
    }

    return &block0;
}




//Might not be the most efficient collision detection every.. but since my blocks are at most 32*32 in dimension
//This should not be very heavy calculating. WCS ill just reduce tick-rate
void blockCollision(struct TetrisBlock *block) {
    int startX = block->position->x;
    int startY = block->position->y;

    int relativeX;
    int relativeY;

    int partOfBlockCollidedBottom = 0;
    int partOfBlockCollidedLeft = 0;
    int partOfBlockCollidedRight = 0;

    for (relativeX = 0; relativeX < blockSize; relativeX++) {
        for (relativeY = 0; relativeY < blockSize; relativeY++) {
            if (getBlockActivation(relativeX, relativeY, block->geometry)) {                       //Block active at pixel

                if (getPixelOnRoids(relativeX + startX + wallOffset, relativeY + startY)) {                //Pixel active
                    partOfBlockCollidedLeft = 1;
                }

                if(getPixelOnRoids(relativeX + startX - wallOffset, relativeY + startY)) {                //--||--
                   partOfBlockCollidedRight = 1;
                }

                if(getPixelOnRoids(relativeX + startX, relativeY + startY + wallOffset)) {                //--||--
                   partOfBlockCollidedBottom = 1;
                }

                //TOP COLLISION cannot occur... yet
                // if(!getBlockActivationOnRoids(relativeX, relativeY - 1, block->geometry) &&      //--||--
                //    getPixelOnRoids(relativeX + startX, relativeY + startY - 1)) {                //--||--
                //     block->rightCollision = BLOCKCOLLIDED;
                // } else {
                //     block->rightCollision = BLOCKFREE;
                // }

            }  
        }
    }

    block->bottomCollision = partOfBlockCollidedBottom;
    block->rightCollision = partOfBlockCollidedRight;
    block->leftCollision = partOfBlockCollidedLeft;
}

//Neither very computing efficient, but it think it'll be fine.
int availableRotation(struct TetrisBlock *next) {
    int startX = next->position->x;
    int startY = next->position->y;

    int relativeX;
    int relativeY;

    for (relativeX = 0; relativeX < blockSize; relativeX++) {
        for(relativeY = 0; relativeY < blockSize; relativeY++) {
            if (getBlockActivationOnRoids(relativeX, relativeY, next->geometry) && //Next occupies space
                 getPixelOnRoids(startX + relativeX, startY + relativeY)) {             //Something else occupies space
                return 0;                                                               //Not available
            }
        }
    }

    return 1;                                                                           //Available
}

/*

    BOTH THE offset and the shift has to account for the banner and borders, because the graphics buffer
    and logic buffer is not separated that's why there's a bunch of wierd - signs everywhere.. cba fixing it.

*/

int saturizedRows[gameHeigth];
int* mapScanOffset( void ) {

    int x;
    int y;
    int offset;
    int saturized;

    offset = 0;
    for (y = gameHeigth - 3; y > 1 + byteSize; y--) {
        saturized = 1;

        for (x = wallOffset; x < gameWidth - wallOffset; x++) {
            if (!getPixelOnRoids(x, y)) {
                saturized = 0;
                break;
            }
        }

        if (saturized) {
            offset++;
            saturizedRows[y] = -1;
            SCORE++;
        } else {
            saturizedRows[y] = offset;
        }

    }

    return saturizedRows;
}

char temporaryGameBuffer[gameWidth][gameHeigth];
void shiftMap(int* offset) {

    int x;
    int y;


    for (y = wallOffset + byteSize; y < gameHeigth - wallOffset; y++) {
        for(x = wallOffset; x < gameWidth - wallOffset; x++) {
            temporaryGameBuffer[x][y] = getPixelOnRoids(x, y);
            deactivatePixel(x, y);
        }
    }


    for (y = wallOffset + byteSize; y < gameHeigth - wallOffset; y++) {
        for (x = wallOffset; x < gameWidth - wallOffset; x++) {
            if (offset[y] == -1) {
                break;
            }

           if (temporaryGameBuffer[x][y]) { 
                activatePixel(x, y + offset[y]);
           }
        }
    }
}


