/*
 ============================================================================
 Name        : RueckgabeVorgangBuchen.c
 Author      : Christian R?sch
 Created on  : Jun 4, 2011
 Description : Entfernt die Datensaetze in der Rueckgabeliste aus der Verleihdatendatei
 Rueckgabe   : Status 1, falls alle Eintraege erfolgreich geloescht wurden
 Status 0, falls mindestens Eintrag nicht geloescht/gefunden wurde
 ============================================================================
 */

#include "Videotheksystem.h"

Status * RueckgabevorgangBuchen(KundenNummer* Kundennummer) {

	// Setze den Rueckgabewert auf 'Erfolg'
	Status * s = initialisiereStatus();
	s->wert = 1;

	// Oeffne die Verleihdatendatei
	FILE *verleihDaten = DateiOeffnen(verleihDatenDateiAdresse());
	// Speichere die Rueckgabeliste lokal ab
	RueckgabeListe * eintrag = rueckgabeListe;
	// Solange Eintraege vorhanden sind, entferne diese..
	while (eintrag != NULL) {
		// Setze den Dateizeiger an den Anfang der Datei
		fseek(verleihDaten, 0, SEEK_SET);

		// Lese den ersten Datensatz der Datei
		VerleihDatensatz* ds = LeseNaechstenVerleihDatensatz(verleihDaten);
		// Signal, ob Eintrag gefunden und entfernt wurde
		int Ende = 0;
		while (!feof(verleihDaten) && Ende == 0) {
			// wenn aktueller Eintrag dem zu loeschenden entspricht
			if (ds != NULL && ds->kundenNummer->nummer == Kundennummer->nummer && ds->filmNummer->nummer
					== eintrag->filmNummer->nummer && ds->ausleihDatum->tm_year == eintrag->ausleihDatum->tm_year
					&& ds->ausleihDatum->tm_mon == eintrag->ausleihDatum->tm_mon && ds->ausleihDatum->tm_mday
					== eintrag->ausleihDatum->tm_mday) {
				// Oeffne die Datei neu, um den Eintrag loeschen zu koennen
				DateiSchliessen(verleihDaten);
				verleihDaten = DateiOeffnen(verleihDatenDateiAdresse());
				// loesche den Eintrag aus der Datei
				LoescheEintragAusVerleihDaten(verleihDaten, ds);
				// Oeffne die Datei erneut, um nach dem naechsten Eintrag zu suchen
				verleihDaten = DateiOeffnen(verleihDatenDateiAdresse());
				// Signalisiere, dass Eintrag geloescht wurde
				Ende = 1;
			} else {
				// gebe aktuellen Datensatz frei und lese den naechsten
				gebeVerleihDatensatzFrei(ds);
				ds = LeseNaechstenVerleihDatensatz(verleihDaten);
			}
		}
		// gebe letzten Datensatz frei
		gebeVerleihDatensatzFrei(ds);

		// aktueller Eintrag wurde nicht gefunden
		if (Ende == 0) {
			// Setze Signal
			s->wert = 0;
		}
		// Nehme den naechsten zu entfernenden Eintrag
		eintrag = eintrag->naechster;
	}
	DateiSchliessen(verleihDaten);

	// Gebe den Status zurueck
	return s;
}
