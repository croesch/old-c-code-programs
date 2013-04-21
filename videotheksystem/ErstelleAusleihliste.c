/*
 ============================================================================
 Name        : AusleihVorgangBuchen.c
 Author      : Johann Deter
 Created on  : Jun 7, 2011
 Description : Leert die vorhandene Ausleihliste und initialisiert sie von neuem
 ============================================================================
 */

#include "Videotheksystem.h"

void LeereAusleihListe() {
	if (ausleihListe != NULL) {
		gebeAusleihListeFrei(ausleihListe);
	}
	ausleihListe = NULL;
}
