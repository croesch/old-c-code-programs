/*
 ============================================================================
 Name        : LeseNaechstenFilmDatensatz.c
 Author      : Johann Deter
 Created on  : Jun 7, 2011
 Description : Liest den Filmdatensatz an aktueller Dateizeigerposition
 aus Filmdatei und fuellt den uebergebenen Datensatz.
 ============================================================================
 */

#include "Videotheksystem.h"

/**
 * Leert Titel, Kommentar und Beschreibung des Filmdatensatzes und initialisiert
 * diese neu.
 */
static void bereinigeDaten(FilmDatensatz* daten) {
	gebeFilmTitelFrei(daten->filmTitel);
	gebeBeschreibungFrei(daten->beschreibung);
	gebeKommentarFrei(daten->kommentar);

	daten->filmTitel = initialisiereFilmTitel();
	daten->beschreibung = initialisiereBeschreibung();
	daten->kommentar = initialisiereKommentar();

	strcpy(daten->filmTitel->titel, "");
	strcpy(daten->beschreibung->beschreibung, "");
	strcpy(daten->kommentar->kommentar, "");
}

void LeseNaechstenFilmDatensatz(FILE *filmdatenDatei, FilmDatensatz* daten) {

	// Titel, Beschreibung und Kommentar bereinigen
	bereinigeDaten(daten);

	// Speicher fuer Zeile beantragen
	char* zeile = (char*) malloc(sizeof(char) * 500);
	strcpy(zeile, ""); // initialisiere Zeile mit leerem Wert

	// Lese Zeile ein
	fgets(zeile, 500, filmdatenDatei);

	// Zeiger in der gelesenen Zeile
	int zeiger = 0;

	// Lese erste Daten ein
	daten->filmNummer->nummer = leseInteger(zeile, &zeiger, 6, 6, " ");
	daten->medienAnzahl->anz = leseInteger(zeile, &zeiger, 2, 2, " ");
	daten->tagesPreis->wert = leseInteger(zeile, &zeiger, 3, 3, " ");
	daten->fsk->fsk = leseInteger(zeile, &zeiger, 2, 2, " ");
	daten->filmDauer->dauer = leseInteger(zeile, &zeiger, 3, 3, " ");

	// Position der Beschreibung
	int beschreibungsPos = 0;
	// Position des Kommentares
	int kommentarPos = 0;
	// Durchlaufe die Zeile und suche nach Kommentar und Beschreibung.
	int i;
	for (i = 21; zeile[i] != '\0' && zeile[i] != '\n' && zeile[i] != '\r'; ++i) {
		// Wenn ': ' gefunden, setze Beschreibungsposition auf Zeichen danach.
		if (zeile[i] == ':' && zeile[i + 1] == ' ') {
			beschreibungsPos = i + 2;
		}
		// Wenn '>>' gefunden, setze Kommentarposition auf Zeichen danach.
		if (zeile[i] == '>' && zeile[i + 1] == '>') {
			kommentarPos = i + 2;
		}
	}

	if (kommentarPos > 0) {
		// Wenn Kommentar enthalten, speichere diesen im Datensatz
		free(daten->kommentar->kommentar);
		daten->kommentar->kommentar = teilString(zeile, kommentarPos, i - kommentarPos);
	}
	free(daten->filmTitel->titel);
	if (beschreibungsPos > 0) {
		// Wenn Beschreibung vorhanden, unterscheide, ob Kommentar enthalten
		free(daten->beschreibung->beschreibung);
		if (kommentarPos > 0) {
			// Speichere Beschreibung im Datensatz
			daten->beschreibung->beschreibung
					= teilString(zeile, beschreibungsPos, kommentarPos - 2 - beschreibungsPos);
		} else {
			// Speichere Beschreibung im Datensatz
			daten->beschreibung->beschreibung = teilString(zeile, beschreibungsPos, i - beschreibungsPos);
		}
		// Speichere Titel bis zur Beschreibung ab
		daten->filmTitel->titel = teilString(zeile, 21, beschreibungsPos - 2 - 21);
	} else {
		// Wenn keine Beschreibung vorhanden, unterscheide, ob Kommentar vorhanden
		if (kommentarPos > 0) {
			// Speichere Titel im Datensatz
			daten->filmTitel->titel = teilString(zeile, 21, kommentarPos - 2 - 21);
		} else {
			// Speichere Titel im Datensatz
			daten->filmTitel->titel = teilString(zeile, 21, i - 21);
		}
	}

	// Gebe gelesene Zeile wieder frei
	free(zeile);
}
