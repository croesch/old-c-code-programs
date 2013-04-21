/*
 ============================================================================
 Name        : Videotheksystem.c
 Author      : Christian Rösch
 Created on  : Jun 4, 2011
 Description : Videotheksystem - Hauptprogramm, Start
 ============================================================================
 */
#include "Videotheksystem.h"

/*
 * Hauptprogramm zur Steuerung des Programmablaufs
 */
void VideothekSystem() {
	// Signal fuer Programmende
	int Ende = 0;
	while (Ende == 0) {
		// Zeige Menue an und forder zur Auswahl auf
		Ziffer * auswahl = MenueAuswahl();
		// Leerer Container, der zum Aufruf fuer Filmsuchen benoetigt wird
		FilmDatensatz* leererDatensatz = initialisiereFilmDatensatz();
		// Leerer Container um allokierten Speicher freigeben zu koennen
		VerfuegbareMedienAnzahl* anz = NULL;

		// Reagiere auf Benutzereingabe
		switch (auswahl->wert) {
			case 1:
				// Benutzer moechte nach einem Film suchen
				anz = FilmSuchen(leererDatensatz);
				// gebe intern allokierten Restspeicher frei
				gebeVerfuegbareMedienAnzahlFrei(anz);
				break;
			case 2:
				// Kunde will einen Film suchen
				FilmAusleihen();
				break;
			case 3:
				// Kunde will einen Film zurueckgeben
				FilmZurueckgeben();
				break;
			case 4:
				// Kunde will einen Film zurueckgeben ohne vorher nach Film zu suchen
				BezahlungPruefen();
				break;
			case 5:
				// Ausgeliehenen Filme werden aufgelistet
				AusgelieheneFilmeAuflisten();
				break;
			case 6:
				// Programm wird beendet
				Ende = 1;
				break;
		}
		// Gebe allokierten Speicher frei
		gebeFilmDatensatzFrei(leererDatensatz);
		gebeZifferFrei(auswahl);
	}
	// Gebe noch im Speicher befindliche Listen frei
	gebeRueckgabeListeFrei(rueckgabeListe);
	gebeAusleihListeFrei(ausleihListe);
}

/*
 * Start des Programms und Aufruf des Hauptprogramms Videotheksystem
 */
int main() {
	VideothekSystem();

	return 0;
}
