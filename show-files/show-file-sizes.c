/*
 *
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 04.03.2010 - 11:20 Uhr
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void entferneUmbruch( char string[] );
int indexAuslesen( char *dateipfad );
void indexDateiLesen();
int dateiGroesse( char *dateipfad );
void leereBildschirm();


/*
 * Ruft indexDateiLesen auf, falls kein Argument angegeben wurde. Ansonsten
 * ruft indexAuslesen mit dem ersten Argument auf.
 *
 * return EXIT_SUCCESS: Falls das Programm fehlerfrei beendet.
 *
 * param argc: Anzahl der Argumente
 * param argv: Pointer auf Charpointer der Argumente
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 04.03.2010 - 11:20 Uhr
 */
int main( int argc, char** argv ) {

    leereBildschirm();

    if( argc > 1 ) {

	indexAuslesen( argv[1] );

    } else {

	indexDateiLesen();

    }

    return ( EXIT_SUCCESS );
}

/*
 * Entfernt in einem String alle vorkommenden \n durch Verschieben aller
 * nachfolgender Zeichen.
 * Verändert nichts, falls kein \n vorhanden ist.
 *
 * param string: String mit zu entfernenden \n - Zeichen.
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 04.03.2010 - 11:20 Uhr
 */
void entferneUmbruch( char string[] ) {

    int laenge = strlen( string );
    int i = 0;

    for( i = 0; i < laenge; ++i ) {

	if( string[i] == '\n' ) {

	    int j = i;
	    while( j < laenge ) {
		//Verschiebe alle folgenden Zeichen um eine Position nach vorne
		string[j] = string[j+1];
		++j;
	    }
	    //Zum Prüfen ob an aktueller Stelle evtl "\n" nachgerückt ist.
	    --i;
	}
    }
}

/*
 * Liest die Datei Zeile für Zeile aus und erwartet pro Zeile einen Dateipfad.
 * Die Größe der Dateien und die Gesamtgröße aller werden ausgegeben.
 *
 * return -1: Indexdatei lässt sich nicht öffnen.
 * return 1: Kein Fehler (Ist ein Dateipfad nicht erreichbar -> kein Fehler)
 *
 * param dateipfad: Charpointer der Dateipfad enthält, wird ungeprüft an fopen
 *		    übergeben.
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 04.03.2010 - 11:20 Uhr
 */
int indexAuslesen( char *dateipfad ) {

    FILE *datei = NULL;
    datei = fopen( dateipfad, "r" );

    if( datei == NULL ) {

	printf( "Datei \"%s\" konnte nicht geoeffnet werden\n\n", dateipfad );
        return -1;

    }

    char zeile[100] = { 0 };

    fseek( datei, 0, SEEK_END );
    int dateiEnde = ftell( datei );

    fseek( datei, 0L, SEEK_SET );
    leereBildschirm();

    int groesseDatei = 0, gesamtGroesse = 0, i = 0;
    for( i = 0; ftell( datei ) < dateiEnde ; ++i ) {

	fgets( zeile, 98, datei ); //Standardterminalbreite von 80
	entferneUmbruch( zeile );

	groesseDatei = dateiGroesse( zeile );

	if( groesseDatei == -1 ) {

	    printf( "Datei \"%s\" konnte nicht geoeffnet werden.\n\n", zeile );

	} else {

	    gesamtGroesse += groesseDatei;
	    printf( "%s\n\t\t\t\t\t%i Byte\n", zeile, groesseDatei );

	}
    }

    printf( "============================================================\n" );
    printf( "Gesamtgroesse:\t\t\t\t%i Byte\n\n", gesamtGroesse );

    fclose( datei );

    return 1;
}


/*
 * Gibt die Anfrage aus, welche Datei der Benutzer öffnen will und übergibt
 * diese an "indexAuslesen".
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 04.03.2010 - 11:20 Uhr
 */
void indexDateiLesen() {

    char pfad[200] = { 0 };

    printf( "Gib den Dateipfad an, welche Datei geladen werden soll:\n" );
    fgets( pfad, 198, stdin );
    entferneUmbruch( pfad );

    indexAuslesen( pfad );
}


/*
 * Gibt die Größe einer Datei zurück. Setzt den Dateizeiger an das Ende der Datei
 * und gibt diese Position als Größe der Datei zurück.
 *
 * return -1: Wenn die Datei sich nicht öffnen lässt
 * return X: Wobei X die Größe der Datei ist
 *
 * param dateipfad: Dateipfad zur Datei, deren Groesse ermittelt werden soll,
 *		    wird ungeprüft an fopen übergeben!
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 04.03.2010 - 11:20 Uhr
 */
int dateiGroesse( char *dateipfad ) {

    FILE *datei = NULL;
    datei = fopen( dateipfad, "r" );

    if( datei == NULL ) {

	return -1;

    }

    int groesse = 0;
    fseek( datei, 0, SEEK_END );

    groesse = ftell( datei );
    fclose( datei );

    return groesse;
}

/*
 * Leert den Bildschirm und gibt mit printf die Programmüberschrift aus
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 04.03.2010 - 11:20 Uhr
 */
void leereBildschirm() {

    system( "clear" );
    printf( "Ausgeben von Dateigroessen anhand einer Indexdatei.\n" );
    printf( "V. 1.0 - Autor Christian Roesch\n\n" );

}