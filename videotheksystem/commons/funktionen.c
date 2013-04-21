/*
 ============================================================================
 Name        : funktionen.h
 Author      : Christian Roesch
 Created on  : Jun 15, 2011
 Description : Enthaelt nützliche Funktionen
 ============================================================================
 */

#include <time.h>
#include <stdarg.h>
#include "KundenVerwaltung.h"
#include "funktionen.h"

#define DEBUG 0

/*
 * Addiert die gewünschte Ausleihdauer zum aktuellen Datum.
 * Berechnet somit das Datum der Rueckgabe.
 *
 * @param datum: Datum zu dem die Ausleihdauer hinzuaddiert wird
 * @param dauer: Gewuenschte Ausleihdauer
 *
 * @return neues Datum (Rueckgabedatum)
 */
Datum* addiereAusleihDauerZuDatum(Datum * datum, AusleihDauer * dauer) {

	Datum* erg = initialisiereDatum();
	kopiereDatum(erg, datum);
	erg->tm_year -= 1900;
	erg->tm_mon -= 1;
	erg->tm_mday += dauer->dauer;
	mktime((struct tm*) erg);

	// korrigiere Korrektur
	erg->tm_year += 1900;
	erg->tm_mon += 1;
	return erg;
}

/*
 * Berechnet die Differenz zweier Daten in Tagen.
 *
 * @param erstes: Das erste Datum (zeitlich gesehen)
 * @param zweites: Das zweite Datum (zeitlich gesehen)
 *
 * @return Differenz in Tagen
 */
int berechneDatumsDifferenz(Datum* erstes, Datum* zweites) {
	// kopiere erstes Datum, um Manipulationen durchfuehren zu koennen
	Datum * _eins = initialisiereDatum();
	kopiereDatum(_eins, erstes);

	// kopiere zweites Datum, um Manipulationen durchfuehren zu koennen
	Datum * _zwei= initialisiereDatum();
	kopiereDatum(_zwei, zweites);

	// WICHTIG: Bringe Datum in 'maschinen-Form', sonst haben manche Plattformen Probleme
	_eins->tm_year -= 1900;
	_eins->tm_mon -= 1;
	_zwei->tm_year -= 1900;
	_zwei->tm_mon -= 1;

	// Berechne Differenz in Sekunden
	int differenz = (int) difftime(timegm(_zwei), timegm(_eins));
	// Berechne Differenz in Tagen
	differenz /= (60 * 60 * 24);

	// Gebe benutzten Speicher wieder frei
	gebeDatumFrei(_eins);
	gebeDatumFrei(_zwei);

	return differenz;
}

FILE * DateiOeffnen(const char* pfad) {
	FILE* datei = fopen(pfad, "a+");

	// Setze den Dateizeiger an den Anfang der Datei (fuer Windows)
	fseek(datei, 0, SEEK_SET);
	return datei;
}

void DateiSchliessen(FILE * datei) {
	fclose(datei);
}
void TextOhneUmbruchAusgeben(const char* meldung, ...) {
	va_list args;
	va_start(args, meldung);
	vfprintf(stdout, meldung, args);
	va_end(args);
}

void TextAusgeben(const char* meldung, ...) {
	va_list args;
	va_start(args, meldung);
	vfprintf(stdout, meldung, args);
	va_end(args);
	fprintf(stdout, "\n");
}

void TitelAusgeben(const char* titel) {
	printf("- %s", titel);
	if (strlen(titel) < 30) {
		printf(" ");
		int i;
		for (i = strlen(titel); i < 30; ++i) {
			printf("-");
		}
	}
	printf("\n");
}

/*
 ============================================================================
 Author      : Christian R��sch
 Created on  : Mar 24, 2011
 Description : Prints a debugging message, if the debug mode is switched on
 Parameters  : format: the message to print to the error stream
 arg:    the arguments to put into the formatted message
 ============================================================================
 */
void DebugAusgabe(const char* format, ...) {
	if (DEBUG) {
		va_list args;
		fprintf(stdout, "DEBUG: ");
		va_start(args, format);
		vfprintf(stdout, format, args);
		va_end(args);
		fprintf(stdout, "\n");
	}
}

void FehlerMeldungAusgeben(const char* meldung, ...) {
	va_list args;
	fprintf(stderr, "FEHLER: ");
	va_start(args, meldung);
	vfprintf(stderr, meldung, args);
	va_end(args);
	fprintf(stderr, "\n");
}

/*
 ============================================================================
 Author      : Christian R��sch
 Created on  : Apr 7, 2011
 Description : Fetches an positive integer value from a given text at the given offset.
 Ensures that the integer is at least 'min' characters wide and maximum
 'max' characters wide.
 Parameters  : text the text to read the integer from
 offset the offset in the text at which the integer is located
 min the minimum wide of the integer to read
 max the maximum wide of the integer to read
 Returns	 : -1 if the given arguments a invalid
 -2 if the integer at the given position is too short
 -3 if the integer contains characters that are no numbers
 -4 if the integer at the given position is too long
 n the integer that has been successfully read
 ============================================================================
 */
int leseInteger(char* text, int *offset, int min, int max, char *trenner) {

	if (min > max || max < 0) {
		DebugAusgabe("falsche Argumente: min=%d, max=%d", min, max);
		return -1; // falsche Argumente
	}

	int nummer = 0;

	int i;
	for (i = *offset; i < *offset + max; ++i) {
		//		if (isEndOfColumnChar(text[i])) {
		if (strchr(trenner, text[i]) != NULL) {
			if (i >= *offset + min) {
				break;
			}
			return -2; // too short
		}
		if (isdigit(text[i])) {
			nummer = nummer * 10 + text[i] - '0';
		} else {
			return -3; // non-digit character contained
		}
	}
	//		if (isEndOfColumnChar(text[i])) {
	if (text[i] == '\0' || strchr(trenner, text[i]) != NULL) {
		*offset = i + 1;
		return nummer;
	}
	return -4; // too long
}

