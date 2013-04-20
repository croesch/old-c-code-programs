/* 
 * Datei:   main.c
 * Übungen vom 01.02.2010
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 *
 * Zuletzt geändert am: 15.02.2010 - 10:05 Uhr
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *stringKopierer( char *string );
int speicherreservierung( long int n, int *zeiger );
void aufgabe1();
void aufgabe2();
void aufgabe3();
void aufgabe4();
void aufgabe5();

/*
 * Ruft die versch. Aufgaben auf.
 * Programm zum Anzeigen der Ergebnisse der Übungen vom 01.02.2010.
 *
 * gibt 0 zurück wenn keine Probleme auftreten.
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 01.02.2010 - 21:00 Uhr
 */
int main() {

    printf( "Aufgabe 1:\n");
    aufgabe1();

    printf( "Aufgabe 2:\n");
    aufgabe2();

    printf( "Aufgabe 3:\n");
    aufgabe3();

    printf( "Aufgabe 4:\n");
    aufgabe4();

    printf( "Aufgabe 5:\n");
    aufgabe5();

    return 0;
}

/*
 * Aufgabe 5:
 * Fragt ab, wie viele Namen eingegeben werden sollen. Liest diese ein und
 * gibt sie anschließend wieder aus.
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 15.02.2010 - 10:05 Uhr
 */
void aufgabe5() {

    printf( "Gib Anzahl an wie viele Namen du eingeben moechtest: " );
    int i, anzahl = 0;
    
    scanf( "%i", &anzahl );
    getchar();
    printf( "\n" );

    char namen[anzahl][22];
    //Namen einlesen
    for( i = 0; i < anzahl; ++i ) {
	    printf( "Name Nr. %i: ", i+1 );
	    fgets( namen[i], 22, stdin );
    }
    printf( "\n" );
    //Ausgabe
    for( i = 0; i < anzahl; ++i ) {
	    printf( "Name Nr. %i: %s",
		    i+1,
		    namen[i] );
    }
    printf("\n");
}

/*
 * Zur Aufgabe 4:
 * Reserviert Speicher der Größe n für den übergebenen Zeiger.
 * Gibt diesen wieder frei.
 *
 * Liefert 1 zurück bei Erfolg, -1 bei Fehlschlag.
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 01.02.2010 - 21:00 Uhr
 */
int speicherreservierung( long int n, int *zeiger ) {
    //Speicher reservieren ...
    zeiger = malloc( n );
    if( zeiger == NULL ) {
	return -1;
    }
    //Speicher freigeben ...
    free( zeiger );

    return 1;
}

/*
 * Aufgabe 4:
 * Ruft "speicherreservierung" auf und gibt je nach Ausgang der Fkt. eine Text
 * aus.
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 15.02.2010 - 10:05 Uhr
 */
void aufgabe4() {

    int *speicher = NULL;
    if( speicherreservierung( 1024, speicher ) == 1 ) {

	printf( "Speicherreservierung hat funktioniert!\n\n" );

    } else {

	printf( "Speicherreservierung hat nicht funktioniert!\n\n" );
    }

}

/*
 * Für Aufgabe 3:
 * Kopiert einen übergebenen String in einen Zeiger, der zurückgegeben wird.
 * Letztes Zeichen ist \0, welches auf jeden Fall hinzugefügt wird.
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 01.02.2010 - 21:00 Uhr
 */
char *stringKopierer( char *string ) {

    int i, laenge = strlen( string );

    char kopiert[laenge];
    
    for( i = 0; i < laenge - 1; ++i ) {
	kopiert[i] = string[i];
    }
    
    kopiert[laenge - 1] = '\0';

    return kopiert;
}

/*
 * Aufgabe 3:
 * Übergibt einen String an stringKopierer und gibt den zurückgegebenen Zeiger
 * aus. Liefert zusätzlich eine Ausgabe zu den Speicheradressen der beiden Inhalte.
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 15.02.2010 - 10:05 Uhr
 */
void aufgabe3() {

    printf( "Gib einen String ein der kopiert werden soll [max. 30 Zeichen]: " );

    char zuUebergeben[32];
    fgets( zuUebergeben, 32, stdin );
    
    char *uebergeben = stringKopierer( zuUebergeben );

    printf( "Kopiert: %s\n\t(von %p nach %p)\n\n",
		uebergeben,
		&zuUebergeben,
		&uebergeben );
}

/*
 * Aufgabe 2:
 * Fragt ab, wie viele Zahlen der Benutzer eingeben wird. Diese werden anschließend
 * eingelesen und darauf hin wieder ausgegeben (mit 2 multipliziert).
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 01.02.2010 - 21:00 Uhr
 */
void aufgabe2() {

    printf( "Gib Anzahl der Zahlen ein, die eingelesen werden sollen: " );
    int i, anzahl = 0;

    scanf( "%i", &anzahl );
    int zahlen[anzahl];

    //Einlesen
    printf( "\n" );
    for( i = 0; i < anzahl; ++i ) {
	    printf( "Zahl Nr. %i: ", i+1 );
	    scanf( "%i", &zahlen[i] );
    }

    //Ausgeben
    printf( "\n" );
    for( i = 0; i < anzahl; ++i ) {
	    printf("Zahl Nr. %i: %i * 2 = %i\n",
		    i + 1,
		    zahlen[i],
		    zahlen[i] * 2 );
    }

    printf( "\n" );
    getchar(); //Zeichen aus Inputstream holen (damit nächster fgets-Befehl fkt.
}


/*
 * Aufgabe 1:
 * Reserviert in 1024 Byte - Schritten Speicher, wenn nicht mehr Speicher reserviert
 * werden kann, so wird die Anzahl der Durchläufe (geteilt durch 1024) ausgegeben.
 * Dies entspricht der reservierten Größe in Megabyte.
 * Speicherfreigabe erfolgt intern.
 *
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 01.02.2010 - 21:00 Uhr
 */
void aufgabe1(){

        int *speicher = malloc( 1 );
        int reserviert = 1;
    
	while( speicher != NULL ) {
	    speicher = realloc( speicher, ( ++reserviert * 1024 ) );
        }

        free( speicher );
    printf( "Maximal reservierbarer Speicher: %i MB \n\n", reserviert / 1024 );
}
