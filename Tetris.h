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

#define maxInUse 3 
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
unsigned long f_cpu =  12288000UL   ;
long delays = 0;
short delay_ = 500;
long bdelay = 0;
short buttondelay = 150;
short btdowndelay = 30;
short btsidedelay = 80;
unsigned char blocktype;
unsigned char blocktypeFutur;
unsigned char blockrotation;
unsigned long startTime;
unsigned long elapsedTime;
bool block[8][18]; //2 extra for rotation

bool pile[8][16];
bool disp[8][16];
bool selectColor = RED ;
bool gameoverFlag = false;
int cnt = 0;
int zaehler=1;
unsigned int score= 0 ;
	const char Nummern[][8] PROGMEM=
	{
		{0B00000000,0B00111110,0B01111111,0B01010001,0B01001001,0B01111111,0B00111110,0B00000000},// 0
		{0B00000000,0B00000001,0B00000001,0B01111111,0B01111111,0B00010001,0B00000001,0B00000000}, //1
		{0B00000000,0B00100011,0B01100111,0B01000101,0B01001001,0B01111001,0B00110001,0B00000000}, // 2
		{0B00000000,0B01000100,0B11000110,0B10010010,0B10010010,0B11111110,0B01101100,0B00000000}, // 3
		{0B00000000,0B00001100,0B00010100,0B00100100,0B01111111,0B01111111,0B00001000,0B00000000},// 4
		{0B00000000,0B01110010,0B01110011,0B01010001,0B01010001,0B01011111,0B01001110,0B00000000},// 5
		{0B00000000,0B00111110,0B01111111,0B01001001,0B01001001,0B01101111,0B00100110,0B00000000},//6
		{0B00000000,0B01100000,0B01100000,0B01000111,0B01011111,0B01111000,0B01100000,0B00000000},// 7
		{0B00000000,0B00110110,0B01111111,0B01001001,0B01001001,0B01111111,0B00110110,0B00000000},// 8
		{0B00000000,0B00110010,0B01111011,0B01001001,0B01001001,0B01111111,0B00111110,0B00000000},//9
		
	};
	const char	blockFutur[][8] PROGMEM=
	{
		{0B00000000,0B00111110,0B01111111,0B01010001,0B01001001,0B01111111,0B00111110,0B00000000},// 0
		{0B00000000,0B00000001,0B00000001,0B01111111,0B01111111,0B00010001,0B00000001,0B00000000}, //1
		{0B00000000,0B00100011,0B01100111,0B01000101,0B01001001,0B01111001,0B00110001,0B00000000}, // 2
		{0B00000000,0B01000100,0B11000110,0B10010010,0B10010010,0B11111110,0B01101100,0B00000000}, // 3
		{0B00000000,0B00001100,0B00010100,0B00100100,0B01111111,0B01111111,0B00001000,0B00000000},// 4
		{0B00000000,0B01110010,0B01110011,0B01010001,0B01010001,0B01011111,0B01001110,0B00000000},// 5
		{0B00000000,0B00111110,0B01111111,0B01001001,0B01001001,0B01101111,0B00100110,0B00000000},//6

		
	};

void futurBlock();
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
void findescore( unsigned int score);
void clearMatrix(void);
void stopISR();
void startISR();
void setISRtimer();
#endif /* INCFILE1_H_ */