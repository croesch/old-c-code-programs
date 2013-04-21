/*
 ============================================================================
 Name        : MenueAuswahl.c
 Author      : Johann Deter
 Created on  : Jun 7, 2011
 Description : Zeigt das Menue an und liest die Auswahl des Benutzers ein.
 Rueckgabe   : Die vom Benutzer getroffene Auswahl
 ============================================================================
 */

#include "Videotheksystem.h"

Ziffer * MenueAuswahl() {

	// Initialisierung des Rueckgabewertes
	Ziffer * ziffer = initialisiereZiffer();

	// Menue anzeigen
	TitelAusgeben("Menue");
	TextAusgeben("  1: Film suchen");
	TextAusgeben("  2: Film ausleihen");
	TextAusgeben("  3: Film zurueckgeben");
	// Verkuerztes Verfahren, falls Filmnummer bekannt ist
	TextAusgeben("  4: Film zurueckgeben (ohne Filmliste erstellen)");
	TextAusgeben("  5: ausgeliehene Filme auflisten");
	TextAusgeben("  6: Programm beenden");
	TextAusgeben("---------------------------------");
	TextOhneUmbruchAusgeben("Menueauswahl: ");

	// Lese Wahl des Benutzers
	scanf("%d", &ziffer->wert);

	// Gebe die Auswahl zurueck
	return ziffer;
}
