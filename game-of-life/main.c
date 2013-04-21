/* 
 * File:   main.c
 * Author: christian
 *
 * Created on 22. Februar 2010, 09:02
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

short **zellWerte = NULL;
int hoehe = 20, breite = 40;

int zaehleLebendeNachbarn( int spalte, int zeile, int spaltenMax, int zeilenMax ) {

    int nachbarn = 0;

    int linkeSpalte = spalte - 1;
    int rechteSpalte = spalte + 1;
    int obereZeile = zeile - 1;
    int untereZeile = zeile + 1;

    if( spalte == 0 ) {
	linkeSpalte = spaltenMax;
    }
    if( zeile == 0 ) {
	obereZeile = zeilenMax;
    }
    if( spalte == spaltenMax ) {
	rechteSpalte = 0;
    }
    if( zeile == zeilenMax ) {
	untereZeile = 0;
    }

    nachbarn += zellWerte[obereZeile][linkeSpalte];
    nachbarn += zellWerte[zeile][linkeSpalte];
    nachbarn += zellWerte[untereZeile][linkeSpalte];
    nachbarn += zellWerte[obereZeile][spalte];
    nachbarn += zellWerte[untereZeile][spalte];
    nachbarn += zellWerte[obereZeile][rechteSpalte];
    nachbarn += zellWerte[zeile][rechteSpalte];
    nachbarn += zellWerte[untereZeile][rechteSpalte];

    return nachbarn;
}

void feldBerechnen() {

    short **naechsterZug = NULL;
    naechsterZug = malloc( hoehe * sizeof( short * ) );

    int i = 0;
    for( i = 0; i < hoehe; ++i ) {
	naechsterZug[i] = malloc( breite * sizeof( short ) );
	memcpy( naechsterZug[i], zellWerte[i], sizeof( short ) * breite );
    }

    int j = 0, nachbarn = 0;
    //Zeilen
    for( i = 0; i < hoehe; i++ ) {
	//Spalten
	for( j = 0; j < breite; j++ ) {
	    nachbarn = zaehleLebendeNachbarn( j, i, breite - 1, hoehe - 1 );
	    if( zellWerte[i][j] ) {
		if( nachbarn == 2 || nachbarn == 3 ){
		    naechsterZug[i][j] = 1;
		} else {
		    naechsterZug[i][j] = 0;
		}
	    } else {
		if( nachbarn == 3 ){
		    naechsterZug[i][j] = 1;
		} else {
		    naechsterZug[i][j] = 0;
		}
	    }

	    }
    }

    for( i = 0; i < hoehe; ++i ) {
	memcpy( zellWerte[i], naechsterZug[i] ,sizeof( short ) * breite );
	free( naechsterZug[i] );
    }
    free( naechsterZug );

}

/*
 * Erzeugt das Spielfeld mit variabler Breite, Höhe, Zellenhöhe.
 * Die Zellenbreite hängt von der Höhe ab, es wird angestrebt ein quadratisches
 * Feld zu erreichen. Der Wert der Zelle wird möglichst zentriert geschrieben.
 *
 * breite: Anzahl der Spalten
 * hoehe: Anzahl der Zeilen
 * zellenHoehe: Höhe einer einzelnen Zelle in Zeichen
 * hilfe: 1, wenn Ziffern 1-9 ausgegeben werden sollen
 *
 * AUTOR: Christian Rösch
 * Zuletzt geändert am 18. Januar 2010, 19:42
 */
void feldAusgeben() {

    int i, j = 0;
    //Zeilen
    for( i = 0; i < hoehe; i++ ) {
	//Spalten
	for( j = 0; j < breite; j++ ) {

	    if( zellWerte[i][j] ) {
		printf( "# " ); //Zeichen für lebendige Zellen
	    } else {
		printf( "  " ); //Zeichen für tote Zellen
	    }

        }
	printf( "\n" );
    }

    printf( "\n" );
}

void leereBildschirm() {

    system( "clear" );
    printf( "Game of life V. 1.0:\n" );

}

