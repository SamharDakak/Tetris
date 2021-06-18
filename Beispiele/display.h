#ifndef DISPLAY_H_
#define DISPLAY_H_

//Float in String konvertieren
void ftoa(float n, char *res, int afterpoint);

//Kehrt einen String um
void reverse(char *str, int len);

//Integer in String konvertieren
int intToStr(int x, char str[], int d);

//Display Initialisierung
void initDisplay();

// Ausgabe der ADC-Werte
void showAdcValues();

//Bootdisplay anzeigen
void showBootDisplay();

//PWM-Einstllungen anzeigen
void showPWMAdjustDisplay();

//Buck-Display anzeigen
void showBuckDisplay();

//Boost-Display anzeigen
void showBoostDisplay();

//LDO-Display anzeigen
void showLDODisplay();

//Hauptmenu anzeigen
void showMainMenuDisplay();

#endif
