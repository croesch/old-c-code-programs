/*
 ============================================================================
 Name        : datentypen.h
 Author      : Christian Rösch
 Created on  : Jun 14, 2011
 Description : Enthält alle Datentypen, die das Programm so benötigt. Und die Funktionen, um diese Datentypen zu initialisieren/freizugeben.
 ============================================================================
 */

#include <time.h>
#include "datentypen.h"
#include <stdlib.h>

Adresse* initialisiereAdresse() {
	Adresse* adresse = (Adresse*) malloc(sizeof(Adresse));

	adresse->adresse = (char*) malloc(100 * sizeof(char));

	return adresse;
}

void gebeAdresseFrei(Adresse* adresse) {
	free(adresse->adresse);
	free(adresse);
}

AusleihDaten* initialisiereAusleihDaten() {
	AusleihDaten* ausleihDaten = (AusleihDaten*) malloc(sizeof(AusleihDaten));

	ausleihDaten->ausleihDauer = initialisiereAusleihDauer();
	ausleihDaten->bestaetigung = initialisiereBestaetigung();
	ausleihDaten->kundenIdentifikation = initialisiereKundenIdentifikation();

	return ausleihDaten;
}

void gebeAusleihDatenFrei(AusleihDaten* ausleihDaten) {
	gebeAusleihDauerFrei(ausleihDaten->ausleihDauer);
	gebeBestaetigungFrei(ausleihDaten->bestaetigung);
	gebeKundenIdentifikationFrei(ausleihDaten->kundenIdentifikation);

	free(ausleihDaten);
}

AusleihDauer* initialisiereAusleihDauer() {
	AusleihDauer* dauer = (AusleihDauer*) malloc(sizeof(AusleihDauer));

	dauer->dauer = 0;

	return dauer;
}

void gebeAusleihDauerFrei(AusleihDauer* dauer) {
	free(dauer);
}

AusleihListe* initialisiereAusleihListe() {
	AusleihListe* liste = (AusleihListe*) malloc(sizeof(AusleihListe));

	liste->filmNummer = initialisiereFilmNummer();
	liste->filmTitel = initialisiereFilmTitel();
	liste->tagesPreis = initialisiereTagesPreis();
	liste->betrag = initialisiereBetrag();
	liste->naechster = NULL;

	return liste;
}

void gebeAusleihListeFrei(AusleihListe* liste) {
	if (liste != NULL) {
		gebeBetragFrei(liste->betrag);
		gebeFilmNummerFrei(liste->filmNummer);
		gebeFilmTitelFrei(liste->filmTitel);
		gebeTagesPreisFrei(liste->tagesPreis);
		gebeAusleihListeFrei(liste->naechster);
		free(liste);
	}
}

Beschreibung* initialisiereBeschreibung() {
	Beschreibung* beschreibung = (Beschreibung*) malloc(sizeof(Beschreibung));

	beschreibung->beschreibung = (char*) malloc(1000 * sizeof(char));

	return beschreibung;
}
void gebeBeschreibungFrei(Beschreibung* beschreibung) {
	free(beschreibung->beschreibung);
	free(beschreibung);
}

Bestaetigung* initialisiereBestaetigung() {
	Bestaetigung* best = (Bestaetigung*) malloc(sizeof(Bestaetigung));

	best->bestaetigung = (char*) malloc(4 * sizeof(char));

	return best;
}

void gebeBestaetigungFrei(Bestaetigung* best) {
	free(best->bestaetigung);
	free(best);
}

Betrag* initialisiereBetrag() {
	Betrag* betrag = (Betrag*) malloc(sizeof(Betrag));

	betrag->betrag = 0;

	return betrag;
}

void gebeBetragFrei(Betrag* betrag) {
	free(betrag);
}

Datum* initialisiereDatum() {
	Datum* d = (Datum*) malloc(sizeof(Datum));
	d->tm_isdst = -1;
	d->tm_hour = d->tm_min = d->tm_sec = d->tm_year = d->tm_mon = d->tm_mday = 0;

	return d;
}

