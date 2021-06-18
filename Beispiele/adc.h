#ifndef ADC_H_
#define ADC_H_

#include <stdbool.h>

#define ADCMaxIncrements 1024 // 8-bit adc
#define Vmax 5                //Maximaler erwarteter Wert am Spannung messenden Eingang
#define SoftenMultiplier 8    // zur Reduktion der Tabellengröße (Speicherplatz sparen)
#define Amax 1                //maximaler erwarteter Wert am Strom messenden Eingang

extern float adcValueV;            // Aktueller Spannungswert
extern float adcValueA;            // Aktueller Stromwert
extern float voltageValuesTable[]; // Mapping von ADC Werten zu Spannungswerten
extern float currentValuesTable[]; // Mapping von ADC Werten zu Stromwerten
extern float incrementV;           // Schrittweite der Spannung
extern float incrementA;           // Schrittweite des Stroms
extern bool flip;

// ADC-Initialisierung
void initAdc();

// ADWandlung
void doAdc();

#endif /* ADC_H_ */