/*
 ============================================================================
 Name        : FuegeEintragZuAusleihliste.c
 Author      : Johann Deter
 Created on  : Jun 7, 2011
 Description : Fuegt einen Eintrag zur Ausleihliste hinzu
 ============================================================================
 */

#include "Videotheksystem.h"

void FuegeEintragZuAusleihliste(Betrag* Betrag, TagesPreis * tagesPreis, FilmNummer* Filmnummer) {

	AusleihListe *eintrag;

	// Wenn Ausleihliste noch nicht initialisiert wurde, dann inititialisiere
	if (ausleihListe == NULL) {
		ausleihListe = initialisiereAusleihListe();
		eintrag = ausleihListe;
	} else {
		AusleihListe *neu = initialisiereAusleihListe();
		eintrag = ausleihListe;
		// Gehe ans Ende der Verketteten Liste
		while (eintrag->naechster != NULL) {
			eintrag = eintrag->naechster;
		}
		eintrag->naechster = neu;
		eintrag = eintrag->naechster;
	}

	// Schreibe Werte in neuen Datensatz
	eintrag->filmNummer->nummer = Filmnummer->nummer;
	eintrag->betrag->betrag = Betrag->betrag;
	eintrag->tagesPreis->wert = tagesPreis->wert;
}
