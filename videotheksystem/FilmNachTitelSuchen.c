/*
 ============================================================================
 Name        : FilmNachTitelSuchen.c
 Author      : Christian R?sch
 Created on  : Jun 4, 2011
 Description : Funktion dient zum Suchen eines Films anhand des Filmtitels
 ============================================================================
 */

#include "Videotheksystem.h"

void FilmNachTitelSuchen() {

	// Benutzer gibt den Suchbegriff ein
	SuchBegriff * suchBegriff = GebeSuchBegriffEin();

	Status * status = initialisiereStatus();
	FILE *filmdatenDatei = DateiOeffnen(filmDatenDateiAdresse());

	// Solange das Ende der Filmdatei nicht erreicht wurde, bearbeite..
	while (!feof(filmdatenDatei)) {
		FilmDatensatz *fds = initialisiereFilmDatensatz();
		// Einlesen des naechsten Filmdatensatzes
		LeseNaechstenFilmDatensatz(filmdatenDatei, fds);
		FilmTitel* titel = fds->filmTitel;
		// wenn der eingegeben Suchbegriff in dem Filmtitel enthalten ist, bearbeite...
		if (strstr(titel->titel, suchBegriff->begriff) != NULL) {
			FilmNummer* nummer = fds->filmNummer;
			VerfuegbareMedienAnzahl* anzVerfuegbar = initialisiereVerfuegbareMedienAnzahl();
			// Prueft wie viele Medien verliehen wurden
			MedienAnzahl* verliehen = VerleihPruefen(nummer);
			anzVerfuegbar->medienAnz = fds->medienAnzahl->anz - verliehen->anz;
			gebeMedienAnzahlFrei(verliehen);

			if (status->wert == 0) {
				FilmTabellenKopfAusgeben();
			}
			FilmTabellenZeileAusgeben(fds, anzVerfuegbar->medienAnz);

			gebeVerfuegbareMedienAnzahlFrei(anzVerfuegbar);

			// Status setzen, dass Film gefunden wurde
			status->wert = 1;
		}

		gebeFilmDatensatzFrei(fds);
	}
	DateiSchliessen(filmdatenDatei);
	// Wenn der Status nicht gesetzt ist, dann wurde kein Film gefunden
	if (status->wert == 0) {
		// Fehlermeldung ausgeben, dass Film nicht gefunden wurde
		FehlerMeldungAusgeben("Keinen Film gefunden");
	}
	gebeStatusFrei(status);
	gebeSuchBegriffFrei(suchBegriff);
}