void gebeDatumFrei(Datum* datum) {
	free(datum);
}

Erfolgsmeldung* initialisiereErfolgsmeldung() {
	Erfolgsmeldung* meldung = (Erfolgsmeldung*) malloc(sizeof(Erfolgsmeldung));

	meldung->meldung = (char*) malloc(1000 * sizeof(char));

	return meldung;
}

void gebeErfolgsmeldungFrei(Erfolgsmeldung* meldung) {
	free(meldung->meldung);
	free(meldung);
}

Fehlermeldung* initialisiereFehlermeldung() {
	Fehlermeldung* meldung = (Fehlermeldung*) malloc(sizeof(Fehlermeldung));

	meldung->meldung = (char*) malloc(1000 * sizeof(char));

	return meldung;
}

void gebeFehlermeldungFrei(Fehlermeldung* meldung) {
	free(meldung->meldung);
	free(meldung);
}

FilmDatei* initialisiereFilmDatei() {
	FilmDatei* filmDatei = (FilmDatei*) malloc(sizeof(FilmDatei));

	filmDatei->filmDatensatz = initialisiereFilmDatensatz();

	return filmDatei;
}

void gebeFilmDateiFrei(FilmDatei* filmDatei) {
	gebeFilmDatensatzFrei(filmDatei->filmDatensatz);
	free(filmDatei);
}

FilmDatensatz* initialisiereFilmDatensatz() {
	FilmDatensatz* datensatz = (FilmDatensatz*) malloc(sizeof(FilmDatensatz));

	datensatz->beschreibung = initialisiereBeschreibung();
	datensatz->filmDauer = initialisiereFilmDauer();
	datensatz->filmNummer = initialisiereFilmNummer();
	datensatz->filmTitel = initialisiereFilmTitel();
	datensatz->fsk = initialisiereFSK();
	datensatz->kommentar = initialisiereKommentar();
	datensatz->medienAnzahl = initialisiereMedienAnzahl();
	datensatz->tagesPreis = initialisiereTagesPreis();
	datensatz->naechster = NULL;

	return datensatz;
}
void gebeFilmDatensatzFrei(FilmDatensatz* filmDatensatz) {
	if (filmDatensatz != NULL) {
		gebeBeschreibungFrei(filmDatensatz->beschreibung);
		gebeFilmDauerFrei(filmDatensatz->filmDauer);
		gebeFilmNummerFrei(filmDatensatz->filmNummer);
		gebeFilmTitelFrei(filmDatensatz->filmTitel);
		gebeFSKfrei(filmDatensatz->fsk);
		gebeKommentarFrei(filmDatensatz->kommentar);
		gebeMedienAnzahlFrei(filmDatensatz->medienAnzahl);
		gebeTagesPreisFrei(filmDatensatz->tagesPreis);
		gebeFilmDatensatzFrei(filmDatensatz->naechster);
		free(filmDatensatz);
	}
}

FilmDauer* initialisiereFilmDauer() {
	FilmDauer* dauer = (FilmDauer*) malloc(sizeof(FilmDauer));

	dauer->dauer = 0;

	return dauer;
}

void gebeFilmDauerFrei(FilmDauer* dauer) {
	free(dauer);
}

FilmListe* initialisiereFilmListe() {
	FilmListe* liste = (FilmListe*) malloc(sizeof(FilmListe));

	liste->filmNummer = initialisiereFilmNummer();
	liste->anz = initialisiereVerfuegbareMedienAnzahl();
	liste->filmTitel = initialisiereFilmTitel();

	return liste;
}
void gebeFilmListe(FilmListe* liste) {
	gebeFilmNummerFrei(liste->filmNummer);
	gebeFilmTitelFrei(liste->filmTitel);
	gebeVerfuegbareMedienAnzahlFrei(liste->anz);
	free(liste);
}

