/*
 ============================================================================
 Name        : VerleihPruefen.c
 Author      : Christian R?sch
 Created on  : Jun 4, 2011
 Description : Funktion prueft wie viele Medien einer Filmnummer verliehen sind
 Rueckgabe   : Die Anzahl verliehener Filme der gegebenen Filmnummer
 ============================================================================
 */

#include <stdio.h>
#include "Videotheksystem.h"

MedienAnzahl* VerleihPruefen(FilmNummer* FilmNummer) {
	// initialisiere Container, um verfuegbare Anzahl rueckgeben zu koennen
	MedienAnzahl* anzahl = initialisiereMedienAnzahl();

	// Oeffne entsprechende Datei
	FILE *verleihdatenDatei = DateiOeffnen(verleihDatenDateiAdresse());
	// Durchsuche Datei nach Vorkommen der Filmnummer
	while (!feof(verleihdatenDatei)) {
		// Lese Verleihdatensatz an aktueller Position
		VerleihDatensatz * ds = LeseNaechstenVerleihDatensatz(verleihdatenDatei);

		// Datensatz kann NULL sein, was fehlerhaften Datensatz anzeigt
		if (ds != NULL) {
			/*
			 * Wenn Filmnummer in Verleihdatensatz enthalen ist,
			 * dann erhoehe Anzahl der verliehenen Medien
			 */
			if (FilmNummer->nummer == ds->filmNummer->nummer) {
				anzahl->anz += 1;
			}
			// gelesenen Datensatz freigeben
			gebeVerleihDatensatzFrei(ds);
		}
	}
	// Verleihdaten-Datei schliessen
	DateiSchliessen(verleihdatenDatei);

	// gefundene Anzahl zurueckgeben
	return anzahl;
}

