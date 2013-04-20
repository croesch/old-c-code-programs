/*
 * Dies ist ein Adressenverwaltungsprogramm, man kann beliebig (Wert theoretisch
 * begrenzt) viele Adressen eingeben und sich das gesamt Adressbuch anzeigen
 * lassen. Speichern und Laden wird unterstützt, sowie das suchen nach Einträgen,
 * die einen gewissen String im Namen-Attribut enthalten.
 * Einträge löschen wird noch nicht unterstützt.
 *
 * Lädt bei Programmstart automatisch ein Adressbuch, sofern als zweites Argument
 * übergeben.
 *
 * Benutzer sollte das Programm über das Menü beenden, da dadurch der für die
 * Adressbucheinträge reservierte Speicher wieder freigegeben wird.
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 *
 * Zuletzt geändert: 16. Februar 2010, 22:40 Uhr
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringfunctions.h"

typedef struct adresse {
    char vname[32];
    char name[32];
    char strasse[52];
    char plz[7];
    char ort[32];
    struct adresse *naechsterEintrag;
} Adresse;

Adresse *anfang = NULL;

Adresse *letzterEintrag( Adresse *eintrag );
void eintragAusgeben( Adresse *eintrag );
void eintragEinlesen();
void ablaufSteuern();
void menueAnzeigen();
void leereBildschirm();
void adressbuchAusgeben();
void eintragFinden();
Adresse *eintragSuchen( Adresse *anfangsElement, char suchString[] );
void eintragFinden();
int adressbuchSpeichern();
int adressbuchInDateiSchreiben( char *dateipfad );
int adressbuchLaden( char *dateipfad );
int istAdressbuchDatei( char *dateipfad );
void speicherFreigabe();

/*
 * Ruft Funktion zur Ablaufsteuerung auf und gibt anschließend, sobald diese
 * terminiert (im Falle des korrekten Beendens durch Benutzer) den reservierten
 * Speicher frei.
 * Falls im zweiten (wichtig!) Argument die Adresse für ein Adressbuch übergeben
 * wird, wird dies bei Programmstart automatisch geladen.
 *
 * argc: Anzahl übergebener Argumente
 * argv: Übergebene Argumente
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 *
 * Zuletzt geändert: 09. Februar 2010, 22:11 Uhr
 */
int main( int argc, char **argv ) {

    if( argc > 1 ) {
	adressbuchLaden( argv[1] );
    }

    ablaufSteuern();

    speicherFreigabe();

    return ( EXIT_SUCCESS );
}


/*
 * Gibt angefangen vom Pointer anfang die Einträge im Adressbuch wieder frei.
 * 
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 *
 * Zuletzt geändert: 16. Februar 2010, 22:50 Uhr
 */
void speicherFreigabe() {

    //Speicherfreigabe nach Programmdurchlauf
    Adresse *zuLoeschen = anfang;
    while( zuLoeschen != NULL ) {

	Adresse *naechstesZuLoeschen = zuLoeschen->naechsterEintrag;

	free( zuLoeschen );
	printf( "Speicher (%p) wurde freigegeben.\n", zuLoeschen );

	zuLoeschen = naechstesZuLoeschen;
    }

}

/*
 * Schreibt das Adressbuch in die Datei, welche übergeben wurde.
 * Prüft nicht, ob speichern erwünscht ist. Schreibt zeilenweise die Werte,
 * erste Zeile ist ein definierter Header der V1.0
 *
 * dateipfad: Pfad zur Datei, in die gespeichert wird.
 *
 * Gibt -1 zurück, wenn Datei nicht geöffnet werden konnte.
 * Gibt 1 zurück, falls ordnungsgemäß gespeichert werden konnte
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 *
 * Zuletzt geändert: 09. Februar 2010, 21:50 Uhr
 */
int adressbuchInDateiSchreiben( char *dateipfad ) {

    FILE *datei = NULL;
    datei = fopen( dateipfad, "wr" );

    if( datei == NULL ) {
	    return -1;
    }

    //Datei als Adressbuchdatei signieren:
    fprintf( datei, "Adressbuch-Adressen-V1.0\n" );

    Adresse *eintrag = anfang;
    while( eintrag != NULL ) {
	fprintf( datei, "%s\n", eintrag->vname );
	fprintf( datei, "%s\n", eintrag->name );
	fprintf( datei, "%s\n", eintrag->strasse );
	fprintf( datei, "%s\n", eintrag->plz );
	fprintf( datei, "%s\n", eintrag->ort );

	eintrag = eintrag->naechsterEintrag;
    }

    fclose( datei );

    return 1;
}

