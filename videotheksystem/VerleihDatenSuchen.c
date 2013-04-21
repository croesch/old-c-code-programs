/*
 ============================================================================
 Name        : VerleihDatenSuchen.c
 Author      : Christian R?sch
 Created on  : Jun 4, 2011
 Description : Funktion sucht nach einem Verleihdatensatz mit der uebergeben
 Filmnummer in der Verleihdaten-Datei
 Rueckgabe   : Den Datensatz zur Kunden- und Filmnummer
 ============================================================================
 */

#include "Videotheksystem.h"

VerleihDatensatz * VerleihDatenSuchen(KundenNummer* Kundennummer, FilmNummer* Filmnummer) {

	// Container fuer die rueckzugebenen Daten
	VerleihDatensatz * vds = NULL;

	// Oeffnen der Verleihdaten-Datei
	FILE *verleihDaten = DateiOeffnen(verleihDatenDateiAdresse());

	// Signal, ob Datensatz gefunden wurde
	int Ende = 0;
	// Solange Verleihdaten-Datei nicht zu ende gelesen wurde und Ende nicht auf 1 gesetzt wurde
	while (!feof(verleihDaten) && Ende == 0) {
		// Lese Datensatz an aktueller Position
		vds = LeseNaechstenVerleihDatensatz(verleihDaten);

		// Datensatz kann NULL sein, was fehlerhaften Datensatz darstellt
		if (vds != NULL) {
			if (Filmnummer->nummer == vds->filmNummer->nummer && Kundennummer->nummer == vds->kundenNummer->nummer) {
				// Stimmen Daten mit den gesuchten ueberein, setze entsprechendes Signal
				Ende = 1;
			} else {
				// Andernfalls gebe nicht benoetigte Daten frei
				gebeVerleihDatensatzFrei(vds);
			}
		}
	}
	DateiSchliessen(verleihDaten);

	// Gebe Daten zurueck
	return vds;
}
