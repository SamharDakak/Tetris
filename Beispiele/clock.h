#include <stdbool.h>

#ifndef _CLOCK_H_
#define _CLOCK_H_

// Konstanten
#define VORTEILER_WERT 60   // Faktor Vorteiler = 60 (Timerticks)
#define HUNDERTSTEL_WERT 10 // Faktor Hundertstel = 10 (1/100 s)
#define ZEHNTEL_WERT 10     // Faktor Zehntel = 10 (1/10 s)

// Variable
extern unsigned char vorteiler;   // Zaehlvariable Vorteiler
extern unsigned char hundertstel; // Zaehlvariable Hundertstel

extern bool timertick; // Bit-Botschaft alle 0,111ms (bei Interrupt)
extern bool takt10ms;  // Bit-Botschaft alle 10ms
extern bool takt100ms; // Bit-Botschaft alle 100ms

// Funktion Clock initialisieren =============================================
void initClock(void);

#endif