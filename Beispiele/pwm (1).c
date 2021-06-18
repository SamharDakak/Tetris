/* =================================================================
Gruppe 9 - Spannungsregeler

Dateiname:             pwm.c

Autoren:               Joshua Hermann (Hochschule Heilbronn)
                       Max Milke (Hochschule Heilbronn)

Version:               1.1
Hardware:              Atmel Atmega 328p, simuliert in SiumulIDE 0.4.13-SR5
Software:              Entwicklungsumgebung: Atmel-/MicrochipStudio 7.0.2542
                                             Visual Studio Code 1.51.1
                       C-Compiler: avr-gcc

Funktion:              Funktionen für die Steuerung des PWM-Ausgangs
                       
Header-Files:          "pwm.h"          
====================================================================

*/

#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <avr/io.h>

#define step (255 / 100)

float dutyCycle = 99;

void initPWM()
{
  DDRD |= (1 << DD6);
  // PD6 ist jetzt ein Ausgang

  OCR0A = dutyCycle;
  // Dutycycle wird auf 38% gesetzt <= Simulationsauslastung verringern

  TCCR0A |= (1 << COM0A1);
  // in Nichtinvertierenden-Modus schalten

  TCCR0A |= (1 << WGM01) | (1 << WGM00);
  // schnellen PWM Modus aktivieren
}

void startPWM()
{
  TCCR0B |= (1 << CS01);
  //Setzt Vorteiler auf 8 und startet PWM
}
void stopPWM()
{
  TCCR0B &= ~(1 << CS01);
  // stopt PWM
}

void incrementDutyCycle(void)
{
  if (dutyCycle + step > 255) //verhindert dutyCycle > 255
  {
    dutyCycle = 255;
  }
  else
  {
    dutyCycle = dutyCycle + step;
  }
  OCR0A = dutyCycle;
}

void decrementDutyCycle(void)
{
  if (dutyCycle - step < 0) //verhindert dutyCycle < 0
  {
    dutyCycle = 0;
  }
  else
  {
    dutyCycle = dutyCycle - step;
  }
  OCR0A = dutyCycle;
}
