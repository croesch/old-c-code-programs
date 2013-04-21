/*
 ============================================================================
 Name        : FuegeEintragZuVerleihdaten.c
 Author      : Johann Deter
 Created on  : Jun 7, 2011
 Description : Fuegt einen VerleihDatensatz zur Datei Verleihdaten hinzu
 ============================================================================
 */

#include "Videotheksystem.h"

void FuegeEintragZuVerleihdaten(VerleihDatensatz * vds, FILE *verleihdatenDatei) {

	fprintf(verleihdatenDatei, "%06d|", vds->filmNummer->nummer);
	fprintf(verleihdatenDatei, "%d|", vds->kundenNummer->nummer);
	fprintf(verleihdatenDatei, "%04d|", vds->ausleihDatum->tm_year);
	fprintf(verleihdatenDatei, "%02d|", vds->ausleihDatum->tm_mon);
	fprintf(verleihdatenDatei, "%02d|", vds->ausleihDatum->tm_mday);
	fprintf(verleihdatenDatei, "%d|", vds->ausleihDauer->dauer);
	fprintf(verleihdatenDatei, "%03d|", vds->tagesPreis->wert);
	fprintf(verleihdatenDatei, "%d\n", vds->bezahlterBetrag->betrag);
}