/*
 * Prüft ob eine Datei eine Adressbuchdatei ist.
 *
 * dateipfad: Pfad der zu überprüfenden Datei.
 *
 * Gibt -2 zurück, wenn Datei ein unbekanntes Format hat.
 * Gibt -1 zurück, wenn die Datei leer ist.
 * Gibt 0 zurück, wenn die Datei nicht vorhanden ist.
 * Gibt 1 zurück, falls Datei das Format für AdressbuchV1.0 vorweist
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 *
 * Zuletzt geändert: 09. Februar 2010, 21:50 Uhr
 */
int istAdressbuchDatei( char *dateipfad ) {

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

    if( enthaeltString( ersteZeile, "Adressbuch-Adressen-V1.0" ) ) {

	fclose( datei );
	return 1; //Datei von Version 1.0
    }

    fclose( datei );

    return -2; //Unbekanntes Format
}

/*
 * Lädt das Adressbuch aus einer Datei, sofern das Format (erste Zeile) passt.
 * Wenn Dateipfad != NULL, wird dieser verwendet, sonst wird nachgefragt.
 *
 * Gibt -1 zurück, falls Datei zwar das passende Format besitzt aber nicht
 *	geöffnet werden kann.
 * Gibt 0 zurück, wenn die Datei nicht geladen werden konnte.
 * Gibt 1 zurück, falls ordnungsgemäß geladen werden konnte
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 *
 * Zuletzt geändert: 16. Februar 2010, 22:50 Uhr
 */
int adressbuchLaden( char *dateipfad ) {

    /*
     * Ich benötige diese lokale Variable, da sonst das manuelle Laden und laden
     * per Argumentübergabe nicht gleichzeitig funktioniert hat. Ich konnte nicht
     * erneut Daten für Dateipfad einlesen in Zeile 209. So funktioniert es.
     */
    char pfad[100];

    if( dateipfad == NULL ) {
	printf( "Gib den Dateipfad an, welche Datei geladen werden soll:\n" );
	fgets( pfad, 100, stdin );
	entferneUmbruch( pfad );
    } else {
	strcpy( pfad, dateipfad );
    }

    int dateiFormat = istAdressbuchDatei( pfad );
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

    fseek( datei, 0, SEEK_END );
    int groesse = ftell( datei );
    fseek( datei, 0, SEEK_SET );

    char ersteZeile[80];
    fgets( ersteZeile, 80, datei ); //damit die "Signierung" nicht geladen wird

    //Speicherleck gefixt, eingegebene Einträge wurden sonst nicht wieder
    // freigegeben.
    speicherFreigabe();

    Adresse *neu = NULL;
    int i;
    for( i = 1; ftell( datei ) < groesse; ++i ) {

	if( ( neu = malloc( sizeof( Adresse ) ) ) == NULL ) {
	    printf( "ERR:\tKonnte kein Speicherplatz reservieren\n");
	}

	fgets( neu->vname, 30, datei );
	fgets( neu->name, 30, datei );
	fgets( neu->strasse, 50, datei );
	fgets( neu->plz, 7, datei );
	fgets( neu->ort, 30, datei );

	entferneUmbruch( neu->vname );
	entferneUmbruch( neu->name );
	entferneUmbruch( neu->strasse );
	entferneUmbruch( neu->plz );
	entferneUmbruch( neu->ort );

	if( i == 1 ) { //Erster Eintrag

	    anfang = neu;
	} else {

	    Adresse *letzter = letzterEintrag( anfang );
	    letzter->naechsterEintrag = neu;
	}

	neu = neu->naechsterEintrag;
    }

    printf( "%i Eintraege erfolgreich geladen.\n", i-1 );

    fclose( datei );
    return 1;
}

/*
 * Speichert das Adressbuch. Fragt nach einem Speicherort, falls dies eine
 * bestehende Datei ist und diese nicht das Format von AdressbuchV1.0 hat, so
 * kann diese nicht überschrieben werden. Leere Dateien werden beschrieben.
 *
 * Gibt -2 zurück, wenn Datei existiert, aber keine Adressdatei ist.
 * Gibt 0 zurück, wenn die Datei existiert, eine Adressdatei ist, der Benutzer
 *	diese aber nicht überschreiben möchte.
 * Gibt 1 zurück, falls ordnungsgemäß gespeichert werden konnte
 * 
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 *
 * Zuletzt geändert: 16. Februar 2010, 22:40 Uhr
 */
