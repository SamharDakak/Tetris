#ifndef PWM_H_
#define PWM_H_

extern float dutyCycle; //Dutycycle des PWM-Ausgangssignals

//Initialisierung der PWM Funktion
void initPWM();

//PWM Dutycyle um 0.01 erhöhen
void incrementDutyCycle();

//PWM Dutycylce um 0.01 verringern
void decrementDutyCycle();

//Pwm Signal wird an PIN D6 gestartet
void startPWM();

//PWM Signal an PIN 6 wird gestopt
void stopPWM();

#endif