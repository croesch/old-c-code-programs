/*
 * Aufgabe 1 & 2:
 * Gibt alle Dateien deren Pfade als übergeben wurden aus.
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 08.02.2010 - 11:08 Uhr
 */

#include <stdio.h>
#include <stdlib.h>

int dateiAusgeben( char *dateipfad );

/*
 * Ruft für jedes Argument einmal die Funktion dateiAusgeben auf.
 * Gibt "0" zurück.
 *
 * argc: Anzahl übergebener Argumente
 * argv: Argumente, welche übergeben worden.
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 08.02.2010 - 11:09 Uhr
 */
int main( int argc, char** argv ) {

    int i;
    for( i = 1; i < argc; ++i ) {

	dateiAusgeben( argv[i] );

    }

    return 0;
}

/*
 * Gibt den Inhalt einer Datei aus.
 * Gibt "0" zurück, wenn kein Fehler auftritt.
 * Gibt "1" zurück, wenn Datei nicht gefunden wurde.
 *
 * dateipfad: Pfad zur Datei, relativ oder absolut.
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 08.02.2010 - 11:09 Uhr
 */
int dateiAusgeben( char *dateipfad ) {

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

    fread( inhalt , sizeof( char ) , groesse, datei );

    //Entfernt bei manchen Dateien "komische Zeichen" am Ende
    inhalt[groesse - 1] = '\0';

    printf( "Datei \"%s\" (%i Zeichen):\n", dateipfad, groesse );
    printf( "%s\n\n", inhalt );

    free( inhalt );
    fclose( datei );

    return 0;
}