FilmNummer* initialisiereFilmNummer() {
	FilmNummer* nummer = (FilmNummer*) malloc(sizeof(FilmNummer));

	nummer->nummer = 0;

	return nummer;
}
void gebeFilmNummerFrei(FilmNummer* nummer) {
	free(nummer);
}

FilmTitel* initialisiereFilmTitel() {
	FilmTitel* titel = (FilmTitel*) malloc(sizeof(FilmTitel));

	titel->titel = (char*) malloc(50 * sizeof(char));

	return titel;
}

void gebeFilmTitelFrei(FilmTitel* titel) {
	free(titel->titel);
	free(titel);
}

Frage* initialisiereFrage() {
	Frage* frage = (Frage*) malloc(sizeof(Frage));

	frage->frage = (char*) malloc(200 * sizeof(char));

	return frage;
}

void gebeFrageFrei(Frage* frage) {
	free(frage->frage);
	free(frage);
}

FSK* initialisiereFSK() {
	FSK* fsk = (FSK*) malloc(sizeof(FSK));

	fsk->fsk = 0;

	return fsk;
}

void gebeFSKfrei(FSK* fsk) {
	free(fsk);
}

GesamtBetrag* initialisiereGesamtBetrag() {
	GesamtBetrag* betr = (GesamtBetrag*) malloc(sizeof(GesamtBetrag));

	betr->betrag = initialisiereBetrag();

	return betr;
}

void gebeGesamtBetragFrei(GesamtBetrag* gesBetrag) {
	gebeBetragFrei(gesBetrag->betrag);
	free(gesBetrag);
}

Kommentar* initialisiereKommentar() {
	Kommentar* kommentar = (Kommentar*) malloc(sizeof(Kommentar));

	kommentar->kommentar = (char*) malloc(1000 * sizeof(char));

	return kommentar;
}

void gebeKommentarFrei(Kommentar* kommentar) {
	free(kommentar->kommentar);
	free(kommentar);
}

KundenDatensatz* initialisiereKundenDatensatz() {
	KundenDatensatz* kds = (KundenDatensatz*) malloc(sizeof(KundenDatensatz));

	kds->adresse = initialisiereAdresse();
	kds->geburtstag = initialisiereDatum();
	kds->kundenName = initialisiereKundenName();
	kds->kundenNummer = initialisiereKundenNummer();
	kds->stammkunde = initialisiereStammkunde();

	return kds;
}

void gebeKundenDatensatzFrei(KundenDatensatz* kds) {
	gebeAdresseFrei(kds->adresse);
	gebeDatumFrei(kds->geburtstag);
	gebeKundenNameFrei(kds->kundenName);
	gebeKundenNummerFrei(kds->kundenNummer);
	gebeStammkundeFrei(kds->stammkunde);
	free(kds);
}

KundenIdentifikation* initialisiereKundenIdentifikation() {
	KundenIdentifikation* kIdent = (KundenIdentifikation*) malloc(sizeof(KundenIdentifikation));

	kIdent->adresse = initialisiereAdresse();
	kIdent->geb = initialisiereDatum();
	kIdent->kundenName = initialisiereKundenName();
	kIdent->kundenNummer = initialisiereKundenNummer();

	return kIdent;
}

void gebeKundenIdentifikationFrei(KundenIdentifikation* kIdent) {
	gebeAdresseFrei(kIdent->adresse);
	gebeDatumFrei(kIdent->geb);
	gebeKundenNameFrei(kIdent->kundenName);
	gebeKundenNummerFrei(kIdent->kundenNummer);
	free(kIdent);
}

KundenName* initialisiereKundenName() {
	KundenName* kName = (KundenName*) malloc(sizeof(KundenName));

	kName->name = (char*) malloc(81 * sizeof(char));

	return kName;
}

void gebeKundenNameFrei(KundenName* kName) {
	free(kName->name);
	free(kName);
}

