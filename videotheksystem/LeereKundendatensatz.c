/*
 ============================================================================
 Name        : LeereKundendatensatz.c
 Author      : Johann Deter
 Created on  : Jun 7, 2011
 Description : Loescht die Werte des Kundendatensatzes OHNE die Referenz zu loeschen
 ============================================================================
 */

#include "Videotheksystem.h"

void LeereKundendatensatz(KundenDatensatz *Datensatz) {
	// Gebe Daten frei
	gebeKundenNummerFrei(Datensatz->kundenNummer);
	gebeKundenNameFrei(Datensatz->kundenName);
	gebeDatumFrei(Datensatz->geburtstag);
	gebeAdresseFrei(Datensatz->adresse);
	gebeStammkundeFrei(Datensatz->stammkunde);

	// Initialisiere Daten
	Datensatz->kundenNummer = initialisiereKundenNummer();
	Datensatz->kundenName = initialisiereKundenName();
	Datensatz->geburtstag = initialisiereDatum();
	Datensatz->adresse = initialisiereAdresse();
	Datensatz->stammkunde = initialisiereStammkunde();
}