int adressbuchSpeichern() {

    char dateipfad[100];
    printf( "Gib den Dateipfad an, wo die Datei gespeichert werden soll:\n" );
    fgets( dateipfad, 100, stdin );
    
    entferneUmbruch( dateipfad );

    int dateiFormat = istAdressbuchDatei( dateipfad );
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
	if( adressbuchInDateiSchreiben( dateipfad ) ) {

	    printf( "Adressbuch wurde erfolgreich gespeichert.\n" );

	} else {

	    printf( "Adressbuch konnte nicht gespeichert werden.\n" );
	}
    }
    
    return 1;
}

/*
 * Fragt den Benutzer welchen String er in den Namen der Einträge suchen möchte
 * und gibt alle Einträge auf dem Bildschirm aus, die dazu passen.
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 *
 * Zuletzt geändert: 01. Februar 2010, 11:11 Uhr
 */
void eintragFinden() {

    char suchString[100];
    int eintragGefunden = 0;
    printf( "Gib einen (Teil des) Namen ein, nach dem du suchen moechtest: " );
    fgets( suchString, 30, stdin );
    entferneUmbruch( suchString );

    Adresse *gefunden = eintragSuchen( anfang, suchString );

    while( gefunden != NULL ) {

	eintragGefunden = 1;
	eintragAusgeben( gefunden );
	gefunden = eintragSuchen( gefunden->naechsterEintrag, suchString );
    }

    if( !eintragGefunden ) {

	printf( "Keinen Eintrag gefunden!\n" );
    }
}

/*
 * Sucht ab einem bestimmten Element in allen nachfolgenden Elementen (bis zum
 * NULL-Element) einen übergebenen String im Namen der Einträge.
 *
 * Gibt den ersten gefundenen Eintrag zurück
 * Gibt NULL zurück, falls bis zum Abbruch der Kette kein Element gefunden wird
 *
 * anfangsElement: Element, bei dem die Suche beginnt (inkl.)
 * suchString: zu suchender (Teil-)String des Namens in den Einträgen
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 *
 * Zuletzt geändert: 01. Februar 2010, 11:11 Uhr
 */
Adresse *eintragSuchen( Adresse *anfangsElement, char suchString[] ) {

    Adresse *suchElement = anfangsElement;

    while( suchElement != NULL ) {

	if( enthaeltString( suchElement->name, suchString ) ) {

	    return suchElement;
	}

	suchElement = suchElement->naechsterEintrag;
    }

    return NULL;
}

/*
 * Gibt alle Adressbucheinträge aus, vom Anfangselement anfang solange immer
 * das nachfolgende Element, bis eines davon NULL ist.
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 *
 * Zuletzt geändert: 01. Februar 2010, 11:11 Uhr
 */
void adressbuchAusgeben() {

    Adresse *auszugeben = anfang;

    do {

	eintragAusgeben( auszugeben );

	auszugeben = auszugeben->naechsterEintrag;

    } while( auszugeben != NULL );
}


/*
 * Dies ist der eigentliche Programmablauf. Liest immer wieder die gewünschte
 * Option ein, die der Benutzer ausführen möchte.
 * So lange der Benutzer nicht Aktion zum Beenden wählt,
 * zeigt das Menü an,
 * fragt den Benutzer was er machen möchte,
 * führt gewünschte Aktion des Benutzers aus (sofern möglich).
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 *
 * Zuletzt geändert: 09. Februar 2010, 21:00 Uhr
 */
void ablaufSteuern() {

    char option[20];
    leereBildschirm();

    do {
	menueAnzeigen();
	printf( "Nr. der Option eingeben (gib eine Ziffer ein): " );
	fgets( option, 20, stdin );

	leereBildschirm();

	switch( option[0]  ) {

	    case '1':
		eintragEinlesen();
		break;

	    case '2':
		if( anfang != NULL ) {
		    eintragFinden();
		} else {
		    printf( "Es sind keine Eintraege vorhanden.\n" );
		}
		break;

	    case '3':
		if( anfang != NULL ) {
		    adressbuchAusgeben();
		} else {
		    printf( "Es sind keine Eintraege vorhanden.\n" );
		}
		break;

	    case '4':
		if( anfang != NULL ) {
		    adressbuchSpeichern();
		} else {
		    printf( "Es sind keine Eintraege vorhanden.\n" );
		}
		break;

	    case '5':
		adressbuchLaden( NULL );
		break;

	    case '6':
		break;

	    default:
		printf( "Ungueltige Eingabe ..\n" );
		break;
	}

    } while( option[0] != '6' );
    
}

