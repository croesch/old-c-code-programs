/*
 ============================================================================
 Name        : FilmZurueckgeben.c
 Author      : Christian R?sch
 Created on  : Jun 4, 2011
 Description : Starten den Vorgang um einen Film zurueck zu geben
 ============================================================================
 */

#include "Videotheksystem.h"

void FilmZurueckgeben() {
	FilmListeErstellen();
	// Pruefen ob der Kunde bezahlt hat
	BezahlungPruefen();
}
