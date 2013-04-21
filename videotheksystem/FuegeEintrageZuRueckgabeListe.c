/*
 ============================================================================
 Name        : FuegeEintragZuRueckgabeListe.c
 Author      : Johann Deter
 Created on  : Jun 7, 2011
 Description : Fuegt einen Eintrag zur Rueckgabeliste hinzu
 ============================================================================
 */

#include "Videotheksystem.h"

void FuegeEintragZuRueckgabeListe(Datum * ausleihDatum, FilmNummer* Filmnummer) {

	RueckgabeListe *eintrag;

	// Wenn die Rueckgabeliste noch nicht initialisiert wurde, initialisiere Rueckgabeliste
	if (rueckgabeListe == NULL) {
		rueckgabeListe = initialisiereRueckgabeListe();
		eintrag = rueckgabeListe;
	} else {
		RueckgabeListe *neu = initialisiereRueckgabeListe();
		eintrag = rueckgabeListe;

		// Gehe ans Ende der Verketteten Liste
		while (eintrag->naechster != NULL) {
			eintrag = eintrag->naechster;
		}
		eintrag->naechster = neu;
		eintrag = eintrag->naechster;
	}

	// Schreibe Werte in neuen Datensatz
	eintrag->filmNummer->nummer = Filmnummer->nummer;
	kopiereDatum(eintrag->ausleihDatum, ausleihDatum);
}
