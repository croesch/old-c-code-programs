/*
 ============================================================================
 Name        : AusgelieheneFilmeAuflisten.c
 Author      : Christian R?sch
 Created on  : Jun 4, 2011
 Description : Erstellt eine Liste aller aktuell ausgeliehenen Filme
 ============================================================================
 */

#include "Videotheksystem.h"

void AusgelieheneFilmeAuflisten() {

	FILE *verleihdatenDatei = DateiOeffnen(verleihDatenDateiAdresse());

	TitelAusgeben("Ausgeliehene Filme auflisten");

	int ausgegeben = 0; // zaehlt die Anzahl angezeigter Datensaetze
	while (!feof(verleihdatenDatei)) {

		VerleihDatensatz * ds = LeseNaechstenVerleihDatensatz(verleihdatenDatei);

		// kann NULL sein, was aber kein valider Wert ist.
		if (ds != NULL) {

			KundenDatensatz* kds = initialisiereKundenDatensatz();
			// beantragten Speicher im Container freigeben
			gebeKundenNummerFrei(kds->kundenNummer);
			// setze Kundennummer, um entsprechenden Kunden zu finden
			kds->kundenNummer = ds->kundenNummer;

			KundeSuchenNachExtern(kds);

			// Berechnung des Rueckgabedatums
			Datum * rueck = addiereAusleihDauerZuDatum(ds->ausleihDatum, ds->ausleihDauer);

			if (ausgegeben == 0) {
				// Bei der ersten Ausgabe Kopfzeile ausgeben
				VerleihDatenKopfAusgeben();
			}
			// Datensatz ausgeben
			VerleihDatenZeileAusgeben(ds, kds->kundenName->name, rueck);
			++ausgegeben; // Zaehler erhoehen

			ds->kundenNummer = NULL; // entferne Abhaengigkeit der Zeiger
			// gebe Daten frei
			gebeDatumFrei(rueck);
			gebeKundenDatensatzFrei(kds);
			gebeVerleihDatensatzFrei(ds);
		}
	}

	if (ausgegeben > 0) {
		// wurde etwas ausgegeben, schliesse Tabelle ab
		VerleihDatenFussAusgeben();
	} else {
		// wurde nichts ausgegeben, gebe entsprechende Meldung aus.
		TextAusgeben("Es sind zur Zeit keine Filme ausgeliehen");
	}
	DateiSchliessen(verleihdatenDatei);
}
