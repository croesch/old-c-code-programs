/*
 ============================================================================
 Name        : LoescheEintragAusVerleihDaten.c
 Author      : Johann Deter
 Created on  : Jun 7, 2011
 Description : Entfernt den gegebenen Datensatz aus der gegebenen Verleihdatendatei.
 ============================================================================
 */

#include "Videotheksystem.h"

void LoescheEintragAusVerleihDaten(FILE *verleihdatenDatei, VerleihDatensatz * vds) {

	// beginn der verketteten Liste initialisieren
	VerleihDatensatz * startVds = initialisiereVerleihDatensatz();
	// Zeiger auf letzten Eintrag setzen
	VerleihDatensatz * aktVds = startVds;
	// Speicher fuer temporaere Datensaetze
	VerleihDatensatz * tempVds;

	// Lese die Verleihdatendatei ein
	while (!feof(verleihdatenDatei)) {
		// Lese naechsten Datensatz
		tempVds = LeseNaechstenVerleihDatensatz(verleihdatenDatei);
		// Wenn Datensatz valide..
		if (tempVds != NULL) {
			if (vergleicheVerleihDatensaetze(tempVds, vds)) {
				/*
				 * Wenn Datensatz dem zu loeschenden entspricht, nicht in Liste aufnehmen
				 * und Speicher wieder freigeben.
				 */
				gebeVerleihDatensatzFrei(tempVds);
			} else {
				/*
				 * Wenn Datensatz nicht zu loeschen ist, fuege ihn in die Liste
				 * zu schreibender Datensaetze
				 */
				aktVds->naechster = tempVds;
				aktVds = aktVds->naechster;
			}
		}
	}

	// Erneut Öffnen zum Schreiben der Datei (ersetze alte Datei)
	DateiSchliessen(verleihdatenDatei);
	verleihdatenDatei = fopen(verleihDatenDateiAdresse(), "w");

	// Schreibe alle gespeicherten Datensaetze
	aktVds = startVds->naechster;
	while (aktVds) {
		FuegeEintragZuVerleihdaten(aktVds, verleihdatenDatei);
		aktVds = aktVds->naechster;
	}

	// Gebe die aufgebaute Liste wieder frei
	gebeVerleihDatensatzFrei(startVds);

	DateiSchliessen(verleihdatenDatei);
}