static tKundenDatensatz* initialisiereTKundenDatensatz() {
	tKundenDatensatz* datenSatz = (tKundenDatensatz*) malloc(sizeof(tKundenDatensatz));

	strcpy(datenSatz->Adresse, "");
	strcpy(datenSatz->Geburtstag, "");
	strcpy(datenSatz->KundenName, "");
	datenSatz->KundenNummer = 0;
	datenSatz->Stammkunde = -1;

	return datenSatz;
}

int KundeSuchenNachExtern(KundenDatensatz* kds) {

	tKundenDatensatz* vonExtern = initialisiereTKundenDatensatz();

	vonExtern->KundenNummer = kds->kundenNummer->nummer;

	int status = KundeSuchen(vonExtern);

	strcpy(kds->adresse->adresse, vonExtern->Adresse);
	strcpy(kds->kundenName->name, vonExtern->KundenName);
	kds->stammkunde->stammkunde = vonExtern->Stammkunde;
	int offs = 0;
	kds->geburtstag->tm_year = leseInteger(vonExtern->Geburtstag, &offs, 4, 4, "/");
	kds->geburtstag->tm_mon = leseInteger(vonExtern->Geburtstag, &offs, 2, 2, "/");
	kds->geburtstag->tm_mday = leseInteger(vonExtern->Geburtstag, &offs, 2, 2, "/");

	free(vonExtern);
	return status;
}

int vergleicheVerleihDatensaetze(VerleihDatensatz* eins, VerleihDatensatz* zwei) {
	if (eins->kundenNummer->nummer == zwei->kundenNummer->nummer && eins->filmNummer->nummer
			== zwei->filmNummer->nummer && eins->ausleihDatum->tm_year == zwei->ausleihDatum->tm_year
			&& eins->ausleihDatum->tm_mon == zwei->ausleihDatum->tm_mon && eins->ausleihDatum->tm_mday
			== zwei->ausleihDatum->tm_mday) {
		return 1;
	} else {
		return 0;
	}
}

char* teilString(char* text, int von, int anzahl) {

	char *teil = strndup(text + von, anzahl);

	return teil;

}

char* verleihDatenDateiAdresse() {
	return "data/rental_information.ri1";
}

char* filmDatenDateiAdresse() {
	return "data/FilmDatei.txt";
}

void FilmTabellenKopfAusgeben() {
	TextAusgeben(" Nummer | Anzahl | Preis | FSK | Dauer | Titel / Kommentar / Beschreibung");
	TextAusgeben("--------+--------+-------+-----+-------+---------------------------------");
}

void FilmTabellenZeileAusgeben(FilmDatensatz* film, int anzahl) {
	TextAusgeben("        |   %02d   | %1.2f  |     |  %03d  | %s", anzahl, film->tagesPreis->wert / 100.0,
			film->filmDauer->dauer, film->filmTitel->titel);

	TextAusgeben(" %06d |   von  | EUR / |  %02d |  min  | %s", film->filmNummer->nummer, film->fsk->fsk,
			film->beschreibung->beschreibung);

	TextAusgeben("        |   %02d   |  Tag  |     |       | %s", film->medienAnzahl->anz, film->kommentar->kommentar);

	TextAusgeben("--------+--------+-------+-----+-------+---------------------------------");
}

void VerleihDatenKopfAusgeben() {
	TextAusgeben("------+--------+----------------------+----------+----+----------+-----+-------");
	TextAusgeben("FilmNr|KundenNr|      Kundenname      |AusleihDat|Tage|RueckgabeD|Preis|Bezahlt");
	TextAusgeben("------+--------+----------------------+----------+----+----------+-----+-------");
}

void VerleihDatenZeileAusgeben(VerleihDatensatz* ds, char* name, Datum* rueck) {
	TextAusgeben("%06d|%8d|%22s|%04d/%02d/%02d|%4d|%04d/%02d/%02d| %3d |%7.2f", ds->filmNummer->nummer,
			ds->kundenNummer->nummer, name, ds->ausleihDatum->tm_year, ds->ausleihDatum->tm_mon,
			ds->ausleihDatum->tm_mday, ds->ausleihDauer->dauer, rueck->tm_year, rueck->tm_mon, rueck->tm_mday,
			ds->tagesPreis->wert, ds->bezahlterBetrag->betrag / 100.0);
}

void VerleihDatenFussAusgeben() {
	TextAusgeben("------+--------+----------------------+----------+----+----------+-----+-------");
}

void TextAuffuellenUndOhneUmbruchAusgeben(char* text, int anzahl, char mit) {
	printf("%s", text);
	if (strlen(text) < anzahl) {
		int i;
		for (i = strlen(text); i < anzahl; ++i) {
			printf("%c", mit);
		}
	}
}

void kopiereDatum(Datum* ziel, Datum* quelle) {
	ziel->tm_year = quelle->tm_year;
	ziel->tm_mon = quelle->tm_mon;
	ziel->tm_mday = quelle->tm_mday;
	ziel->tm_isdst = quelle->tm_isdst;
	ziel->tm_hour = quelle->tm_hour;
	ziel->tm_min = quelle->tm_min;
	ziel->tm_sec = quelle->tm_sec;
}
