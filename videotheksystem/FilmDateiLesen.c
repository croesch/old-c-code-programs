/*
 ============================================================================
 Name        : FilmDateiLesen.c
 Author      : Christian R?sch
 Created on  : Jun 4, 2011
 Description : Funktion ließt den naechsten Filmsatensatz aus der Filmdatei
 und speichert diesen in einer verketteten Liste
 ============================================================================
 */

#include "Videotheksystem.h"

void FilmDateiLesen(FILE *filmdatenDatei, FilmDatensatz* beginn) {
	FilmDatensatz* aktuell = beginn;

	// Lese, wenn Dateizeiger noch nicht auf das Ende der Datei zeigt
	if (!feof(filmdatenDatei)) {
		// Lese den naechsten Filmdatensatz ein
		LeseNaechstenFilmDatensatz(filmdatenDatei, aktuell);
		gebeFilmDatensatzFrei(aktuell->naechster);
		// Haenge den gelesenen Filmdatensatz an eine verkettete Liste
		aktuell->naechster = initialisiereFilmDatensatz();
		aktuell = aktuell->naechster;
	}
}
