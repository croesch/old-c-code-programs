/*
 ============================================================================
 Name        : datentypen.h
 Author      : Christian Rösch
 Created on  : Jun 14, 2011
 Description : Enthält alle Datentypen, die das Programm so benötigt. Und die Funktionen, um diese Datentypen zu initialisieren/freizugeben.
 ============================================================================
 */

#include <time.h>

typedef struct Adresse {
	char* adresse;
} Adresse;

Adresse* initialisiereAdresse();
void gebeAdresseFrei(Adresse* adresse);

typedef struct AusleihDauer {
	int dauer;
} AusleihDauer;

AusleihDauer* initialisiereAusleihDauer();
void gebeAusleihDauerFrei(AusleihDauer* dauer);

typedef struct tm Datum;

Datum* initialisiereDatum();
void gebeDatumFrei(Datum* datum);

typedef struct Beschreibung {
	char* beschreibung;
} Beschreibung;

Beschreibung* initialisiereBeschreibung();
void gebeBeschreibungFrei(Beschreibung* beschreibung);

typedef struct Bestaetigung {
	char* bestaetigung;
	int wert;
} Bestaetigung;

Bestaetigung* initialisiereBestaetigung();
void gebeBestaetigungFrei(Bestaetigung* best);

typedef struct Betrag {
	int betrag;
} Betrag;

Betrag* initialisiereBetrag();
void gebeBetragFrei(Betrag* betrag);

typedef struct KundenName {
	char* name;
} KundenName;

KundenName* initialisiereKundenName();
void gebeKundenNameFrei(KundenName* kName);

typedef struct Erfolgsmeldung {
	char* meldung;
} Erfolgsmeldung;

Erfolgsmeldung* initialisiereErfolgsmeldung();
void gebeErfolgsmeldungFrei(Erfolgsmeldung* meldung);

typedef struct Fehlermeldung {
	char* meldung;
} Fehlermeldung;

Fehlermeldung* initialisiereFehlermeldung();
void gebeFehlermeldungFrei(Fehlermeldung* meldung);

typedef struct FilmDauer {
	int dauer;
} FilmDauer;

FilmDauer* initialisiereFilmDauer();
void gebeFilmDauerFrei(FilmDauer* dauer);

typedef struct FilmNummer {
	int nummer;
} FilmNummer;

FilmNummer* initialisiereFilmNummer();
void gebeFilmNummerFrei(FilmNummer* nummer);

typedef struct FilmTitel {
	char* titel;
} FilmTitel;

FilmTitel* initialisiereFilmTitel();
void gebeFilmTitelFrei(FilmTitel* titel);

typedef struct Frage {
	char* frage;
} Frage;

Frage* initialisiereFrage();
void gebeFrageFrei(Frage* frage);

typedef struct FSK {
	int fsk;
} FSK;

FSK* initialisiereFSK();
void gebeFSKfrei(FSK* fsk);

typedef struct GesamtBetrag {
	Betrag* betrag;
} GesamtBetrag;

GesamtBetrag* initialisiereGesamtBetrag();
void gebeGesamtBetragFrei(GesamtBetrag* betrag);

typedef struct KundenNummer {
	int nummer;
} KundenNummer;

KundenNummer* initialisiereKundenNummer();
void gebeKundenNummerFrei(KundenNummer* nummer);

typedef struct MedieAnzahl {
	int anz;
} MedienAnzahl;

MedienAnzahl* initialisiereMedienAnzahl();
void gebeMedienAnzahlFrei(MedienAnzahl* anz);

typedef struct sbg {
	char* begriff;
} SuchBegriff;

SuchBegriff * initialisiereSuchBegriff();
void gebeSuchBegriffFrei(SuchBegriff * suchBegriff);

typedef struct Stammkunde {
	int stammkunde;
} Stammkunde;

Stammkunde* initialisiereStammkunde();
void gebeStammkundeFrei(Stammkunde* stammkunde);

typedef struct sts {
	int wert;
} Status;

Status * initialisiereStatus();
void gebeStatusFrei(Status * status);

typedef struct tgp {
	int wert;
} TagesPreis;

TagesPreis * initialisiereTagesPreis();
void gebeTagesPreisFrei(TagesPreis * tagesPreis);

typedef struct VerfuegbareMedienAnzahl {
	int medienAnz;
} VerfuegbareMedienAnzahl;

VerfuegbareMedienAnzahl* initialisiereVerfuegbareMedienAnzahl();
void gebeVerfuegbareMedienAnzahlFrei(VerfuegbareMedienAnzahl* medienAnz);

typedef struct ziff {
	int wert;
} Ziffer;

Ziffer * initialisiereZiffer();
void gebeZifferFrei(Ziffer * ziffer);

