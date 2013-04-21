/*
 ============================================================================
 Name        : AusleihDauerEingeben.c
 Author      : Johann Deter
 Created on  : Jun 7, 2011
 Description : Laesst den Benutzer die Ausleihdauer eingeben.
 Rueckgabe	 : Gibt die eingegebene Ausleihdauer zurueck
 ============================================================================
 */

#include "Videotheksystem.h"

AusleihDauer * AusleihDauerEingeben() {

	// initialisiere den Container
	AusleihDauer * dauer = initialisiereAusleihDauer();
	// Benutzer informieren
	TextOhneUmbruchAusgeben("Ausleihdauer (in Tagen): ");
	// Wert einlesen
	scanf("%d", &dauer->dauer);

	// gebe eingelesenen Wert zurueck
	return dauer;
}
