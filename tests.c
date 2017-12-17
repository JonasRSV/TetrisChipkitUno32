#include <stdint.h>
#include "mem.h"
#include "display.h"
#include "paint.h"
#include "builders.h"

/* Test Functions */

int pixelColoringTestVariable = 0;
void testPixelColoring( void ) {
    activatePixel(pixelColoringTestVariable%gameWidth, pixelColoringTestVariable/gameWidth);

    pixelColoringTestVariable ++;
    pixelColoringTestVariable %= (gameHeigth * gameWidth);
}

int pixelKillingTestVariableOn = 1;
int pixelKillingTestVariableOff = 0;
void testPixelKilling( void ) {
    activatePixel(pixelKillingTestVariableOn%gameWidth, pixelKillingTestVariableOn/gameWidth);
    deactivatePixel(pixelKillingTestVariableOff%gameWidth, pixelKillingTestVariableOff/gameWidth);

    pixelKillingTestVariableOn++;
    pixelKillingTestVariableOff++;

    pixelKillingTestVariableOn %= (gameHeigth * gameWidth);
    pixelKillingTestVariableOff %= (gameHeigth * gameWidth);

}

void testPaintBlock( void ) {
    struct TetrisBlock block;
    struct Coordinate position;

    position.x = 16;
    position.y = 64;

    buildRZBlock(&position, &block);
    paintBlock(&block);
}

void testPaintBlockWithRandom( void ) {
    struct TetrisBlock block;
    struct Coordinate position;

    position.x = 16;
    position.y = 64;
    randomBlock(&position, &block);

    clearBlock(&block);
    paintBlock(&block);
    activatePixel(16, 64);
}

int clearPositionIntervallVariable = 0;
void testClearBlock () {
    struct TetrisBlock block;
    struct Coordinate position;

    position.x = 16;
    position.y = 64;
    
    buildMassiveRectangle(&position, &block);

    if (clearPositionIntervallVariable % 31 == 0) {
        paintBlock(&block);
    }

    if (clearPositionIntervallVariable % 17 == 0) {
        clearBlock(&block);
    }

    clearPositionIntervallVariable +=1;
}

