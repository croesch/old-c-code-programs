/*
 ============================================================================
 Name        : Videotheksystem.h
 Author      : Christian R?sch
 Created on  : Jun 23, 2011
 Description : Globale Header-Datei zum Einbinden der Funktionen
 ============================================================================
 */

#include "commons/funktionen.h"
#include "commons/KundenVerwaltung.h"

int AlterBerechnen(Datum* geburtstag, Datum* jetzt);

Status* AlterPruefen(FSK* FSK, Datum* geburtstag);

void AusgelieheneFilmeAuflisten();

AusleihDauer * AusleihDauerEingeben();

Status * AusleihVorgangBuchen(AusleihDauer* Ausleihdauer, AusleihListe* Ausleihliste, KundenNummer* KundenNummer);

void BezahlungPruefen();

void LeereAusleihListe();

void LeereRueckgabeListe();

void FilmAusleihen();

void FilmDateiLesen(FILE *filmdatenDatei, FilmDatensatz * beginn);

void FilmListeErstellen();

VerfuegbareMedienAnzahl* FilmNachFilmNummerSuchen(FilmDatensatz *ZuFuellenderDatensatz);

void FilmNachTitelSuchen();

FilmNummer* FilmNummerEingeben();

VerfuegbareMedienAnzahl* FilmSuchen();

void FilmZurueckgeben();

void FuegeEintragZuAusleihliste(Betrag* Betrag, TagesPreis * tagesPreis, FilmNummer* Filmnummer);

void FuegeEintragZuRueckgabeListe(Datum * ausleihDatum, FilmNummer* Filmnummer);

void FuegeEintragZuVerleihdaten(VerleihDatensatz * vds, FILE *verleihdatenDatei);

SuchBegriff* GebeSuchBegriffEin();

Bestaetigung* holeBestaetigung();

Datum* HoleSystemDatum();

KundenIdentifikation* KundenIdentifikationEingeben();

Status * KundeIdentifizieren(KundenDatensatz *ZuFuellenderDatensatz);

void LeereKundendatensatz(KundenDatensatz *Datensatz);

void LeseNaechstenFilmDatensatz(FILE *filmdatenDatei, FilmDatensatz* daten);

VerleihDatensatz * LeseNaechstenVerleihDatensatz(FILE *verleihdatenDatei);

void LoescheEintragAusVerleihDaten(FILE *verleihdatenDatei, VerleihDatensatz * vds);

Ziffer * MenueAuswahl();

Betrag* PreisBerechnen(TagesPreis * preis, AusleihDauer* Dauer);

void RechnungErstellen(GesamtBetrag* Betrag, AusleihDauer* Dauer, AusleihListe* Liste, KundenDatensatz* Datensatz);

Status * RueckgabevorgangBuchen(KundenNummer* Kundennummer);

VerleihDatensatz * VerleihDatenSuchen(KundenNummer* Kundennummer, FilmNummer* Filmnummer);

MedienAnzahl* VerleihPruefen(FilmNummer* FilmNummer);
