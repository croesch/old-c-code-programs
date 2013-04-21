/*
 ============================================================================
 Name        : funktionen.h
 Author      : Christian Rösch
 Created on  : Jun 15, 2011
 Description : Enthält nützliche Funktionen
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../datentypen.h"

Datum* addiereAusleihDauerZuDatum(Datum * datum, AusleihDauer * dauer);

int berechneDatumsDifferenz(Datum* erstes, Datum* zweites);

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
int leseInteger(char* text, int *offset, int min, int max, char *trenner);

FILE * DateiOeffnen(const char* pfad);

void DateiSchliessen(FILE * datei);

void TextOhneUmbruchAusgeben(const char* meldung, ...);

void TextAusgeben(const char* meldung, ...);

void TitelAusgeben(const char* titel);

/*
 ============================================================================
 Author      : Christian R��sch
 Created on  : Mar 24, 2011
 Description : Prints a debugging message, if the debug mode is switched on
 Parameters  : format: the message to print to the error stream
 arg:    the arguments to put into the formatted message
 ============================================================================
 */
void DebugAusgabe(const char* format, ...);

void FehlerMeldungAusgeben(const char* meldung, ...);

int KundeSuchenNachExtern(KundenDatensatz* kds);

int vergleicheVerleihDatensaetze(VerleihDatensatz* eins, VerleihDatensatz* zwei);

char* teilString(char* text, int von, int anzahl);

char* verleihDatenDateiAdresse();

char* filmDatenDateiAdresse();

void FilmTabellenKopfAusgeben();

void FilmTabellenZeileAusgeben(FilmDatensatz* film, int anzahl);

void TextAuffuellenUndOhneUmbruchAusgeben(char* text, int anzahl, char mit);

void VerleihDatenKopfAusgeben();

void VerleihDatenZeileAusgeben(VerleihDatensatz* ds, char* name, Datum* rueck);

void VerleihDatenFussAusgeben();

void kopiereDatum(Datum* ziel, Datum* quelle);
