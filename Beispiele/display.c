/* =================================================================
Gruppe 9 - Spannungsregeler

Dateiname:             display.c

Autoren:               Joshua Hermann (Hochschule Heilbronn)
                       Max Milke (Hochschule Heilbronn)

Version:               1.1

Hardware:              Atmel Atmega 328p, simuliert in SiumulIDE 0.4.13-SR5
Software:              Entwicklungsumgebung: Atmel-/MicrochipStudio 7.0.2542
                                             Visual Studio Code 1.51.1
                       C-Compiler: avr-gcc

Funktion:              Funktionen für die Displayausgabe
                       
Header-Files:          "display.h"          
====================================================================
*/

#include "display.h"
#include "lcd_lib_de.h"
#include "pwm.h"
#include "adc.h"
#include <string.h>
#include <math.h>

#define ASC_NULL 0x30

//https://www.geeksforgeeks.org/convert-floating-point-number-string/ --------------------------------------
// Converts a floating-point/double number to a string
void ftoa(float n, char *res, int afterpoint)
{

	// Extract integer part
	int ipart = (int)n;

	// Extract floating part
	float fpart = n - (float)ipart;

	// convert integer part to string
	int i = intToStr(ipart, res, 0);

	// check for display option after point
	if (afterpoint != 0)
	{
		res[i] = '.'; // add dot

		// Get the value of fraction part upto given no.
		// of points after dot. The third parameter
		// is needed to handle cases like 233.007
		fpart = fpart * pow(10, afterpoint);

		intToStr((int)fpart, res + i + 1, afterpoint);
	}
}

// Reverses a string 'str' of length 'len'
void reverse(char *str, int len)
{
	int i = 0, j = len - 1, temp;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

int intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x)
	{
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}

	// If number of digits required is more, then
	// add 0s at the beginning
	while (i < d)
		str[i++] = '0';

	reverse(str, i);
	str[i] = '\0';
	return i;
}
//-------------------------------------------------------------------------------------------------------

void initDisplay(void) // Start der Funktion
{
	lcd_init();		 // Initialisierungsroutine aus der lcd_lib
	_delay_ms(2000); // Wartezeit nach Initialisierung
}

void showAdcValues(void)
{
	lcd_clearline(1);

	char V_str[5];
	char A_str[5];

	ftoa(adcValueV, V_str, 2);
	ftoa(adcValueA, A_str, 2);

	lcd_gotoxy(1, 0); // Cursor auf 2. Zeile, 1. Zeichen
	lcd_putstr("V:"); // Ausgabe Festtext

	lcd_gotoxy(1, 2);  // Cursor auf 2. Zeile, 1. Zeichen
	lcd_putstr(V_str); // Ausgabe Voltage

	lcd_gotoxy(1, 7);  // Cursor auf 2. Zeile, 1. Zeichen
	lcd_putstr(" A:"); // Ausgabe Festtext

	lcd_gotoxy(1, 11); // Cursor auf 2. Zeile, 1. Zeichen
	lcd_putstr(A_str); // Ausgabe Voltage

	_delay_ms(200); // kommt noch weg
}

void showBootDisplay(void)
{
	lcd_gotoxy(0, 0);			   // Cursor auf 1. Zeile, 1. Zeichen
	lcd_putstr("uC-Technik - G9"); // Ausgabe Festtext: 16 Zeichen

	lcd_gotoxy(1, 0);			   // Cursor auf 2. Zeile, 1. Zeichen
	lcd_putstr("Spannungsregler"); // Ausgabe Festtext: 16 Zeichen
	_delay_ms(2000);

} // Ende der Funktion

void showPWMAdjustDisplay(void)
{
	char a[2];

	int fpart = (dutyCycle / 255.) * pow(10, 2);

	intToStr((int)fpart, a, 2);

	lcd_gotoxy(0, 0);			   // Cursor auf 1. Zeile, 1. Zeichen
	lcd_putstr("PWM   2:++ 3:--"); // Ausgabe Festtext: 16 Zeichen

	if (dutyCycle >= 255)
	{
		lcd_gotoxy(1, 0);			   // Cursor auf 2. Zeile, 1. Zeichen
		lcd_putstr("DutyCycle: 1.00"); // Ausgabe Festtext: 16 Zeichen
		return;
	}

	lcd_gotoxy(1, 0);			 // Cursor auf 2. Zeile, 1. Zeichen
	lcd_putstr("DutyCycle: 0."); // Ausgabe Festtext: 16 Zeichen //0 fuer edge case von 1 decrementieren

	lcd_gotoxy(1, 13); // Cursor auf 2. Zeile, 1. Zeichen
	lcd_putstr(a);	   // Ausgabe Festtext: 16 Zeichen
}

void showBuckDisplay(void)
{
	lcd_gotoxy(0, 0);			   // Cursor auf 1. Zeile, 1. Zeichen
	lcd_putstr("Buck   1:Toggle"); // Ausgabe Festtext: 16 Zeichen
}

void showBoostDisplay(void)
{
	lcd_gotoxy(0, 0);			   // Cursor auf 1. Zeile, 1. Zeichen
	lcd_putstr("Boost  1:Toggle"); // Ausgabe Festtext: 16 Zeichen
}

void showLDODisplay(void)
{
	lcd_gotoxy(0, 0);			   // Cursor auf 1. Zeile, 1. Zeichen
	lcd_putstr("LDO    1:Toggle"); // Ausgabe Festtext: 16 Zeichen
}

void showMainMenuDisplay(void)
{
	lcd_gotoxy(0, 0);			   // Cursor auf 1. Zeile, 1. Zeichen
	lcd_putstr("1:LDO  2:Boost "); // Ausgabe Festtext: 16 Zeichen

	lcd_gotoxy(1, 0);			   // Cursor auf 2. Zeile, 1. Zeichen
	lcd_putstr("3:Buck         "); // Ausgabe Festtext: 16 Zeichen
}
