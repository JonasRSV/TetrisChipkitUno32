#include <stdint.h>
#include <pic32mx.h>
#include "mem.h"


void setDropTimer( void ) {
    T2CONCLR = (1 << 15);
    TMR2 = 0x0;
    PR2 = 0x1000;
    IFSCLR(0) = (1 << 12);
    T2CONSET = (1 << 15);
}

void updateTimerSpeed( void ) {
    T2CONCLR = (1 << 15);
    TMR2 = 0x0;
    PR2 = GAME_SPEED >> (SCORE >> 1);
    IFSCLR(0) = (1 << 12);
    T2CONSET = (1 << 15);
}

void pollIO ( void ) {

    if (PORTF & 0x2) {
        BUTTON_1 +=1;
    }

    if (PORTD & 0x20) {
        BUTTON_2 +=1;
    }

    if (PORTD & 0x40) {
        BUTTON_3 +=1;
    }

    if (PORTD & 0x80) {
        BUTTON_4 += 1;
    }

}



/*
Because mipsrandom Fails at the moment this will work as substitute

*/

char mipsPseudoBadRandom(char range)  {
    return (char) TMR4 % range;
}
