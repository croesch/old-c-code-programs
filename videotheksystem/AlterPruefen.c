/*
 ============================================================================
 Name        : AlterPruefen.c
 Author      : Christian R?sch
 Created on  : Jun 4, 2011
 Description : Prueft, ob eine Person mit gegebenen Geburtstdatum alt genug fuer
 das gegebene FSK ist.
 Rueckgabe   : Der zurueckgegebene Status zeigt an, ob das Alter hoch genug ist.
 Status 0 entspricht zu geringem Alter
 Status 1 entspricht legitimem Alter
 ============================================================================
 */

#include "Videotheksystem.h"

Status* AlterPruefen(FSK* FSK, Datum* geburtstag) {

	// Status wird mit Wert 0 initialisiert
	Status* status = initialisiereStatus();

	Datum* jetzt = HoleSystemDatum();
	int alter = AlterBerechnen(geburtstag, jetzt);

	if (alter < FSK->fsk) {
		// Alter zu gering
		FehlerMeldungAusgeben("Kunde ist nicht alt genug");
		return status;
	}
	// Alter legitim
	TextAusgeben("Kunde ist %d Jahre alt und darf Film mit FSK %d ausleihen.", alter, FSK->fsk);

	// setze Status auf 'legitimes Alter'
	status->wert = 1;
	return status;
}

