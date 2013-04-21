/*
 ============================================================================
 Name        : HoleSystemDatum.c
 Author      : Johann Deter
 Created on  : Jun 7, 2011
 Description : Holt das Systemdatum
 Rueckgabe	 : Gibt das Systemdatum zurueck
 ============================================================================
 */

#include "Videotheksystem.h"
#include <time.h>

Datum* HoleSystemDatum() {

	time_t lt = time(NULL);
	Datum* d = (Datum*) localtime(&lt);
	d->tm_year += 1900; // Jahr zaehlt intern ab 1900
	d->tm_mon += 1; // Monat fängt intern bei 0 an

	return d;
}
