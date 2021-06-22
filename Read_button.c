/*
 * CFile1.c
 *
 * Created: 16/06/2021 18:02:15
 *  Author: dakak
 */ 
#include <avr/io.h>
#include <stdbool.h>
#include "Read_button.h"
#include "Config.h"
#include "Tetris.h"
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