void entferneUmbruch( char string[] ) {

    int laenge = strlen( string );

    int i = 0;
    for( i = 0; i < laenge; ++i) {

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

int istGOLDatei( char *dateipfad ) {

    FILE *datei = NULL;
    datei = fopen( dateipfad, "r" );

    if( datei == NULL ) {
	return 0; //Datei nicht vorhanden
    }

    fseek( datei, 0, SEEK_END );
    if( ftell( datei ) == 0 ) {

	fclose( datei );
	return -1;	//Datei leer
    }

    char ersteZeile[24];
    fseek( datei, 0L, SEEK_SET );

    fread( ersteZeile, sizeof( char )*24, 1, datei );

    if( strstr( ersteZeile, "gameoflifedateiv.1.0-" ) ) {

	fclose( datei );
	return 1; //Datei von Version 1.0
    }

    fclose( datei );

    return -2; //Unbekanntes Format
}

int inDateiSchreiben( char *dateipfad) {

    FILE *datei = NULL;
    datei = fopen( dateipfad, "w+" );

    if( datei == NULL ) {
	    return -1;
    }

    //Datei als Adressbuchdatei signieren:
    fprintf( datei, "gameoflifedateiv.1.0-%i-%i\n", hoehe, breite );

    int i = 0, j = 0;
    for( i = 0; i < hoehe; ++i ) {
	for( j = 0; j < breite; ++j ) {
	    fprintf( datei, "%i", zellWerte[i][j] );
	}
	fprintf( datei, "\n" );
    }



    fclose( datei );

    return 1;
}


int zustandSpeichern() {

    char dateipfad[100];
    printf( "Gib den Dateipfad an, wo die Datei gespeichert werden soll:\n" );
    fgets( dateipfad, 100, stdin );

    entferneUmbruch( dateipfad );

    int dateiFormat = istGOLDatei( dateipfad );
    if( dateiFormat == -2 ) {
	//Dateiformat unbekannt / wird nicht unterstützt
	printf( "Die Datei hat ein nicht unterstuetztes Format. Aus Sicher" );
	printf( "heitsgruenden kann diese nicht ueberschrieben werden.\n" );
	return -2;
    }

    int benutzerEntscheidung = 0;
    if( dateiFormat == 1 ) {
	//Datei vorhanden passendes Format
	printf( "\nDie Datei ist bereits vorhanden, moechten Sie diese ueber" );
	printf( "schreiben?\n(Achtung, ueberschriebene Daten gehen verloren!)\n" );
	printf( "Geben Sie die Ziffer 1 ein um die Datei zu ueberschreiben. " );
	printf( "\nGeben Sie 0 ein um den Vorgang abzubrechen: " );
	scanf( "%i", &benutzerEntscheidung );

	if( benutzerEntscheidung != 1 ) {
	    //Benutzer bricht das Überschreiben ab
	    return 0;
	}
	getchar();
    }

    if( dateiFormat == 0 || dateiFormat == -1 || benutzerEntscheidung == 1 ) {
	//Datei nicht vorhanden, leer oder Benutzer will überschreiben
	if( inDateiSchreiben( dateipfad ) ) {

	    printf( "Spielzustand wurde erfolgreich gespeichert.\n" );

	} else {

	    printf( "Spielzustand konnte nicht gespeichert werden.\n" );
	}
    }

    return 1;
}

void speicherReservierung() {

    zellWerte = malloc( hoehe * sizeof( short * ) );

    int i = 0;
    for( i = 0; i < hoehe; ++i ) {
	zellWerte[i] = malloc( breite * sizeof( short ) );
    }

}

void speicherFreigabe() {

    int i = 0;
    for( i = 0; i < hoehe; ++i ) {
	free( zellWerte[i] );
    }
    free( zellWerte );

}


int zustandLaden() {

    char pfad[100];

    printf( "Gib den Dateipfad an, welche Datei geladen werden soll:\n" );
    fgets( pfad, 100, stdin );
    entferneUmbruch( pfad );

    int dateiFormat = istGOLDatei( pfad );
    if( dateiFormat != 1 ) {

	printf( "Datei konnte nicht geladen werden. " );
	if( dateiFormat == 0 ) {

	    printf( "Datei nicht vorhanden.\n" );
	} else if( dateiFormat == -1 ) {

	    printf( "Datei ist leer.\n" );
	} else {

	    printf( "Unbekanntes Format.\n" );
	}

	return 0;
    }

    FILE *datei = NULL;
    datei = fopen( pfad, "r" );
    if( datei == NULL ) {

	printf( "Datei konnte nicht geoeffnet werden.\n" );
	return -1;
    }

    fseek( datei, 0, SEEK_SET );

    speicherFreigabe();
    //zellWerte = NULL;

    fscanf( datei, "gameoflifedateiv.1.0-%i-%i\n", &hoehe, &breite );

    speicherReservierung();

    int i = 0, j = 0;
    for( i = 0; i < hoehe; ++i ) {
	for( j = 0; j < breite; ++j ) {
	    char gelesen = '0';
	    fscanf( datei, "%c", &gelesen );
	    if( gelesen == '1' ) {
		zellWerte[i][j] = 1;
	    } else {
		zellWerte[i][j] = 0;
	    }
	}
	fscanf( datei, "\n" );
    }

    printf( "Zustand erfolgreich geladen.\n" );

    fclose( datei );
    return 1;
}


void starteSpiel() {

    int schritte = 10000;
    int dauerDurchlauf = 0;

    int i = 0;
    for( i = 0; i < schritte; ++i ) {
        leereBildschirm();

	feldAusgeben();
	feldBerechnen();
	if( !dauerDurchlauf ) {
	    printf( "Aktion:\t0 = Programm beenden\n\t1 = naechster Schritt\n" );
	    printf( "\t2 = Zustand laden\n\t3 = Zustand speichern:\n" );
	    printf( "\t4 = Schleifendurchlauf (ca. 15 min)\n" );
	    int eingabe = fgetc( stdin );
	    while( getchar() != '\n' );
	    switch( eingabe ) {
		case '0':
		    i = schritte + 1;
		    break;
		case '1':
		    //Nix zu tun, da nächster Schritt verlangt wird.
		    break;
		case '2':
		    zustandLaden();
		    break;
		case '3':
		    zustandSpeichern();
		    break;
		case '4':
		    dauerDurchlauf = 1;
		    break;
		default:
		    break;
	    }
	}
	usleep(150000);
    }

}


/*
 * 
 */
int main(int argc, char** argv) {

    srand( time( NULL ) );
    leereBildschirm();

    //TODO: Breite und Höhe einlesen!

    speicherReservierung();

    int j = 0, i = 0;
    //Zeilen
    for( i = 0; i < hoehe; ++i ) {
	//Spalten
	for( j = 0; j < breite; ++j ) {
	    zellWerte[i][j] = rand()%2;
        }
    }

    starteSpiel();

    speicherFreigabe();

    return (EXIT_SUCCESS);
}

