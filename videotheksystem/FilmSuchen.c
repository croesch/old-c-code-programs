/*
 ============================================================================
 Name        : FilmSuchen.c
 Author      : Christian R?sch
 Created on  : Jun 4, 2011
 Description : Sucht einen Film zunaechst anhand des Filmtitels, dann anhand der Filmnummer
 Rueckgabe	 : Gibt die verfuegbare Medienanzahl des gefunden Films zurueck
 ============================================================================
 */

#include "Videotheksystem.h"

VerfuegbareMedienAnzahl* FilmSuchen(FilmDatensatz *zuFuellenderDatensatz) {

	TitelAusgeben("Film suchen");

	FilmNachTitelSuchen();
	return FilmNachFilmNummerSuchen(zuFuellenderDatensatz);
}