typedef struct KundenIdentifikation {
	KundenNummer* kundenNummer;
	KundenName* kundenName;
	Datum* geb;
	Adresse* adresse;
} KundenIdentifikation;

KundenIdentifikation* initialisiereKundenIdentifikation();
void gebeKundenIdentifikationFrei(KundenIdentifikation* kIdent);

typedef struct AusleihDaten {
	KundenIdentifikation* kundenIdentifikation;
	AusleihDauer* ausleihDauer;
	Bestaetigung* bestaetigung;
} AusleihDaten;

AusleihDaten* initialisiereAusleihDaten();
void gebeAusleihDatenFrei(AusleihDaten* ausleihDaten);

typedef struct AusleihListe {
	FilmNummer* filmNummer;
	TagesPreis* tagesPreis;
	Betrag* betrag;
	FilmTitel* filmTitel;
	struct AusleihListe* naechster;
} AusleihListe;

AusleihListe* initialisiereAusleihListe();
void gebeAusleihListeFrei(AusleihListe* liste);

typedef struct Kommentar {
	char* kommentar;
} Kommentar;

Kommentar* initialisiereKommentar();
void gebeKommentarFrei(Kommentar* kommentar);

typedef struct FilmDatensatz {
	FilmNummer* filmNummer;
	MedienAnzahl* medienAnzahl;
	TagesPreis* tagesPreis;
	FSK* fsk;
	FilmDauer* filmDauer;
	FilmTitel* filmTitel;
	Beschreibung* beschreibung;
	Kommentar* kommentar;
	struct FilmDatensatz* naechster;
} FilmDatensatz;

FilmDatensatz* initialisiereFilmDatensatz();
void gebeFilmDatensatzFrei(FilmDatensatz* filmDatensatz);

typedef struct FilmDatei {
	FilmDatensatz* filmDatensatz;
} FilmDatei;

FilmDatei* initialisiereFilmDatei();
void gebeFilmDateiFrei(FilmDatei* filmDatei);

typedef struct FilmListe {
	FilmNummer* filmNummer;
	VerfuegbareMedienAnzahl* anz;
	FilmTitel* filmTitel;
} FilmListe;

FilmListe* initialisiereFilmListe();
void gebeFilmListe(FilmListe* liste);

typedef struct KundenDatensatz {
	KundenNummer* kundenNummer;
	KundenName* kundenName;
	Datum* geburtstag;
	Adresse* adresse;
	Stammkunde* stammkunde;
} KundenDatensatz;

KundenDatensatz* initialisiereKundenDatensatz();
void gebeKundenDatensatzFrei(KundenDatensatz* kds);

typedef struct Meldung {
	Erfolgsmeldung* erfolg;
	Fehlermeldung* fehler;
	Frage* frage;
	KundenDatensatz* kDs;
	GesamtBetrag* gesBetr;
} Meldung;

Meldung* initialisiereMeldung();
void gebeMeldungFrei(Meldung* meldung);

typedef struct Mwst {
	int mwst;
} Mwst;

Mwst* initialisiereMwst();
void gebeMwstFrei(Mwst* mwst);

typedef struct Rechnung {
	KundenNummer* kundenNummer;
	KundenName* kundenName;
	Adresse* adresse;
	FilmNummer* filmNummer;
	TagesPreis* tagesPreis;
	Betrag* betrag;
	GesamtBetrag* gesBetrag;
	Mwst* mwst;
	Datum* rueckgabeDatum;
} Rechnung;

Rechnung* initialisiereRechnung();
void gebeRechnungFrei(Rechnung* rechnung);

typedef struct rgl {
	FilmNummer* filmNummer;
	Datum* ausleihDatum;
	struct rgl* naechster;
} RueckgabeListe;

RueckgabeListe * initialisiereRueckgabeListe();
void gebeRueckgabeListeFrei(RueckgabeListe * rueckgabeListe);

typedef struct SuchErgebnis {
	FilmListe* filmListe;
	FilmDatensatz* filmDatensatz;
	VerfuegbareMedienAnzahl* medienAnz;
} SuchErgebnis;

SuchErgebnis* initialisiereSuchErgebnis();
void gebeSuchErgebnisFrei(SuchErgebnis* ergebnis);

typedef struct vlds {
	FilmNummer* filmNummer;
	KundenNummer* kundenNummer;
	Datum* ausleihDatum;
	AusleihDauer* ausleihDauer;
	TagesPreis* tagesPreis;
	Betrag* bezahlterBetrag;
	struct vlds* naechster;
} VerleihDatensatz;

VerleihDatensatz * initialisiereVerleihDatensatz();
void gebeVerleihDatensatzFrei(VerleihDatensatz * datensatz);

RueckgabeListe* rueckgabeListe;
AusleihListe* ausleihListe;
