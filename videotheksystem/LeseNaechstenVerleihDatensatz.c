/*
 ============================================================================
 Name        : LeseNaechstenVerleihDatensatz.c
 Author      : Johann Deter
 Created on  : Jun 7, 2011
 Description : Liest den Verleihdatensatz an aktueller Dateizeigerposition
 aus Verleihdatendatei.
 Rueckgabe   : Gibt den gelesenen Datensatz zurueck oder NULL, wenn Datensatz
 nicht valide ist (beginnt nicht mit Ziffer oder ist leer).
 ============================================================================
 */

#include "Videotheksystem.h"

VerleihDatensatz * LeseNaechstenVerleihDatensatz(FILE *verleihdatenDatei) {

	// Allokiere Speicher fuer die aktuelle Zeile
	char* zeile = (char*) malloc(sizeof(char) * 60);
	strcpy(zeile, ""); // initialisiere Zeile

	// lese die Zeile ein
	fgets(zeile, 60, verleihdatenDatei);

	// Wenn Zeile leer oder nicht mit Ziffer beginnt, gebe NULL zurueck
	if (strcmp(zeile, "") == 0 || !isdigit(zeile[0])) {
		/*
		 * Am Ende der Datei liest Ubuntu zusätzlich einige Zeichen,
		 * die weder \n,\r noch \0 sind. Mit einem Hex-Editor ist kein Zeichen zu sehen.
		 * Daher blieb uns nur der Test auf eine Ziffer.
		 */
		free(zeile);
		return NULL;
	}

	// initialisiere rueckzugebenden Datensatz
	VerleihDatensatz* daten = initialisiereVerleihDatensatz();
	// Zeiger in der aktuellen Zeile
	int zeiger = 0;

	// Lese Zeile in Datensatz ein
	daten->filmNummer->nummer = leseInteger(zeile, &zeiger, 6, 6, "|");
	daten->kundenNummer->nummer = leseInteger(zeile, &zeiger, 1, 11, "|");

	daten->ausleihDatum->tm_year = leseInteger(zeile, &zeiger, 4, 4, "|");
	daten->ausleihDatum->tm_mon = leseInteger(zeile, &zeiger, 2, 2, "|");
	daten->ausleihDatum->tm_mday = leseInteger(zeile, &zeiger, 2, 2, "|");

	daten->ausleihDauer->dauer = leseInteger(zeile, &zeiger, 1, 11, "|");
	daten->tagesPreis->wert = leseInteger(zeile, &zeiger, 3, 3, "|");
	daten->bezahlterBetrag->betrag = leseInteger(zeile, &zeiger, 1, 11, "|\r\n\0");

	// Gebe Zeile frei und Datensatz zurueck
	free(zeile);
	return daten;
}
