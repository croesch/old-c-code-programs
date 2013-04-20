/*
 * Aufgabe 3-5:
 * Gibt den Inhalt einer Datei Zeilenweise aus.
 * Der Pfad zur Datei wird während des Programms eingegeben. Es wird geprüft,
 * welche Zeilen der Benutzer sehen möchte und ob diese im Dokument vorhanden
 * sind.
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 09.02.2010 - 20:20 Uhr
 */

#include <stdio.h>
#include <stdlib.h>

int dateiZeilenAusgeben( int anfang, int ende, char *dateipfad );
int zaehleZeilen( char *dateipfad );

/*
 * Stellt die Abfragen an den Nutzer, welche Datei und welche Zeilen er davon
 * sehen möchte. Falls die Zeilen nicht valide sind, muss der Benutzer so lange
 * die invaliden Zeilen neu eingeben, bis es passt.
 *
 * Gibt "0" zurück.
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 09.02.2010 - 20:21 Uhr
 */
int main() {

    char dateipfad[100];
    printf( "Gib den Dateipfad an, welche Datei geladen werden soll:\n" );
    fgets( dateipfad, 100, stdin );

    int anzahlZeilen = zaehleZeilen( dateipfad );

    if( anzahlZeilen == -1 ) {
	printf( "Datei konnte nicht geoeffnet werden!\n" );
    } else {

	int anfang = -1, ende = -1;

	while( ( anfang == -1 ) || ( ende == -1 ) ) {

	    printf( "Gib die Zeilen (max. %i) ein, die ausgegeben werden sollen.\n",
		    anzahlZeilen );
	    if( anfang == -1 ) {
		printf( "Erste Zeile: " );
		scanf( "%i", &anfang );
	    }
	    if( ende == -1 ) {
		printf( "Letzte Zeile: " );
		scanf( "%i", &ende );
	    }
	    if( anfang < 1 ) {
		printf( "Die gewaehlte erste Zeile ist zu klein.\n" );
		anfang = -1;
	    }
	    if( ende > anzahlZeilen ) {
		printf( "Die gewaehlte letzte Zeile ist zu gross.\n" );
		ende = -1;
	    }
	    if( anfang > ende ) {
		printf( "Die letzte Zeile muss groesser als die erste sein.\n" );
		anfang = -1;
		ende = -1;
	    }
	    if( ( anfang == -1 ) || ( ende == -1 ) ) {
		printf( "Neue Eingabe erforderlich.\n\n" );
	    }

	}

	dateiZeilenAusgeben( anfang,
		ende,
		dateipfad );
    }

    return 0;
}

/*
 * Gibt den Inhalt einer Datei Zeilenweise aus, mit Enter bekommt der Benutzer
 * die nächste Zeile angezeigt.
 *
 * Gibt "0" zurück, wenn kein Fehler auftritt.
 * Gibt "1" zurück, wenn Datei nicht gefunden wurde.
 *
 * anfang: Erste Zeile die ausgegeben wird (1. Zeile = 1)
 * ende: Letzte Zeile, welche ausgegeben wird (ende > anfang)
 * dateipfad: Pfad zur Datei, relativ oder absolut.
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 09.02.2010 - 20:20 Uhr
 */
int dateiZeilenAusgeben( int anfang, int ende, char *dateipfad ) {

    FILE *datei = NULL;
    datei = fopen( dateipfad, "r" );

    if( datei == NULL ) {
	    printf( "Datei \"%s\" konnte nicht geoeffnet werden\n\n", dateipfad );
	    return 1;
    }

    int groesse = 0;
    fseek( datei, 0, SEEK_END );
    groesse = ftell( datei );

    char *inhalt = malloc( groesse );

    fseek( datei, 0L, SEEK_SET );
    printf( "Druecke Enter um jeweils die naechste Zeile zu sehen:\n" );

    int i;
    for( i = 1; ftell( datei ) < groesse ; ++i ) {

	fgets( inhalt, 80, datei ); //Standardterminalbreite von 80

	if( i >= anfang && i <= ende ) {
	    
	    getchar(); //Bei mehreren Zeichen werden mehrere Zeilen ausgegeben
            printf( "%s", inhalt );

	}
	if( i > ende ) {
	    break;
	}
    }

    free( inhalt );
    fclose( datei );

    return 0;
}

/*
 * Zählt die Anzahl an Zeilen.
 * Gibt "-1" zurück, wenn Datei nicht gefunden wurde.
 * Gibt sonst Anzahl der Zeilen zurück.
 *
 * dateipfad: Pfad zur Datei, relativ oder absolut.
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 09.02.2010 - 20:20 Uhr
 */
int zaehleZeilen( char *dateipfad ) {

    FILE *datei = NULL;
    datei = fopen( dateipfad, "r" );

    if( datei == NULL ) {
	    printf( "Datei \"%s\" konnte nicht geoeffnet werden\n\n", dateipfad );
	    return -1;
    }

    int groesse = 0;
    fseek( datei, 0, SEEK_END );

    groesse = ftell( datei );

    fseek( datei, 0L, SEEK_SET );

    char *inhalt = malloc( 80 );
    int i;
    for( i = 1; ftell( datei ) < groesse ; ++i ) {

	fgets( inhalt, 80, datei ); //Standardterminalbreite von 80

    }

    free( inhalt );
    fclose( datei );

    return i;

}
