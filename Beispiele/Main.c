/* =================================================================
Gruppe 9 - Spannungsregeler
 
Dateiname:             main.c
 
Autoren:               Joshua Hermann (Hochschule Heilbronn)
                       Max Milke (Hochschule Heilbronn)
 
Version:               1.1
 
Hardware:              Atmel Atmega 328p, simuliert in SiumulIDE 0.4.13-SR5
Software:              Entwicklungsumgebung: Atmel-/MicrochipStudio 7.0.2542
                                             Visual Studio Code 1.51.1
                       C-Compiler: avr-gcc
 
Funktion:              Stellt die Funktion diverser Spannungsregler da, dazu werden die Teilprogramme eines ADCs
                       eines PWM-Ausgangs, der Ansteuerung eines Displays sowie das Einlesen mehrer Schalter genutzt.
 
Displayanzeige:        Start (fuer 2s):        Betrieb1 (Hauptebene):
                       +----------------+      +----------------+
                       |uC-Technik - G9 |      |1. LDO  2.Boost |
                       |Spannungsregler |      |3. Buck         |
                       +----------------+      +----------------+
                       Betrieb2 (1. Subebene)     Betrieb3 (2. Subebene)
                       +----------------+      +----------------+
                       |LDO    1.Toggle |      |PWM   2:++ 3:-- |
                       |V:x.xx   A:x.xx |      |DutyCycle: 0050 | 
                       +----------------+      +----------------+
 
Tastenfunktionen:      Schalter 1-3 führen in die Subprogramme
                       Schalter 4 bringt einen zurück ins übergeordnete Programm
                       In der ersten Subebene öffent Schalter 1 Subebene 2
                       In Subebene 2 kann mit Schalter 2 & 3 der der Dutycycle verändert werden
 
Header-Files:          <avr/io.h>       
                       <avr/interrupt.h>
                       <util/delay.h>   
                       "adc.h"          
                       "display.h"      
                       "buttons.h"     
                       "pwm.h"          
====================================================================
 
*/
 
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif
 
// Festlegung der Quarzfrequenz
#ifndef F_CPU          // optional definieren
#define F_CPU 16000000 // atMega328 mit 16MHz
#endif
 
// Include von Header-Dateien
#include <avr/io.h>            // Header-Dateien zum ATmega328
#include <avr/interrupt.h>     // Header-Datei fuer Interrupts
#include <util/delay.h>        // Header-Datei fuer Delays
#include "adc.h"               // Header-Datei fuer ADC
#include "display.h"           // Header-Datei fuers Display
#include "buttons.h"           // Header-Datei fuer Buttons
#include "pwm.h"               // Header-Datei fuers PWM
#include "simulationControl.h" //Header-Datei fuer die Simulationssteuerung
#include "clock.h"             //Header-Datei fuer die Clock
 
// Globale Variablen
unsigned int state = 0; //state gibt Menustatus an
unsigned int param = 0; //param gibt Spannungsregler an
 
#define MainMenuCase 0
#define DCDCMenuCase 1
#define PWMMenuCase 2
 
#define LDOCase 1
#define BoostCase 2
#define BuckCase 3
 
//Funktionen deklarieren
void mainMenuOptions(void);
void DCDCOptions(void);
void PWMOptions(void);
 
// Hauptprogramm ========================================
int main(void)
{
  //initialisierungen
  initAdc();               // Initialisierung des AD-Wandlers
  initDisplay();           // Initialisierung des Displays
  initButtons();           // Initialisierung der Buttons
  initPWM();               // Initialisierung des PWM
  initSimulationControl(); // Initialisierung der Simulationssteuerung
  initClock();             // Initialisierung Clock
 
  //Display Start Funktion
  showBootDisplay();
  showMainMenuDisplay();
 
  while (1)
  {
    readButtons();
    switch (state)
    {
    case MainMenuCase:
      mainMenuOptions();
      break;
 
    case DCDCMenuCase:
      startPWM();
      doAdc();
      showAdcValues();
      DCDCOptions();
      break;
 
    case PWMMenuCase:
      PWMOptions();
      break;
    }
    //taster bool wieder ausschalten
    sw1_slope = 0;
    sw2_slope = 0;
    sw3_slope = 0;
    sw4_slope = 0;
  }
}
 
//Tastenfunktionen im Hauptmenu
void mainMenuOptions()
{
  //zum LDO Display
  if (sw1_slope)
  {
    state = DCDCMenuCase;
    param = LDOCase;
    showLDODisplay();
    changeToLDO();
    return;
  }
  //zum Boost Display
  if (sw2_slope)
  {
    state = DCDCMenuCase;
    param = BoostCase;
    showBoostDisplay();
    changeToBoost();
    return;
  }
  //zum Buck Display
  if (sw3_slope)
  {
    state = DCDCMenuCase;
    param = BuckCase;
    showBuckDisplay();
    changeToBuck();
    return;
  }
}
 
//Tastenfunktionen im Spannungsreglermenu
void DCDCOptions()
{
  //zum PWM Einstellungsdisplay
  if (sw1_slope)
  {
    state = PWMMenuCase;
    showPWMAdjustDisplay();
    return;
  }
  //zurueck zum main menu
  if (sw4_slope)
  {
    state = MainMenuCase;
    param = 0;
    showMainMenuDisplay();
    stopPWM();
    turnAllOff();
    //turnAllOff();
    return;
  }
}
 
//Tastenfunktionen im PWM menu
void PWMOptions()
{
  //pwm++
  if (sw2_slope)
  {
    //pwm++
    incrementDutyCycle();
    showPWMAdjustDisplay();
    return;
  }
  //pwm--
  if (sw3_slope)
  {
    decrementDutyCycle();
    showPWMAdjustDisplay();
    return;
  }
  //zurueck zu Spannungsregler menu
  if (sw4_slope)
  {
    state = 1;
    switch (param)
    {
    case LDOCase: //zurueck in LDO menu
    {
      showLDODisplay();
      return;
    }
    case BoostCase: //zurueck in Boost menu
    {
      showBoostDisplay();
      return;
    }
    case BuckCase: //zurueck in Buck menu
    {
      showBuckDisplay();
      return;
    }
    }
  }
  return;
}