/*
 ============================================================================
 Name        : BezahlungPruefen.c
 Author      : Christian R?sch
 Created on  : Jun 4, 2011
 Description : Berechnet bei der Rueckgabe von Filmen die ausstehenden Zahlungen
 ============================================================================
 */

#include "Videotheksystem.h"

void BezahlungPruefen() {
	KundenDatensatz *kds = initialisiereKundenDatensatz();
	// Identifiziere Kunden
	Status * s = KundeIdentifizieren(kds);
	// Wenn Kunde bekannt ist, dann mache weiter, sonst beende Funktion
	if (s->wert == 1) {
		Datum * rueckDatum = HoleSystemDatum();
		LeereRueckgabeListe();
		LeereAusleihListe();
		GesamtBetrag* gesamt = initialisiereGesamtBetrag();

		int Ende = 0;
		// Mache weiter, solange Ende = 0 ist
		while (Ende == 0) {
			// Benutzer gibt Filmnummer ein
			FilmNummer* fnr = FilmNummerEingeben();

			// Film an hand der eigegebenen Filmnummer in den Verleihdaten suchen
			VerleihDatensatz * vds = VerleihDatenSuchen(kds->kundenNummer, fnr);

			if (vds == NULL) {
				FehlerMeldungAusgeben("Kunde %d hat keinen Film der Nummer %d ausgeliehen.", kds->kundenNummer->nummer,
						fnr->nummer);
			} else {
				AusleihDauer * dauer = initialisiereAusleihDauer();
				dauer->dauer = berechneDatumsDifferenz(vds->ausleihDatum, rueckDatum);

				// Berechnen des Preises an hand des Tagespreises und der Ausleihdauer
				Betrag* betrag = PreisBerechnen(vds->tagesPreis, dauer);

				// Wenn Kunde schon einen Teil des Betrags bezahlt hat, dann diesen abziehen
				// vom Betrag
				betrag->betrag -= vds->bezahlterBetrag->betrag;

				// Betrag darf nicht negativ werden, wenn doch, dann wird dieser auf 0 gesetzt
				if (betrag->betrag < 0) {
					betrag->betrag = 0;
				}

				// Berechneten Betrag zum Gesamtbetrag addieren
				gesamt->betrag->betrag += betrag->betrag;
				FuegeEintragZuRueckgabeListe(vds->ausleihDatum, fnr);
				FuegeEintragZuAusleihliste(betrag, vds->tagesPreis, fnr); // für Rechnung
				TextAusgeben("Weitere Filme zurueckgeben?");
				Bestaetigung* bestaetigung = holeBestaetigung();

				// Werden keine weiteren Filme mehr zurueckgegeben, dann wird Ende auf 1 gesetzt
				if (!bestaetigung->wert) {
					Ende = 1;
				}
				gebeAusleihDauerFrei(dauer);
				gebeBetragFrei(betrag);
				gebeBestaetigungFrei(bestaetigung);
				gebeVerleihDatensatzFrei(vds);
			}
			gebeFilmNummerFrei(fnr);
		}
		AusleihDauer* dauer = initialisiereAusleihDauer(); // dauer = 0
		Bestaetigung* bestaetigung = initialisiereBestaetigung();

		// Wenn der Gesamtbetrag > 0 ist, dann muss eine Rechnung erstellt werden,
		// die vom Kunden sofort zu begleichen ist
		if (gesamt->betrag->betrag > 0) {
			RechnungErstellen(gesamt, dauer, ausleihListe, kds);
			TextAusgeben("Betrag %.2f bezahlt?", gesamt->betrag->betrag / 100.0);
			gebeBestaetigungFrei(bestaetigung);
			// Hole Bestaetigung ob Kunde Rechnung bezahlt hat
			bestaetigung = holeBestaetigung();
		} else {
			// Kunde hatte keine ausstehenden Zahlungen mehr
			// somit kann die Bestaetigung auf 'ja' gesetzt werden
			bestaetigung->wert = 1;
		}

		// Wenn Bestaetigung 'Ja' ist, dann kann der Rueckgabevorgang gebucht werden
		if (bestaetigung->wert) {
			gebeStatusFrei(s);
			s = RueckgabevorgangBuchen(kds->kundenNummer);

			// Wurde der Rueckgabevorgang erfolgreich gebucht, so gebe Erfolgsmeldung
			// aus, sonst Fehlermeldung
			if (s->wert == 1) {
				TextAusgeben("Rueckgabevorgang erfolgreich gebucht.");
			} else {
				FehlerMeldungAusgeben("Rueckgabevorgang nicht gebucht!");
			}
		} else {
			// Kunde hat Rechnung nicht bezahlt
			TextAusgeben("Rueckgabevorgang nicht gebucht, da Kunde nicht gezahlt hat!");
		}
		gebeAusleihDauerFrei(dauer);
		gebeBestaetigungFrei(bestaetigung);
		gebeGesamtBetragFrei(gesamt);
	}
	gebeKundenDatensatzFrei(kds);
	gebeStatusFrei(s);
}
