/*
 * IncFile2.h
 *
 * Created: 21/06/2021 17:09:04
 *  Author: dakak
 */ 

#include <stdbool.h>


#ifndef read_H_
#define read_H_

 extern bool sw1_neu;               // Bitspeicher fuer Taste 1
 extern bool sw2_neu;               // Bitspeicher fuer Taste 2
 extern bool sw3_neu;               // Bitspeicher fuer Taste 3
 extern bool sw4_neu;               // Bitspeicher fuer Taste 4

 extern bool sw1_alt;               // alter Wert von Taste 1
 extern bool sw2_alt;               // alter Wert von Taste 2
 extern bool sw3_alt;               // alter Wert von Taste 3
 extern bool sw4_alt;               // alter Wert von Taste 4

 extern bool sw1_slope;             // Flankenspeicher fuer Taste 1
 extern bool sw2_slope;             // Flankenspeicher fuer Taste 2
 extern bool sw3_slope;             // Flankenspeicher fuer Taste 3
 extern bool sw4_slope;             // Flankenspeicher fuer Taste 4
 extern long bdelay;
int readBut();
void initTaster(void);

#endif /* INCFILE2_H_ */