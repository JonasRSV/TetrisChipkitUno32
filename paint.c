#include "mem.h"
#include "display.h"
#include "blocks.h"

int getBlockActivation(int x, int y, const char *geometry) {
    return geometry[x + blockSize * y];
}

int getBlockActivationOnRoids(int x, int y, const char *geometry) {
    if (x <= 0 || x >= gameWidth || y >= gameWidth) {
        return 0; //Not activate out of bounds
    }

    return getBlockActivation(x, y, geometry);
}

int getPixelOnRoids(int x, int y) {
    if (x < 0 || x >= gameWidth || y >= gameHeigth) {
        return 1; //Active out of bounds
    }

    return getPixel(x, y);
}

void clearScreen( void ) {
    int x;
    int y;

    //Clears Screen
    for (x = wallOffset; x < gameWidth - wallOffset; x++) {
        for (y = wallOffset; y < gameHeigth - wallOffset; y++) {
            deactivatePixel(x, y);
        }
    }
}

void paintBorder( void ) {
    int x;
    int y;

    for (y = 0; y < 2; y++) {
        for(x = 0; x < gameWidth; x++) {
            activatePixel(x, y);
        }
    }

    for(y = gameHeigth - 1; y > gameHeigth - 3; y--) {
        for(x = 0; x < gameWidth; x++) {
            activatePixel(x, y);
        }
    }

    for (x = 0; x < 2; x++) {
        for(y = 0; y < gameHeigth; y++) {
            activatePixel(x, y);
        }
    }

    for (x = gameWidth - 1; x > gameWidth - 3; x--) {
        for(y = 0; y < gameHeigth; y++) {
            activatePixel(x, y);
        }
    }
}

void paintBanner( void ) {
    int x;
    int y;

    for (x = 2; x < gameWidth - 2; x++) {
        for (y = 0; y < byteSize; y++) {
            if (banner[x - 2 + y*(gameWidth - 2)]) {
                activatePixel((gameWidth - 1 ) - x, y + 2);
            }
        }
    }
}


void paintWorld( void ) {
    paintBanner();
    paintBorder();
}



void paintBlock(struct TetrisBlock *block) {
    int startX = block->position->x;
    int startY = block->position->y;

    int relativeX;
    int relativeY;

    for (relativeX = 0; relativeX < blockSize; relativeX++) {
        for (relativeY = 0; relativeY < blockSize; relativeY++) {
            if (getBlockActivation(relativeX, relativeY, block->geometry)) {
                activatePixel(startX + relativeX, startY + relativeY);
            } 
        }
    }
}


void clearBlock(struct TetrisBlock *block) {
    int startX = block->position->x;
    int startY = block->position->y;

    int relativeX;
    int relativeY;

    for (relativeX = 0; relativeX < blockSize; relativeX++) {
        for (relativeY = 0; relativeY < blockSize; relativeY++) {
            if (getBlockActivation(relativeX, relativeY, block->geometry)) {
                deactivatePixel(relativeX + startX, relativeY + startY);
            }
        }
    }
}