KundenNummer* initialisiereKundenNummer() {
	KundenNummer* nr = (KundenNummer*) malloc(sizeof(KundenNummer));

	nr->nummer = 0;

	return nr;
}

void gebeKundenNummerFrei(KundenNummer* nummer) {
	free(nummer);
}

MedienAnzahl* initialisiereMedienAnzahl() {
	MedienAnzahl* anz = (MedienAnzahl*) malloc(sizeof(MedienAnzahl));

	anz->anz = 0;

	return anz;
}

void gebeMedienAnzahlFrei(MedienAnzahl* anz) {
	free(anz);
}

Meldung* initialisiereMeldung() {
	Meldung* meldung = (Meldung*) malloc(sizeof(Meldung));

	meldung->kDs = initialisiereKundenDatensatz();
	meldung->erfolg = initialisiereErfolgsmeldung();
	meldung->fehler = initialisiereFehlermeldung();
	meldung->frage = initialisiereFrage();
	meldung->gesBetr = initialisiereGesamtBetrag();

	return meldung;
}

void gebeMeldungFrei(Meldung* meldung) {
	gebeKundenDatensatzFrei(meldung->kDs);
	gebeErfolgsmeldungFrei(meldung->erfolg);
	gebeFehlermeldungFrei(meldung->fehler);
	gebeFrageFrei(meldung->frage);
	gebeGesamtBetragFrei(meldung->gesBetr);
}

Mwst* initialisiereMwst() {
	Mwst* mwst = (Mwst*) malloc(sizeof(Mwst));

	mwst->mwst = 0;

	return mwst;
}

void gebeMwstFrei(Mwst* mwst) {
	free(mwst);
}

Rechnung* initialisiereRechnung() {
	Rechnung* rechnung = (Rechnung*) malloc(sizeof(Rechnung));

	rechnung->adresse = initialisiereAdresse();
	rechnung->betrag = initialisiereBetrag();
	rechnung->filmNummer = initialisiereFilmNummer();
	rechnung->gesBetrag = initialisiereGesamtBetrag();
	rechnung->kundenName = initialisiereKundenName();
	rechnung->kundenNummer = initialisiereKundenNummer();
	rechnung->mwst = initialisiereMwst();
	rechnung->rueckgabeDatum = initialisiereDatum();
	rechnung->tagesPreis = initialisiereTagesPreis();

	return rechnung;

}

void gebeRechnungFrei(Rechnung* rechnung) {
	gebeAdresseFrei(rechnung->adresse);
	gebeBetragFrei(rechnung->betrag);
	gebeFilmNummerFrei(rechnung->filmNummer);
	gebeGesamtBetragFrei(rechnung->gesBetrag);
	gebeKundenNameFrei(rechnung->kundenName);
	gebeKundenNummerFrei(rechnung->kundenNummer);
	gebeMwstFrei(rechnung->mwst);
	gebeDatumFrei(rechnung->rueckgabeDatum);
	gebeTagesPreisFrei(rechnung->tagesPreis);
	free(rechnung);
}

RueckgabeListe * initialisiereRueckgabeListe() {
	RueckgabeListe * liste = (RueckgabeListe*) malloc(sizeof(RueckgabeListe));
	liste->ausleihDatum = initialisiereDatum();
	liste->filmNummer = initialisiereFilmNummer();
	liste->naechster = NULL;
	return liste;
}

void gebeRueckgabeListeFrei(RueckgabeListe * rueckgabeListe) {
	if (rueckgabeListe != NULL) {
		gebeDatumFrei(rueckgabeListe->ausleihDatum);
		gebeFilmNummerFrei(rueckgabeListe->filmNummer);
		gebeRueckgabeListeFrei(rueckgabeListe->naechster);
		free(rueckgabeListe);
	}
}

