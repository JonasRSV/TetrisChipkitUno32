#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mem.h"
#include "game.h"
#include "input.h"
#include "paint.h"
#include "display.h"


void initializeMagic( void ) {
    // Following lines is magic from the lab
    SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
    SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
    while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
    OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
    while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
    SYSKEY = 0x0;  /* Lock OSCCON */
    
    /* Set up output pins */
    AD1PCFG = 0xFFFF;
    ODCE = 0x0;
    TRISECLR = 0xFF;
    PORTE = 0x0;
    
    /* Output pins for display signals */
    PORTF = 0xFFFF;
    PORTG = (1 << 9);
    ODCF = 0x0;
    ODCG = 0x0;
    TRISFCLR = 0x70;
    TRISGCLR = 0x200;
    
    /* Set up input pins */
    TRISDSET = (1 << 8);
    TRISFSET = (1 << 1);
    
    /* Set up SPI as master */
    SPI2CON = 0;
    SPI2BRG = 4;
    /* SPI2STAT bit SPIROV = 0; */
    SPI2STATCLR = 0x40;
    /* SPI2CON bit CKP = 1; */
    SPI2CONSET = 0x40;
    /* SPI2CON bit MSTEN = 1; */
    SPI2CONSET = 0x20;
    /* SPI2CON bit ON = 1; */
    SPI2CONSET = 0x8000;

}

void initializeInterrupts() {

    // PORTD = PORTD | 0x7e0;


    /* 
        Set SW4 Interrupt for DROP-Timer
    */
    IFSCLR(0) = (1 << 19); 
    IPCSET(4) = (1 << 28) + (1 << 27) + (1 << 26) + (1 << 25) + (1 << 24); 
    IECSET(0) = (1 << 19);

    /*

        Set SW3 Interrupt for Pause Game

    */

    // IFSCLR(0) = (1 << 15);
    // IPCSET(4) = (1 << 28) + (1 << 27) + (1 << 26) + (1 << 25) + (1 << 24); 
    // IECSET(0) = (1 << 15);




    /* TIMER 1 SETTINGS 16 bit timer */
    T4CONCLR = (1 << 15);
    T4CONSET = (1 << 4) + (1 << 5) + (1 << 6);
    TMR4 = 0x0;
    PR4 = PLAYER_SPEED;

    IPCSET(4) = 0x1f;
    IFSCLR(0) = (1 << 16);
    IECSET(0) = (1 << 16);



    /*T2 Settings, 32 bit timer */
    T2CONCLR = (1 << 15); // Turns timer off
    T2CONSET = (1 << 3); //32 bit timer on
    T2CONSET = (1 << 4) + (1 << 5) + (1 << 6); // Set scale
    
    TMR2 = 0x0; // Clear content of T3/T3 

    PR2 = GAME_SPEED;  
        //Faster good for testing
    // PR2 = 0x00001012;

    IPCSET(3) = 0x1f; //Full priority and sub priority
    IFSCLR(0) = (1 << 12); //Clear interrupt status flag.
    IECSET(0) = (1 << 12); //Enable Timer3 Interrupts.
    

  asm("ei");

  T4CONSET = (1 << 15);
  T2CONSET = (1 << 15); //Turns timer on.. 32 bit timer only read T2 con

}

void initializeIO( void ) {
    //for button 2-4, 1 << 11 for SW4

    TRISDSET = 0xe0 + (1 << 11);

    //For button 1
    TRISFSET = 0x2;

    //For SCORE Lamps
    TRISE = 0x0;

    PORTECLR = 0xff;
}


//Cancer Mips does not have Malloc

int BUTTON_1 = 0;
int BUTTON_2 = 0;
int BUTTON_3 = 0;
int BUTTON_4 = 0;
uint16_t SCORE = 0;

struct TetrisBlock *gameBlock;

/*
    MIPS Architecture or something sux bawls.. IF i add a function or memory read anywhere in this function everything breaks.
    If i remove one i can add another.. but it seems as if functions are capped on how many further calls they can make.. or something.
    Because of this i cannot add Game Pause functionality..

    For example.. try to add 

    if (IFS(0) & (1 << 15)) {
        ..
    }

    in the ISR.. everything will break.

*/
void user_isr( void ) { //Magic function Called on interrupts

    // testPixelColoring();
    // testPixelKilling();
    // testPaintBlockWithRandom();
    // testPaintBlock();
    // testClearBlock();
    // tick(gameBlock);
    // if (IFS(0) & (1 << 15)) {
    // }

    if (IFS(0) & (1 << 19)) {
        setDropTimer();
    }

    if (IFS(0) & (1 << 12)) {
        gameBlock = gameTick(gameBlock);
    }

    if (IFS(0) & (1 << 16)) {
        pollIO();
        gameBlock = playerTick(gameBlock);
    }

    updateOled();

    IFSCLR(0) = (1 << 19); //Sw4
    IFSCLR(0) = (1 << 16); //T4
    IFSCLR(0) = (1 << 12); //32 bit T2

}


int main(void) {
    initializeMagic();
    initializeOled();
    initializeInterrupts();
    initializeIO();
    gameBlock = initializeGame();
    paintWorld();
    while(1) { }
}
