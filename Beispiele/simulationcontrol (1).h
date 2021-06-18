#ifndef _SIMULATIONCONTROL_H_
#define _SIMULATIONCONTROL_H_

//Initialisierung der Simulationskontrolle
void initSimulationControl();

//alles abschalten
void turnAllOff();

//nur LDO Schaltung und Auswertung aktivieren
void changeToLDO();

//nur Boost SChaltung und Auswertung aktivieren
void changeToBoost();

//nur Buck Schaltung und Auswertung aktivieren
void changeToBuck();

#endif /*_SIMULATIONCONTROL_H_*/