/* =================================================================
Gruppe 9 - Spannungsregeler

Dateiname:             simulationControl.c

Autoren:               Joshua Hermann (Hochschule Heilbronn)
                       Max Milke (Hochschule Heilbronn)

Version:               1.1

Hardware:              Atmel Atmega 328p, simuliert in SiumulIDE 0.4.13-SR5
Software:              Entwicklungsumgebung: Atmel-/MicrochipStudio 7.0.2542
                                             Visual Studio Code 1.51.1
                       C-Compiler: avr-gcc

Funktion:              Funktionen für die Steuerung der Simulation
                       
Header-Files:          "simulationControl.h"          
====================================================================
*/
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

// Festlegung der Quarzfrequenz
#ifndef F_CPU          // optional definieren
#define F_CPU 16000000 // atMega328 mit 16MHz
#endif

#include <avr/io.h>
#include <util/delay.h> // Header-Datei fuer Delays

void initSimulationControl()
{
  DDRB = 1; // Port B auf Eingabe schalten
  _delay_us(10);
}

void turnAllOff()
{
  PORTB &= ~(1 << PORTB1);
  PORTB &= ~(1 << PORTB2);
  PORTB &= ~(1 << PORTB3);
  PORTB &= ~(1 << PORTB4);
  PORTB &= ~(1 << PORTB5);
}

void changeToLDO()
{
  PORTB |= (1 << PORTB1);
  PORTB |= (1 << PORTB5);
  PORTB &= ~(1 << PORTB4);
  PORTB &= ~(1 << PORTB3);
  PORTB &= ~(1 << PORTB2);
}

void changeToBoost()
{
  PORTB |= (1 << PORTB4);
  PORTB |= (1 << PORTB2);
  PORTB &= ~(1 << PORTB0);
  PORTB &= ~(1 << PORTB3);
  PORTB &= ~(1 << PORTB1);
}

void changeToBuck()
{
  PORTB |= (1 << PORTB4);
  PORTB |= (1 << PORTB3);
  PORTB &= ~(1 << PORTB5);
  PORTB &= ~(1 << PORTB2);
  PORTB &= ~(1 << PORTB1);
}