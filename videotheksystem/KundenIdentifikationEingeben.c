/*
 ============================================================================
 Name        : KundenIdentifikationEingeben.c
 Author      : Johann Deter
 Created on  : Jun 7, 2011
 Description : Lese die Kundenidentifikation ein
 Rueckgabe   : Die gelesene Kundenidentifikation
 ============================================================================
 */

#include "Videotheksystem.h"

KundenIdentifikation* KundenIdentifikationEingeben() {

	// Initialisiere Speicher fuer Kundenidentifikation
	KundenIdentifikation* kdi = initialisiereKundenIdentifikation();

	// Text fuer Benutzer ausgeben
	TitelAusgeben("Kunden-Identifikation");
	TextOhneUmbruchAusgeben("Kundennummer: ");
	// Lese Kundennummer ein
	scanf("%d", &kdi->kundenNummer->nummer);

	// Wenn Kundennummer 0 oder negativ (ungueltig) lese Name, Geburtsdatum und Adresse ein
	if (kdi->kundenNummer->nummer <= 0) {

		TextOhneUmbruchAusgeben("Kundenname:");
		scanf("%s", kdi->kundenName->name);

		// Einlesen des Geburtsdatums, aufgeteilt in Jahr, Monat und Tag
		TextOhneUmbruchAusgeben("Geburtstagsjahr: ");
		scanf("%d", &kdi->geb->tm_year);

		TextOhneUmbruchAusgeben("Geburtstagsmonat: ");
		scanf("%d", &kdi->geb->tm_mon);

		TextOhneUmbruchAusgeben("Geburtstagstag: ");
		scanf("%d", &kdi->geb->tm_mday);

		TextOhneUmbruchAusgeben("Adresse: ");
		scanf("%s", kdi->adresse->adresse);

	}

	// Gebe gelesene Informationen zurueck
	return kdi;
}
