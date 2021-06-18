/* =================================================================
Gruppe 9 - Spannungsregeler

Dateiname:             clock.c

Autoren:               Joshua Hermann (Hochschule Heilbronn)
                       Max Milke (Hochschule Heilbronn)

Version:               1.1

Hardware:              Atmel Atmega 328p, simuliert in SiumulIDE 0.4.13-SR5
Software:              Entwicklungsumgebung: Atmel-/MicrochipStudio 7.0.2542
                                             Visual Studio Code 1.51.1
                       C-Compiler: avr-gcc

Funktion:              Funktionen für die Steuerungstasten-Erkennung

Header-Files:          "clock.h"          
====================================================================
*/

#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include "clock.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Variable
unsigned char vorteiler = VORTEILER_WERT;     // Zaehlvariable Vorteiler
unsigned char hundertstel = HUNDERTSTEL_WERT; // Zaehlvariable Hundertstel

bool timertick; // Bit-Botschaft alle 0,111ms (bei Interrupt)
bool takt10ms;  // Bit-Botschaft alle 10ms
bool takt100ms; // Bit-Botschaft alle 100ms

// Timer 0 initialisieren
void initClock(void)
{
  TCCR1A = 0;             // Timer 1 auf "Normal Mode" schalten
  TCCR1B |= (1 << CS01);  // mit Prescaler /8 betreiben
  TIMSK1 |= (1 << TOIE0); // Overflow-Interrupt aktivieren
}

// Interrupt-Routine ==========================================================
ISR(TIMER1_OVF_vect)
/* In der Interrupt-Routine sind die Softwareteiler für die Taktbotschaften 
   (10ms, 100ms) realisiert. Die Interrupts stammen von Timer 1 (Interrupt 1)
 
   Verwendete Variable: vorteiler
                        hunderstel
 
   Ausgangsvariable:    takt10ms
                        takt100ms
*/
{
  timertick = 1;      // Botschaft 0,166ms senden
  --vorteiler;        // Vorteiler dekrementieren
  if (vorteiler == 0) // wenn 0 erreicht: 10ms abgelaufen
  {
    vorteiler = VORTEILER_WERT; //    Vorteiler auf Startwert
    takt10ms = 1;               //    Botschaft 10ms senden
    --hundertstel;              //    Hunderstelzähler dekrementieren

    if (hundertstel == 0) // wenn 0 erreicht: 100ms abgelaufen
    {
      hundertstel = HUNDERTSTEL_WERT; // Teiler auf Startwert
      takt100ms = 1;                  //    Botschaft 100ms senden
    }
  }
}