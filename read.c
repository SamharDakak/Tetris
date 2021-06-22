/*
 * CFile1.c
 *
 * Created: 21/06/2021 17:09:12
 *  Author: dakak
 */ 
#include "read.h"
#include <avr/io.h>
#include <util/delay.h>

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
 
 long bdelay = 0;
void initTaster(void)
{
	DDRD = DDRD & 0xF0;             // Port B auf Eingabe schalten
	PORTD |= 0x0F;                  // Pullup-Rs eingeschaltet
	_delay_ms(10);                  // Wartezeit Umstellung Hardware-Signal
}

int readBut()
{
	if (bdelay > millis())
	{
		return 0;
	}

	// Einlesen der 4 Tastensignale
	sw1_neu = (PIND & (1 << PD0));
	sw2_neu = (PIND & (1 << PD1));
	sw3_neu = (PIND & (1 << PD2));
	sw4_neu = (PIND & (1 << PD3));
	
	// Auswerten der Flanken beim Druecken
	
	if ((sw1_neu==0)&(sw1_alt==1))  // wenn Taste 1 soeben gedrueckt wurde:
	sw1_slope = 1;              //    Flankenbit Taste 1 setzen
	
	if ((sw2_neu==0)&(sw2_alt==1))  // wenn Taste 2 eben gedrueckt wurde:
	sw2_slope = 1;              //    Flankenbit Taste 2 setzen
	
	if ((sw3_neu==0)&(sw3_alt==1))  // wenn Taste 3 eben gedrueckt wurde:
	sw3_slope = 1;              //    Flankenbit Taste 3 setzen
	
	if ((sw4_neu==0)&(sw4_alt==1))  // wenn Taste 4 eben gedrueckt wurde:
	sw4_slope = 1;              //    Flankenbit Taste 4 setzen
	
	// Zwischenspeichern aktuelle Tastenwerte
	
	sw1_alt = sw1_neu;              // aktuelle Tastenwerte speichern
	sw2_alt = sw2_neu;              //    in Variable fuer alte Werte
	sw3_alt = sw3_neu;
	sw4_alt = sw4_neu;
}