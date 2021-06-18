/* =================================================================
Gruppe 9 - Spannungsregeler

Dateiname:             adc.c

Autoren:               Joshua Hermann (Hochschule Heilbronn)
                       Max Milke (Hochschule Heilbronn)

Version:               1.1

Hardware:              Atmel Atmega 328p, simuliert in SiumulIDE 0.4.13-SR5
Software:              Entwicklungsumgebung: Atmel-/MicrochipStudio 7.0.2542
                                             Visual Studio Code 1.51.1
                       C-Compiler: avr-gcc

Funktion:              Funktionen für die Auswertung der ADC-Eingänge
                       
Header-Files:          "adc.h"          
====================================================================
*/
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include "adc.h"
#include <avr/io.h>
#include <avr/interrupt.h>

bool flip = 0;
float adcValueV = 0;																  // Spannungswert initialisiert mit 0V
float adcValueA = 0;																  // Stromwert initialisiert mit 0A
float voltageValuesTable[ADCMaxIncrements / SoftenMultiplier];						  // Spannungstabelle mit der Laenge 256 erstellen
float currentValuesTable[ADCMaxIncrements / SoftenMultiplier];						  // Stromtabelle mit der Laenge 256 erstellen
float incrementV = (float)Vmax / ((float)ADCMaxIncrements / (float)SoftenMultiplier); // Schrittweite der Spannung
float incrementA = (float)Amax / ((float)ADCMaxIncrements / (float)SoftenMultiplier); // Schrittweite des Stroms

void initAdc()
{
	// ADMUX &= ~((1 << REFS0) | (1 << REFS1));

	ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) | (1 << ADEN); // Teiler 128; ADC ON

	int index;
	for (index = 0; index < (ADCMaxIncrements / SoftenMultiplier); index++) // Nachschlagtabellen fuer Spannungs und Stromwerte erstellen mit der laenge 256
	{
		voltageValuesTable[index] = index * incrementV; // Spannungswert mit index * Schrittweite definieren
		currentValuesTable[index] = index * incrementA; // Stromwert mit index * Schrittweite definieren
	}
}

void doAdc()
{
	if (!flip) // Abwechselnd Strom und Spannung abfragen
	{

		ADMUX &= ~(1 << MUX0);				 // Stromeingang deaktivieren
		ADMUX |= (1 << MUX1 | (1 << REFS0)); // Spannungseingang aktivieren //
	}
	else if (flip)
	{
		ADMUX &= ~(1 << MUX1);				 //Spannungseingang deaktivieren
		ADMUX |= (1 << MUX0 | (1 << REFS0)); // Stromeingang aktivieren
	}

	int rawAdcValue = 0;   //lokale variable fuer adc initialisieren
	ADCSRA |= (1 << ADSC); // Wandlung starten
	while (ADCSRA & (1 << ADSC))
		; // Ende der Wandlung abwarten

	rawAdcValue = ADCL + (ADCH << 8); // 10-Bit-Wert berechnen
									  // ADCL muss vor ADCH stehen!!
									  // siehe Datenblatt des ATmega 328
	if (!flip)						  // Entscheiden ob Spannungs oder Stromwert gemessen wurde
	{
		adcValueV = voltageValuesTable[(rawAdcValue / SoftenMultiplier)] + (rawAdcValue % SoftenMultiplier * (incrementV / (float)SoftenMultiplier)); // Wert in Spannungstabelle nachschauen
	}
	else if (flip)
	{
		adcValueA = (currentValuesTable[(rawAdcValue / SoftenMultiplier)]) + (rawAdcValue % SoftenMultiplier * (incrementA / (float)SoftenMultiplier)); // Wert in Stromtabelle nachschauen
	}
	flip = !flip; // zwischen Strom und Spannungsmessung wechseln
}
