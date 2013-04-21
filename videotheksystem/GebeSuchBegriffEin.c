/*
 ============================================================================
 Name        : GebeSuchBegriffEin.c
 Author      : Johann Deter
 Created on  : Jun 7, 2011
 Description : Laesst den Benutzer einen Suchbegriff eingeben
 Rueckgabe	 : Gibt den eingegeben Suchbegriff zurueck
 ============================================================================
 */

#include "Videotheksystem.h"

SuchBegriff* GebeSuchBegriffEin() {
	SuchBegriff* begriff = initialisiereSuchBegriff();
	TextOhneUmbruchAusgeben("Suchbegriff: ");
	scanf("%s", begriff->begriff);
	return begriff;
}
