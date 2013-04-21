/*
 ============================================================================
 Name        : FilmListeErstellen.c
 Author      : Christian R?sch
 Created on  : Jun 4, 2011
 Description : Funktion erstellt eine Filmliste, wenn mehrere Filme ausgeliehen werden
 ============================================================================
 */

#include "Videotheksystem.h"

void FilmListeErstellen() {
	KundenDatensatz *kds = initialisiereKundenDatensatz();
	Status * s = KundeIdentifizieren(kds);
	// Wenn Kunde identifiziert wurde, dann mache weiter, sonst beende Funktion
	if (s->wert == 1) {
		Datum* geburtstag = kds->geburtstag;
		AusleihDauer* dauer = AusleihDauerEingeben();
		LeereAusleihListe();
		GesamtBetrag* gesamt = initialisiereGesamtBetrag();
		int Ende = 0;
		// Mache solange Ende = 0 ist
		while (Ende == 0) {
			FilmDatensatz *fds = initialisiereFilmDatensatz();

			// suchen einer Films, und bestimmen der verfuegbaren Medienanzahl
			VerfuegbareMedienAnzahl* anz = FilmSuchen(fds);

			// Wenn Medienanz groesser 0 ist, dann mache weiter
			if (anz->medienAnz > 0) {
				FilmNummer* filmNummer = fds->filmNummer;
				TagesPreis* preis = initialisiereTagesPreis();
				preis->wert = fds->tagesPreis->wert;
				FSK* fsk = fds->fsk;
				FilmTitel* titel = fds->filmTitel;
				gebeStatusFrei(s);
				// Proefen ob Kunde alt genug ist
				s = AlterPruefen(fsk, geburtstag);
				// Wenn Kunde alt genug ist, dann darf dieser den Film ausleihen
				if (s->wert == 1) {
					Betrag* betrag = PreisBerechnen(preis, dauer);
					TextAusgeben("Film '%s' ausleihen?", titel->titel);
					// Bestaetigung holen, ob Kunde den gewuenschten Film ausleihen will
					Bestaetigung* best = holeBestaetigung();
					// Wenn Kunde Film ausleihen moechte, dann fuege den Eintrag zur Ausleihliste hinzu
					if (best->wert) {
						FuegeEintragZuAusleihliste(betrag, preis, filmNummer);
						gesamt->betrag->betrag += betrag->betrag;
					}
					gebeBestaetigungFrei(best);
					gebeBetragFrei(betrag);
				}
				gebeTagesPreisFrei(preis);
			}

			gebeVerfuegbareMedienAnzahlFrei(anz);

			TextAusgeben("Weiteren Film ausleihen?");
			// Bestatigung holen, ob Kunde weitere Filme ausleihen moechte
			Bestaetigung* best = holeBestaetigung();
			// Wenn Kunde keine weiteren Filme ausleihen moechte, dann setze Ende auf 1
			if (!best->wert) {
				Ende = 1;
			}
			gebeFilmDatensatzFrei(fds);
			gebeBestaetigungFrei(best);
		}
		// Erstellen der zu zahlenden Rechnung
		if (ausleihListe != NULL) {
			RechnungErstellen(gesamt, dauer, ausleihListe, kds);
			Bestaetigung* best = initialisiereBestaetigung();
			best->wert = 0;

			// Wenn Kunde ein Stammkunde ist, dann Fragen ob er auf Rechnung zahlen moechte
			if (kds->stammkunde->stammkunde == 1) {
				TextAusgeben("Auf Rechnung bezahlen?");
				gebeBestaetigungFrei(best);
				// Hole Bestaetigung ob Stammkunde auf Rechnung zahlen moechte
				best = holeBestaetigung();
			}
			// Wenn auf Rechnung gezahlt wird, dann wir der Betrag in der Ausleihliste auf 0 gesetzt
			if (best->wert) {
				ausleihListe->betrag->betrag = 0;
			} else {
				// Sonst muss Kunde direkt Rechnung begleichen
				TextAusgeben("Betrag %.2f bezahlt?", gesamt->betrag->betrag / 100.0);
				gebeBestaetigungFrei(best);
				// Hole Bestaetigung ob Kunde bezahlt hat
				best = holeBestaetigung();
			}
			// Wenn Kunde bezahlt hat, dann kann Ausleihvorgang gebucht und abgeschlossen werden
			if (best->wert) {
				gebeStatusFrei(s);
				s = AusleihVorgangBuchen(dauer, ausleihListe, kds->kundenNummer);
				// Wurde Ausleihvorgang erfolgreich gebucht, dann gebe Erfolgsmeldung aus
				if (s->wert == 1) {
					TextAusgeben("Ausleihvorgang erfolgreich gebucht!");
				}
			}
			gebeBestaetigungFrei(best);
		}
		gebeAusleihDauerFrei(dauer);
		gebeGesamtBetragFrei(gesamt);
		gebeStatusFrei(s);
	}
	gebeKundenDatensatzFrei(kds);
}
