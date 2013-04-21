/*
 ============================================================================
 Name        : FilmNachFilmNummerSuchen.c
 Author      : Christian R?sch
 Created on  : Jun 4, 2011
 Description : Funktion dient zum Suchen eines Films anhand einer Filmnummer
 Rueckgabe	 : Gibt die verfuegbare Medienanzahl zurueck
 ============================================================================
 */

#include "Videotheksystem.h"

VerfuegbareMedienAnzahl* FilmNachFilmNummerSuchen(FilmDatensatz *ZuFuellenderDatensatz) {

	VerfuegbareMedienAnzahl* anzVerfuegbar = initialisiereVerfuegbareMedienAnzahl();

	// Benutzer gibt die Filmnummer ein
	FilmNummer* nummer = FilmNummerEingeben();
	Status * status = initialisiereStatus();

	FILE *filmdatenDatei = DateiOeffnen(filmDatenDateiAdresse());

	// Solange Dateiende Filmdatei nicht erreicht wurde und Wert des Statuses 0 ist, bearbeite..
	while (!feof(filmdatenDatei) && status->wert == 0) {
		// Lesen der Filmdatei
		FilmDateiLesen(filmdatenDatei, ZuFuellenderDatensatz);
		// Wenn Filmnummer der Filmnummer des zu fuellenden Datensatzes entspricht, bearbeite..
		if (nummer->nummer == ZuFuellenderDatensatz->filmNummer->nummer) {
			// Pruefen ob gesuchter Film vorhanden ist
			MedienAnzahl* verliehen = VerleihPruefen(ZuFuellenderDatensatz->filmNummer);
			anzVerfuegbar->medienAnz = ZuFuellenderDatensatz->medienAnzahl->anz - verliehen->anz;
			gebeMedienAnzahlFrei(verliehen);

			TextAusgeben("Film gefunden:", nummer->nummer);

			FilmTabellenKopfAusgeben();
			FilmTabellenZeileAusgeben(ZuFuellenderDatensatz, anzVerfuegbar->medienAnz);

			// Status setzen, dass Film gefunden wurde
			status->wert = 1;
		}
	}
	DateiSchliessen(filmdatenDatei);
	// Wenn Status auf 0 gesetzt ist, dann wurde Film nicht gefunden
	if (status->wert == 0) {
		// Fehlermeldung, dass Film nicht gefunden wurde
		FehlerMeldungAusgeben("Film mit Filmnummer %d nicht gefunden.", nummer->nummer);
	}
	gebeFilmNummerFrei(nummer);
	gebeStatusFrei(status);

	// Gebe Anzahl der verfuegbaren Filmmedien zurueck
	return anzVerfuegbar;
}
