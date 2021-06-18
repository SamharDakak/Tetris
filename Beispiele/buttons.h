#include <stdbool.h>

#ifndef BUTTONS_H_
#define BUTTONS_H_

extern bool sw1_new;   // Bitspeicher fuer Taste 1
extern bool sw2_new;   // Bitspeicher fuer Taste 2
extern bool sw3_new;   // Bitspeicher fuer Taste 3
extern bool sw4_new;   // Bitspeicher fuer Taste 4
extern bool sw1_slope; // Flankenspeicher fuer Taste 1
extern bool sw2_slope; // Flankenspeicher fuer Taste 2
extern bool sw3_slope; // Flankenspeicher fuer Taste 3
extern bool sw4_slope; // Flankenspeicher fuer Taste 4
extern bool sw1_old;   // Bitspeicher fuer Taste 1 vorheriger Wert
extern bool sw2_old;   // Bitspeicher fuer Taste 2 vorheriger Wert
extern bool sw3_old;   // Bitspeicher fuer Taste 3 vorheriger Wert
extern bool sw4_old;   // Bitspeicher fuer Taste 4 vorheriger Wert

// Funktion Tasten initialisieren =============================================
void initButtons(void);

// Funktion Tasten einlesen ===================================================
void readButtons(void);

#endif