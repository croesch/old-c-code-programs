/*
 ============================================================================
 Name        : RechnungErstellen.c
 Author      : Christian R?sch
 Created on  : Jun 4, 2011
 Description : Stellt aus den gegebenen Daten eine Rechnung auf dem Bildschirm dar
 ============================================================================
 */

#include "Videotheksystem.h"

void RechnungErstellen(GesamtBetrag* Betrag, AusleihDauer* Dauer, AusleihListe* Liste, KundenDatensatz* Datensatz) {

	// aktuelles Datum
	Datum * datum = HoleSystemDatum();

	// Titel der Rechnung, enthaelt aktuelles Datum
	TextAusgeben("+------------------------------------------------------------+");
	TextAusgeben("|                   RECHNUNG v. %04d/%02d/%02d                   |", datum->tm_year, datum->tm_mon,
			datum->tm_mday);
	TextAusgeben("+------------------------------------------------------------+");

	// Kundennummer ausgeben
	TextOhneUmbruchAusgeben("| KundenNr: %12d", Datensatz->kundenNummer->nummer);
	TextAuffuellenUndOhneUmbruchAusgeben("", 37, ' ');
	TextAusgeben("|");

	// Kundenname ausgeben
	TextOhneUmbruchAusgeben("| Kundenname: ");
	TextAuffuellenUndOhneUmbruchAusgeben(Datensatz->kundenName->name, 47, ' ');
	TextAusgeben("|");

	// Adresse ausgeben
	TextOhneUmbruchAusgeben("| Adresse: ");
	TextAuffuellenUndOhneUmbruchAusgeben(Datensatz->adresse->adresse, 50, ' ');
	TextAusgeben("|");

	// Leerzeile
	TextAuffuellenUndOhneUmbruchAusgeben("|", 61, ' ');
	TextAusgeben("|");

	// Falls Rueckgabedatum in Zukunft, gebe Anzahl Tage aus (Beim zurueckgeben ist dauer=0)
	if (Dauer->dauer > 0) {
		TextAusgeben("| Filme fuer %5d Tage:                                     |", Dauer->dauer);
	}

	// Filme der Rechnung ausgeben
	while (Liste) {
		// Zeile pro Film
		TextAusgeben("| Filmnummer %06d  Tagespreis %03d Ct.  zu %12.2f EUR |", Liste->filmNummer->nummer,
				Liste->tagesPreis->wert, Liste->betrag->betrag / 100.0);
		// naechster Film
		Liste = Liste->naechster;
	}
	// Zeilen fuer Gesamtbetrag ausgeben
	TextAusgeben("|                                          ------------------+");
	TextAusgeben("|                             Gesamtbetrag: %12.2f EUR |", Betrag->betrag->betrag / 100.0);
	// Mehrwertsteuer berechnen und ausgeben
	double mwst = Betrag->betrag->betrag / 100 * 0.19;
	TextAusgeben("|                Darin enthalten 19%% MwSt.: %12.2f EUR |", mwst);

	// Leerzeile
	TextAuffuellenUndOhneUmbruchAusgeben("|", 61, ' ');
	TextAusgeben("|");

	// Falls Rueckgabedatum in Zukunft, gebe es aus (Beim zurueckgeben ist dauer=0)
	if (Dauer->dauer > 0) {
		// Berechnen und Ausgeben des Rueckgabedatums
		Datum* rueck = addiereAusleihDauerZuDatum(datum, Dauer);
		TextAusgeben("|                Rueckgabe bis spaetestens:       %04d/%02d/%02d |", rueck->tm_year,
				rueck->tm_mon, rueck->tm_mday);
		gebeDatumFrei(rueck);

		// Leerzeile
		TextAuffuellenUndOhneUmbruchAusgeben("|", 61, ' ');
		TextAusgeben("|");
	}

	// Unterer Rand der Rechnung
	TextAusgeben("+------------------------------------------------------------+");
}