/*
 * Zeigt die Möglichkeiten an, welche der Nutzer hat. Keine Aktionen nur Ausgabe.
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 *
 * Zuletzt geändert: 09. Februar 2010, 21:00 Uhr
 */
void menueAnzeigen() {

    printf( "\nDu hast nun folgende Optionen:\n" );

    printf( "1.:\tNeuen Eintrag hinzufuegen ...\n" );

    if( anfang != NULL ) {
        printf( "2.:\tNach Eintrag suchen ...\n" );
	printf( "3.:\tAlle Adressen anzeigen\n" );
        printf( "4.:\tAdressbuch speichern ...\n" );
    }

    printf( "5.:\tVorhandenes Adressbuch laden ...\n" );
    printf( "6.:\tProgramm beenden!\n\n" );
}

/*
 * Leert den Bildschirminhalt und gibt die Überschrift des Programms aus.
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 *
 * Zuletzt geändert: 01. Februar 2010, 11:11 Uhr
 */
void leereBildschirm() {

    system( "clear" );
    printf( "Adressbuch V. 1.0:\n\n" );

}

/*
 * Liest einen neuen Adressbucheintrag ein, der als Nachfolger des letzten
 * Eintrages der Kette hinzugefügt wird.
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 *
 * Zuletzt geändert: 16. Februar 2010, 22:50 Uhr
 */
void eintragEinlesen() {

    Adresse *neu = NULL;
    if( anfang == NULL ) {

	if( ( anfang = malloc( sizeof( Adresse ) ) ) == NULL ) {
	    printf( "ERR:\tKonnte kein Speicherplatz reservieren\n");
	}

	neu = anfang;

    } else {

	Adresse *last = letzterEintrag( anfang );

	if( ( last->naechsterEintrag = malloc( sizeof( Adresse ) ) ) == NULL ) {
	    printf( "ERR:\tKonnte kein Speicherplatz reservieren\n");
	}

	neu = last->naechsterEintrag;
    }

    printf( "Neue Adresse eingeben [Anzahl zulaessige Zeichen]:\n");

    printf( "Vorname [30]:\t" );
    fgets( neu->vname, 32, stdin );

    printf( "Nachname [30]:\t" );
    fgets( neu->name, 32, stdin );

    printf( "Straße [50]:\t" );
    fgets( neu->strasse, 52, stdin );

    printf( "PLZ [5]:\t" );
    fgets( neu->plz, 7, stdin );

    printf( "Ort [30]:\t" );
    fgets( neu->ort, 32, stdin );

    entferneUmbruch( neu->vname );
    entferneUmbruch( neu->name );
    entferneUmbruch( neu->strasse );
    entferneUmbruch( neu->plz );
    entferneUmbruch( neu->ort );
}


/*
 * Gibt einen Adressbucheintrag auf dem Terminal aus.
 *
 * eintrag: Element, welches dargestellt werden soll.
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 *
 * Zuletzt geändert: 01. Februar 2010, 11:11 Uhr
 */
void eintragAusgeben( Adresse *eintrag ) {

    printf( "Name:\t\t%s, %s\n", eintrag->name, eintrag->vname );

    printf( "Strasse:\t%s\n", eintrag->strasse );

    printf( "Ort:\t\t%s %s\n\n", eintrag->plz, eintrag->ort );
}

/*
 * Findet den letzten Eintrag in der Kette der Adressen.
 * Gibt den Eintrag zurück, welcher der erste ist, der als Nachfolger ein
 * NULL-Element hat. (Sollte in der Theorie dann der letzte Eintrag sein)
 *
 * eintrag: Beginn der Suche nach dem letzten Element.
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert: 01. Februar 2010, 11:11 Uhr
 */
Adresse* letzterEintrag( Adresse *eintrag ) {

    while( eintrag->naechsterEintrag != NULL ) {

	eintrag = eintrag->naechsterEintrag;

    }

    return eintrag;
}
