#include <stdint.h>
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */

#ifndef _MEM_INCL

#define _MEM_INCL

#define byteBufferMax 512
#define byteColumns 128
#define byteMemoryPages 4
#define pixelBufferWidth 128
#define pixelBufferHeigth 32
#define byteSize 8

#define GAME_SPEED 0x00011012
#define PLAYER_SPEED 0x5000

#define blockSize 14
#define gameHeigth pixelBufferWidth
#define gameWidth pixelBufferHeigth
#define wallOffset 2

#define BLOCKCOLLIDED 1
#define BLOCKFREE 0
#define FALLSPEED 2 //Has to be a factor of bufferheigth.


#define STARTX gameWidth/2
#define STARTY 10

extern int BUTTON_1;
extern int BUTTON_2;
extern int BUTTON_3;
extern int BUTTON_4;
// extern int SWITCH_4;
extern uint16_t SCORE;


struct Coordinate;
struct TetrisBlock;

/* Defining Structs Here Because not doing so caused error: dereferencing pointer to incomplete type
Because i was using them in different files and cba this was easy fix */

struct Coordinate {
   int x;
   int y;
};

struct TetrisBlock {
    const char *geometry;
    struct TetrisBlock *next;
    struct TetrisBlock *prev;
    struct Coordinate *position;
    int leftCollision;
    int rightCollision;
    int bottomCollision;
    int id;
};

extern struct TetrisBlock block0;
extern struct TetrisBlock block1;
extern struct TetrisBlock block2;
extern struct TetrisBlock block3;
extern struct Coordinate position;


#endif