/* =================================================================
Gruppe 9 - Spannungsregeler

Dateiname:             buttons.c

Autoren:               Joshua Hermann (Hochschule Heilbronn)
                       Max Milke (Hochschule Heilbronn)

Version:               1.1

Hardware:              Atmel Atmega 328p, simuliert in SiumulIDE 0.4.13-SR5
Software:              Entwicklungsumgebung: Atmel-/MicrochipStudio 7.0.2542
                                             Visual Studio Code 1.51.1
                       C-Compiler: avr-gcc

Funktion:              Funktionen für die Steuerungstasten-Erkennung

Header-Files:          "buttons.h"          
====================================================================
*/

#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

// Festlegung der Quarzfrequenz
#ifndef F_CPU          // optional definieren
#define F_CPU 16000000 // atMega328 mit 16MHz
#endif

#include "buttons.h"
#include <avr/io.h>
#include <util/delay.h>

bool sw1_new = 1;   // Bitspeicher fuer Taste 1
bool sw2_new = 1;   // Bitspeicher fuer Taste 2
bool sw3_new = 1;   // Bitspeicher fuer Taste 3
bool sw4_new = 1;   // Bitspeicher fuer Taste 4
bool sw1_slope = 0; // Flankenspeicher fuer Taste 1
bool sw2_slope = 0; // Flankenspeicher fuer Taste 2
bool sw3_slope = 0; // Flankenspeicher fuer Taste 3
bool sw4_slope = 0; // Flankenspeicher fuer Taste 4
bool sw1_old = 1;   // alter Wert fuer Taste 1
bool sw2_old = 1;   // alter Wert fuer Taste 2
bool sw3_old = 1;   // alter Wert fuer Taste 3
bool sw4_old = 1;   // alter Wert fuer Taste 4

void initButtons(void)
{
  DDRC = DDRC & 0xE1; // Port B auf Eingabe schalten
  PORTC = (1 << PC6) | (1 << PC5) | (1 << PC4) | (1 << PC3);
  _delay_us(10);
}

// Funktion Tasten einlesen ===================================================
void readButtons(void)
{
  // Einlesen der 4 Tastensignale
  sw1_new = (PINC & (1 << PB3));
  sw2_new = (PINC & (1 << PB4));
  sw3_new = (PINC & (1 << PB5));
  sw4_new = (PINC & (1 << PB6));

  // Auswerten der Flanken beim Druecken

  if ((sw1_new == 0) & (sw1_old != 0)) // wenn Taste 1 soeben gedrueckt wurde:
  {
    sw1_slope = 1; //    Flankenbit Taste 1 setzen
  }

  if ((sw2_new == 0) & (sw2_old != 0)) // wenn Taste 2 eben gedrueckt wurde:
  {
    sw2_slope = 1; //    Flankenbit Taste 2 setzen
  }

  if ((sw3_new == 0) & (sw3_old != 0)) // wenn Taste 3 eben gedrueckt wurde:
  {
    sw3_slope = 1; //    Flankenbit Taste 3 setzen
  }

  if ((sw4_new == 0) & (sw4_old != 0)) // wenn Taste 4 eben gedrueckt wurde:
  {
    sw4_slope = 1; //    Flankenbit Taste 4 setzen
  }
  // Zwischenspeichern aktuelle Tastenwerte

  sw1_old = sw1_new; // aktuelle Tastenwerte speichern
  sw2_old = sw2_new; //    in Variable fuer alte Werte
  sw3_old = sw3_new;
  sw4_old = sw4_new;
}