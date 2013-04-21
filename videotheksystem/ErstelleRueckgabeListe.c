/*
 ============================================================================
 Name        : ErstelleRueckgabeListe.c
 Author      : Johann Deter
 Created on  : Jun 7, 2011
 Description : Leert die vorhandene Rueckgabeliste und initialisiert sie von neuem
 ============================================================================
 */

#include "Videotheksystem.h"

void LeereRueckgabeListe() {
	if (rueckgabeListe != NULL) {
		gebeRueckgabeListeFrei(rueckgabeListe);
	}
	rueckgabeListe = NULL;
}
