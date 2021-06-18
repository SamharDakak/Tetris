/*=============================================================================

LCD_LIB_de	Funktionen fuer die LCD-Anzeige des MiniMEXLE
=========================================================

Dateiname: lcd_lib_de.h

Bibliothek fuer das LCD-Display des MiniMexle Boards bzw. optimiert fuer LCD-Display HD44780

Autor: 		Steffen Freihofer (2006)
Adaption: 	Thomas Pospiech (2007, Timing-Probleme geloest)
			G. Gruhler, D. Chilachava (2009, Init Ports und Dokumentation)
			P. Blinzinger (2020, Libary umgebaut fuer SimulIDE, kompatibel mit dem Mexle2020 Board)
			T. Fischer (Clean Code)

Version: 	1.4	vom 07.10.2020

=============================================================================*/

// Deklarationen ==============================================================

//chip deklaration
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

// Festlegung der Quarzfrequenz

#ifndef F_CPU						 // optional definieren
#define F_CPU 12288000UL // MiniMEXLE mit 12,288 MHz Quarz
#endif

// Include von Header-Dateien

#include <avr/io.h>				 // I/O Konfiguration (intern weitere Dateien)
#include <avr/interrupt.h> // globale Interrupts definieren (sei() und cli())
#include <stdint.h>				 // Definition von Typen (int, char, ...)
#include <stdbool.h>			 // Definition von 1-Bit-Variablentypen (bool)
#include <util/delay.h>		 // Definition von Delays (Wartezeiten)

// Port-Bits

#define PIN_EN PD4 // Enable-Signal zum Display: Port D, PD4
#define PIN_RS PD7 // Register-Select zum Display: Port D, PD5

// Makros

#define DDR_DATA DDRD		//Datenrichtungsregister  fuer Datenport zum LCD (Verwendung der Bits 0 bis 3)
#define DDR_CTRL DDRD		//Datenrichtungsregister  fuer Steuerport zum LCD
#define PORT_DATA PORTD // Port ist Datenport zum LCD (Verwendung der Bits 0 bis 3)
#define PORT_CTRL PORTD // Port ist Steuerport zum LCD

// Konstanten

#define CMD_CLR_DIS 0x01	 // Instruction Code fuer LCD: Loeschen des Displays
#define CMD_MOD_4BIT1 0x03 // Instruction Code fuer LCD: erster  Initialisierungswert f�r 4-Bit Ansteuerung
#define CMD_MOD_4BIT2 0x02 // Instruction Code fuer LCD: zweiter Initialisierungswert f�r 4-Bit Ansteuerung
#define CMD_ENB_DIS 0x0C	 // Instruction Code fuer LCD: Aktivieren des Displays
#define CMD_INC_CSR 0x06	 // Instruction Code fuer LCD: Cursor auf "increment mode"
#define CMD_FCT_DIS 0x28	 // Instruction Code fuer LCD: Function Set: Display Mode 2 Zeilen, 5x8 Pixel
#define CMD_NXT_LIN 0x40	 // Instruction Code fuer LCD: Bit6 f�r Ausgabe in naechster Zeile
#define CMD_GOTO_XY 0x80	 // Instruction Code fuer LCD: Goto XY

#define DLY_INIT_LONG 10 // 10ms - lange Zeitdauer bei Init
#define DLY_INIT_SHRT 3	 //  3ms - kurze Zeitdauer bei Init
#define DLY_CMD_LONG 55	 // 55us - lange Zeitdauer nach Steuerbefehl
#define DLY_CMD_SHRT 2	 //  2us - kurze Zeitdauer nach Steuerbefehl

// Funktionsprototypen

void lcd_enable(void);
void lcd_write(unsigned char byte);
void lcd_init(void);
void lcd_putc(unsigned char zeichen);
void lcd_putstr(char *string);
void lcd_gotoxy(unsigned char line, unsigned char pos);
void lcd_clearDisplay(void);
void lcd_clearline(unsigned char line);
void lcd_displayMessage(char *string, unsigned char, unsigned char);
