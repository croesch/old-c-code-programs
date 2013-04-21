/*
 ============================================================================
 Name        : AusleihVorgangBuchen.c
 Author      : Johann Deter
 Created on  : Jun 7, 2011
 Description : Laesst den Benutzer eine Filmnummer eingeben
 Rueckgabe	 : gibt die eingegeben Filmnummer zurueck
 ============================================================================
 */

#include "Videotheksystem.h"

FilmNummer* FilmNummerEingeben() {
	FilmNummer* nummer = initialisiereFilmNummer();

	TextOhneUmbruchAusgeben("FilmNummer: ");
	scanf("%d", &nummer->nummer);

	return nummer;
}
