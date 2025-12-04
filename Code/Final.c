#include <delay.h>
#include <io.h>

//using a dotmatrix[Common Cathode]:
//  A DotMatrix(8x8) is a matrix of LEDs in 8 columns and 8 rows.
//  It has Two sets of pins:
//    set 1 -> A-H : pins of A to H are for rows
//    set 2 -> 1-8 : pins of 1 to 8 are for columns
//  when you try to light an specific LED, first you need to declear its COLUMN status.
//  so, you HIGH(3V-5V-VCC) the column number you want and LOW(0-GND) the other ones to
//  not set the other ones ON on a single row.
//  then, you LOW(0-GND) the row you desire and HIGH(3V-5V-VCC) the otherones so in a column,
//  so there is no other rows on.
//  
//  here is the plan: we have a display_clean function, which sets the columns to LOW and rows
//  to HIGHT
//  DDRB = DDRD = 0xFF
//  ROWS[LOW] : PORTB = 0x00
//  COLUMN[HIGH] : PORTD = 0xFF 
//
//  example :
//  row 3 column 1 and 2:
//  COLUMNS : 0b11000000
//  ROWS    : 0b11011111

void SETUP_DTOAMATRIX(void);
void clean_screen(void);
void show_screen(unsigned char ROWS, unsigned char COLUMNS);
unsigned char reverse(unsigned char b);

void main(void){
//    columns : PORTD
//    ROWS    : PORTB
    SETUP_DTOAMATRIX();
    show_screen(0b10000001, 0b10000000);
//    clean_screen();    
//    PORTB = 0b11011111;
//    PORTD = 0b11000000;
    
}

unsigned char reverse(unsigned char b)
{
    unsigned char r = 0;
    unsigned char i = 0;

    for (i = 0; i < 8; i++) {
        r <<= 1;
        r |= (b & 1);
        b >>= 1;
    }
    return r;
}

void SETUP_DTOAMATRIX(void){
    DDRB = 0xFF;
    DDRD = 0xFF;
    clean_screen();
}

void clean_screen(void){
    PORTB = 0x00;
    PORTD = 0xFF;
}

void show_screen(unsigned char ROWS, unsigned char COLUMNS){
    PORTB = ~reverse(ROWS);
    PORTD = reverse(COLUMNS);
}