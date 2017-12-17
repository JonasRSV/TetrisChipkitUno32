#include <stdint.h>
#include <pic32mx.h>
#include "mem.h"

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

uint8_t displayBuffer[byteMemoryPages][byteColumns];

uint8_t spi2PutByte(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
  return SPI2BUF;
}

void initializeOled(void) {
    DISPLAY_CHANGE_TO_COMMAND_MODE;
    quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);
    
    /* Display off command */
    spi2PutByte(0xAE);

    /* Bring Reset low and then high */
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);
    
    /* Send the Set Charge Pump and Set Pre-Charge Period commands */
	spi2PutByte(0x8D);
	spi2PutByte(0x14);
	
	spi2PutByte(0xD9);
	spi2PutByte(0xF1);
    
    /* Turn on VCC and wait 100ms */
	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);
    
    /* Send the commands to invert the display. This puts the display origin
** in the upper left corner.
*/
	spi2PutByte(0xA1);
	spi2PutByte(0xC8);
    
    /* Send the commands to select sequential COM configuration. This makes the
** display memory non-interleaved.
*/
	spi2PutByte(0xDA);
	spi2PutByte(0x20);
    
    /* Send Display On command */
	spi2PutByte(0xAF);
}

void updateOled( void ) {
    int pageIndex, index;

    for (pageIndex = 0; pageIndex < byteMemoryPages; pageIndex++) {
        DISPLAY_CHANGE_TO_COMMAND_MODE;
        
        /* Set Page Address */
        spi2PutByte(0x22); //Set Page command
        spi2PutByte(pageIndex); //Set Page Number

        // Start at left column
        spi2PutByte(0); //Set low Nybble (Dunno what that means)
        spi2PutByte(0x10); //Set high Nybble (Still Dunno what that means)

        DISPLAY_CHANGE_TO_DATA_MODE;

        for (index = 0; index < byteColumns; index++) {
            spi2PutByte(displayBuffer[pageIndex][index]);
        }
    }
}

void setPixel(int x, int y, int activation) {
    int memoryPage = y / byteSize;
    int pixel = y % byteSize;

    uint8_t byte = displayBuffer[memoryPage][x];

    if (activation) {
        byte |= (1 << pixel);
    } else {
        byte &= ~(1 << pixel);
    }

    displayBuffer[memoryPage][x] = byte;
}

int pixelStatus(int x, int y) {
    int memoryPage = y / byteSize;
    int pixel = y % byteSize;

    uint8_t byte = displayBuffer[memoryPage][x];

    return byte & (1 << pixel);
}

int getPixel(int x, int y) {
    return pixelStatus(y, x);
}

void activatePixel(int x, int y) {
    setPixel(y, x, 1);
}

void deactivatePixel(int x, int y) {
    setPixel(y, x, 0);
}