SuchErgebnis* initialisiereSuchErgebnis() {
	SuchErgebnis* ergebnis = (SuchErgebnis*) malloc(sizeof(SuchErgebnis));

	ergebnis->filmDatensatz = initialisiereFilmDatensatz();
	ergebnis->filmListe = initialisiereFilmListe();
	ergebnis->medienAnz = initialisiereVerfuegbareMedienAnzahl();

	return ergebnis;
}

void gebeSuchErgebnisFrei(SuchErgebnis* ergebnis) {
	gebeFilmDatensatzFrei(ergebnis->filmDatensatz);
	gebeFilmListe(ergebnis->filmListe);
	gebeVerfuegbareMedienAnzahlFrei(ergebnis->medienAnz);
	free(ergebnis);
}

Stammkunde* initialisiereStammkunde() {
	Stammkunde* stKunde = (Stammkunde*) malloc(sizeof(Stammkunde));

	stKunde->stammkunde = 0;

	return stKunde;
}

void gebeStammkundeFrei(Stammkunde* stammkunde) {
	free(stammkunde);
}

Status * initialisiereStatus() {
	Status * status = (Status*) malloc(sizeof(Status));
	status->wert = 0;
	return status;
}

void gebeStatusFrei(Status * status) {
	free(status);
}

SuchBegriff * initialisiereSuchBegriff() {
	SuchBegriff * begriff = (SuchBegriff*) malloc(sizeof(SuchBegriff));
	begriff->begriff = (char*) malloc(sizeof(char) * 80);
	return begriff;
}

void gebeSuchBegriffFrei(SuchBegriff * suchBegriff) {
	free(suchBegriff->begriff);
	free(suchBegriff);
}

TagesPreis * initialisiereTagesPreis() {
	TagesPreis * preis = (TagesPreis*) malloc(sizeof(TagesPreis));
	preis->wert = 0;
	return preis;
}

void gebeTagesPreisFrei(TagesPreis * tagesPreis) {
	free(tagesPreis);
}

VerfuegbareMedienAnzahl* initialisiereVerfuegbareMedienAnzahl() {
	VerfuegbareMedienAnzahl* medienAnz = (VerfuegbareMedienAnzahl*) malloc(sizeof(VerfuegbareMedienAnzahl));

	medienAnz->medienAnz = 0;

	return medienAnz;
}

void gebeVerfuegbareMedienAnzahlFrei(VerfuegbareMedienAnzahl* medienAnz) {
	free(medienAnz);
}

VerleihDatensatz * initialisiereVerleihDatensatz() {
	VerleihDatensatz * satz = (VerleihDatensatz*) malloc(sizeof(VerleihDatensatz));
	satz->filmNummer = initialisiereFilmNummer();
	satz->kundenNummer = initialisiereKundenNummer();
	satz->ausleihDatum = initialisiereDatum();
	satz->ausleihDauer = initialisiereAusleihDauer();
	satz->tagesPreis = initialisiereTagesPreis();
	satz->bezahlterBetrag = initialisiereBetrag();
	satz->naechster = NULL;

	return satz;
}

void gebeVerleihDatensatzFrei(VerleihDatensatz * datensatz) {
	if (datensatz != NULL) {
		gebeVerleihDatensatzFrei(datensatz->naechster);
		gebeFilmNummerFrei(datensatz->filmNummer);
		gebeKundenNummerFrei(datensatz->kundenNummer);
		gebeDatumFrei(datensatz->ausleihDatum);
		gebeAusleihDauerFrei(datensatz->ausleihDauer);
		gebeTagesPreisFrei(datensatz->tagesPreis);
		gebeBetragFrei(datensatz->bezahlterBetrag);
		free(datensatz);
	}
}

Ziffer * initialisiereZiffer() {
	Ziffer * ziffer = (Ziffer*) malloc(sizeof(Ziffer));
	ziffer->wert = 0;
	return ziffer;
}

void gebeZifferFrei(Ziffer * ziffer) {
	free(ziffer);
}
