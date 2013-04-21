/*
 ============================================================================
 Name        : PreisBerechnen.c
 Author      : Christian R?sch
 Created on  : Jun 4, 2011
 Description : Berechnet den Preis aus Tagespreis und Anzahl an Tagen.
 Rueckgabe   : Betrag, der fuer diesen Tagespreis und Anzahl an Tagen zu zahlen ist.
 ============================================================================
 */

#include "Videotheksystem.h"

Betrag* PreisBerechnen(TagesPreis * preis, AusleihDauer* Dauer) {
	// Initialisierung des zu berechnenden Betrages
	Betrag* b = initialisiereBetrag();

	// Kalkulation des Betrages
	b->betrag = preis->wert * Dauer->dauer;

	// Ausgabe fuer den Benutzer
	double betrag = b->betrag / 100.0;
	TextAusgeben("Fuer %d Tage wird eine Leih-Gebuehr von %02.2f EUR faellig.", Dauer->dauer, betrag);

	// Rueckgabe des berechneten Betrages
	return b;
}

