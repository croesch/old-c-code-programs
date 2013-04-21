/*
 ============================================================================
 Name        : AusleihVorgangBuchen.c
 Author      : Johann Deter
 Created on  : Jun 7, 2011
 Description : Laesst den Benutzer eine Bestaetigung eingeben
 Rueckgabe	 : Gibt die eingegebe Bestaetigung zurueck
 ============================================================================
 */

#include "Videotheksystem.h"

Bestaetigung* holeBestaetigung() {
	Bestaetigung* b = initialisiereBestaetigung();
	TextOhneUmbruchAusgeben("Bestaetigung (j/n): ");
	// Einlesen der Bestaetigung
	scanf("%s", b->bestaetigung);

	// Wenn eingebebe Bestaetigung 'nein' ist, dann wert auf 0 setzen
	if (strcmp(b->bestaetigung, "n") == 0
			|| strcmp(b->bestaetigung, "N") == 0
			|| strcmp(b->bestaetigung, "nein") == 0
			|| strcmp(b->bestaetigung, "Nein") == 0
			|| strcmp(b->bestaetigung, "NEIN") == 0
			|| strcmp(b->bestaetigung, "no") == 0
			|| strcmp(b->bestaetigung, "No") == 0
			|| strcmp(b->bestaetigung, "NO") == 0) {
		b->wert = 0;
	} else if (strcmp(b->bestaetigung, "j") == 0 // Wenn Bestaetigung 'ja' ist, dann wert auf 1 setzen
			|| strcmp(b->bestaetigung, "J") == 0
			|| strcmp(b->bestaetigung, "ja") == 0
			|| strcmp(b->bestaetigung, "Ja") == 0
			|| strcmp(b->bestaetigung, "JA") == 0
			|| strcmp(b->bestaetigung, "y") == 0
			|| strcmp(b->bestaetigung, "Y") == 0
			|| strcmp(b->bestaetigung, "yes") == 0
			|| strcmp(b->bestaetigung, "Yes") == 0
			|| strcmp(b->bestaetigung, "YES") == 0) {
		b->wert = 1;
	} else {
		// Wenn etwas falsches eingegeben wurde, dann nochmal eingeben lassen
		FehlerMeldungAusgeben("Bestaetigung falsch, erneut eingeben: ");
		b = holeBestaetigung();
	}

	return b;
}
