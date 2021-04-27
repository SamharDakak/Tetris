/*
 * IncFile1.h
 *
 * Created: 06/04/2021 19:44:16
 *  Author: dakak
 */ 


#ifndef Tetris
#define Tetris

#ifndef F_CPU                   // optional definieren
#define F_CPU   12288000UL        // ATmega 328 mit 12,288 MHz Quarz
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdbool.h>
#include <stdlib.h>
#include <util/atomic.h>
#include <avr/interrupt.h>
#include <time.h>

#define maxInUse 2 
#define SLAVE_SELECT    PORTB &= ~(1 << PB2)
#define SLAVE_DESELECT  PORTB |= (1 << PB2)
#define ISR_FREQ 190  
#define GREEN 0
#define RED 1

#define offREDoffGREEN 0
#define offREDonGREEN 1
#define onREDoffGREEN 2
int colorMode = '3';
int maxInShutdown = RED;
int SetbrightnessValue = 15;
bool sw1_neu = 1;               // Bitspeicher fuer Taste 1
bool sw2_neu = 1;               // Bitspeicher fuer Taste 2
bool sw3_neu = 1;               // Bitspeicher fuer Taste 3
bool sw4_neu = 1;               // Bitspeicher fuer Taste 4

bool sw1_alt = 1;               // alter Wert von Taste 1
bool sw2_alt = 1;               // alter Wert von Taste 2
bool sw3_alt = 1;               // alter Wert von Taste 3
bool sw4_alt = 1;               // alter Wert von Taste 4

bool sw1_slope = 0;             // Flankenspeicher fuer Taste 1
bool sw2_slope = 0;             // Flankenspeicher fuer Taste 2
bool sw3_slope = 0;             // Flankenspeicher fuer Taste 3
bool sw4_slope = 0;             // Flankenspeicher fuer Taste 4
unsigned long f_cpu =  16000000UL  ;
long delays = 0;
short delay_ = 500;
long bdelay = 0;
short buttondelay = 150;
short btdowndelay = 30;
short btsidedelay = 80;
unsigned char blocktype;
unsigned char blockrotation;
unsigned long startTime;
unsigned long elapsedTime;
bool block[8][18]; //2 extra for rotation
bool pile[8][16];
bool disp[8][16];
bool selectColor = RED ;
bool gameoverFlag = false;
int cnt = 0;



volatile unsigned long timer1_millis; 

void initSPI(void);

void initTaster(void);

/*int readButton(void);*/

void writeByte(uint8_t byte);

bool check_overlap();
void rotate();

void check_gameover();

void gameover();
void movedown();

void LEDRefresh();

bool moveleft();

bool moveright();

bool space_below();

bool space_left();

bool space_left2();

bool space_left3();

bool space_right();

bool space_right2();

bool space_right3();

void init_millis(unsigned long f_cpu);
unsigned long millis ();
int readBut();

void maxTransferOne(uint8_t whichMax, uint8_t address, uint8_t value);

void maxTransferSingle( /*uint8_t wich_color*/uint8_t whichMax, uint8_t address, uint8_t value);

void maxTransferAll(uint8_t address, uint8_t value);

void maxShutdown(uint8_t cmd) ;

void setBrightness();

void newBlock();

void updateLED();

void writeWord(uint8_t address, uint8_t data);

void initMatrix(void);

void clearMatrix(void);
void stopISR()  ;
void startISR() ;
void setISRtimer();
#endif /* INCFILE1_H_ */