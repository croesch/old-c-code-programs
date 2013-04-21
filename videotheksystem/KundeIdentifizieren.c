/*
 ============================================================================
 Name        : KundeIdentifizieren.c
 Author      : Christian R?sch
 Created on  : Jun 4, 2011
 Description : Ueberprueft ob der Kunde in der Kundendatei enthalten ist und identifiziert ihn
 Rueckgabe	 : Gibt den Status zurueck ob Kunde bekannt ist oder nicht
 : Status 0 gibt an, dass Kunde nicht in der Datei enthalten ist und somit unbekannt ist
 : Status 1 gibt an, dass Kunde in der Datei enthalten ist und somit bekannt ist
 ============================================================================
 */

#include "Videotheksystem.h"

Status * KundeIdentifizieren(KundenDatensatz *ZuFuellenderDatensatz) {
	// Wenn der zu fuellende Datensatz noch nicht initialisiert wurde, initialisiere
	if (ZuFuellenderDatensatz == NULL) {
		ZuFuellenderDatensatz = initialisiereKundenDatensatz();
	}

	Status * status = initialisiereStatus();
	int Ende = 0;
	// Solange Ende = 0 ist, bearbeite..
	while (Ende == 0) {
		LeereKundendatensatz(ZuFuellenderDatensatz);
		// Eingeben der Kundenidentifikation
		KundenIdentifikation* ID = KundenIdentifikationEingeben();
		// Wenn eingegebene Kundennummer nicht 0 ist, dann wird sie in den zu fuellenden
		// Datensatz kopiert
		if (ID->kundenNummer->nummer != 0) {
			ZuFuellenderDatensatz->kundenNummer->nummer = ID->kundenNummer->nummer;
		} else {
			// Wen Kundenname nicht leer ist, dann kopiere ihn in den zu fuellenden Datensatz
			if (strcmp(ID->kundenName->name, "") != 0) {
				strcpy(ZuFuellenderDatensatz->kundenName->name, ID->kundenName->name);
				if (ID->geb != NULL) {
					kopiereDatum(ZuFuellenderDatensatz->geburtstag, ID->geb);
				}
				if (ID->adresse != NULL) {
					ZuFuellenderDatensatz->adresse = ID->adresse;
				}
			} else {
				Ende = 1;
			}
		}
		gebeKundenIdentifikationFrei(ID);
		if (Ende == 0) {
			// Suchen des Kunden in der Kundendatei
			int Fehlerstatus = KundeSuchenNachExtern(ZuFuellenderDatensatz);
			switch (Fehlerstatus) {
				case 0:
					// Kunde wurde gefunden
					status->wert = 1;
					Ende = 1;
					break;
				case 1:
					// Kunde wurde nicht gefunden
					status->wert = 0;
					FehlerMeldungAusgeben("Kunde nicht gefunden");
					break;
				case 2:
					// Kunde wurde nicht gefunde, weil nicht eindeutig
					status->wert = 0;
					FehlerMeldungAusgeben("Kunde nicht eindeutig");
					break;
			}
		}
	}
	// Wenn Status auf 1 gesetzt ist, dann wurde Kunde gefunden
	// gebe Kundeninformationen ein
	if (status->wert == 1) {
		TextAusgeben("Kunde #%d Name: %s, Geburtstag: %d/%d/%d, Adresse: %s",
				ZuFuellenderDatensatz->kundenNummer->nummer, ZuFuellenderDatensatz->kundenName->name,
				ZuFuellenderDatensatz->geburtstag->tm_year, ZuFuellenderDatensatz->geburtstag->tm_mon,
				ZuFuellenderDatensatz->geburtstag->tm_mday, ZuFuellenderDatensatz->adresse->adresse);
		if (ZuFuellenderDatensatz->stammkunde->stammkunde) {
			TextAusgeben("\tist Stammkunde");
		} else {
			TextAusgeben("\tist kein Stammkunde");
		}
	}
	return status;
}
