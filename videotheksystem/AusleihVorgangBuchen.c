/*
 ============================================================================
 Name        : AusleihVorgangBuchen.c
 Author      : Christian R?sch
 Created on  : Jun 4, 2011
 Description : Schreibt die in der Ausleihliste befindlichen Eintraege in
 die Datei fuer Verleihdatensaetze
 Rueckgabe	 : Gibt den Status zurueck, ob Ausleihvorgang gebucht werden konnte oder nicht
 Status 0 entspricht, dass Ausleihvorgang nicht gebucht werden konnte
 Status 1 entspricht, dass Ausleihvorgang gebucht werden konnte
 ============================================================================
 */

#include "Videotheksystem.h"

Status * AusleihVorgangBuchen(AusleihDauer* Ausleihdauer, AusleihListe* Ausleihliste, KundenNummer* KundenNummer) {

	// aktuelles Datum holen
	Datum * ausleihDatum = HoleSystemDatum();
	// entsprechende Datei oeffnen
	FILE *verleihdatenDatei = DateiOeffnen(verleihDatenDateiAdresse());
	// Liste in lokaler Variable ablegen
	AusleihListe* eintrag = Ausleihliste;
	// Solange Eintraege vorhanden sind, diese in die Datei schreiben
	while (eintrag != NULL) {
		// Daten in einen Datensatz packen
		VerleihDatensatz * vds = initialisiereVerleihDatensatz();
		vds->filmNummer->nummer = eintrag->filmNummer->nummer;
		vds->kundenNummer->nummer = KundenNummer->nummer;
		kopiereDatum(vds->ausleihDatum, ausleihDatum);
		vds->ausleihDauer->dauer = Ausleihdauer->dauer;
		vds->tagesPreis->wert = eintrag->tagesPreis->wert;
		vds->bezahlterBetrag->betrag = eintrag->betrag->betrag;

		// Schreibeoperation aufrufen
		FuegeEintragZuVerleihdaten(vds, verleihdatenDatei);
		// Speicher wieder freigeben
		gebeVerleihDatensatzFrei(vds);

		// naechsten Eintrag ansehen
		eintrag = eintrag->naechster;
	}
	// Datei schliessen
	DateiSchliessen(verleihdatenDatei);

	// Status fuer 'Operation erfolgreich' setzen und rueckgeben
	Status * status = initialisiereStatus();
	status->wert = 1;
	return status;
}
