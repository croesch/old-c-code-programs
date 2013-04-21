/*
 ============================================================================
 Name        : AlterBerechnen.c
 Author      : Johann Deter
 Created on  : Jun 7, 2011
 Description : Berechnet das Alter einer Person anhand des Geburtstdatums und des aktuellen Datums.
 Rueckgabe   : Gibt das berechnete Alter zurueck
 ============================================================================
 */

#include "Videotheksystem.h"

int AlterBerechnen(Datum* geburtstag, Datum* jetzt) {

	// Berechne zuerst die Differenz zwischen den Jahren
	int alter = jetzt->tm_year - geburtstag->tm_year;

	/*
	 * Sollte der Geburtsmonat in diesem Jahr noch kommen, muss das
	 * angenommene Alter um ein Jahr verringert werden.
	 */
	if (jetzt->tm_mon < geburtstag->tm_mon) {
		--alter;
	}
	/*
	 * Entspricht der aktuelle Monat dem Geburtsmonat aber ist der Tag
	 * geringer als der Geburtstag, muss auch hier das Datum verringert werden.
	 */
	if (jetzt->tm_mon == geburtstag->tm_mon && jetzt->tm_mday < geburtstag->tm_mday) {
		--alter;
	}

	return alter;
}
