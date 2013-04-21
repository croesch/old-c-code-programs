/*
 * Datei: main.c
 * Autor: Christian Rösch
 *
 * Zuletzt geändert am 11.01.2010, 08:09
 */

#include <stdio.h>
#include <stdlib.h>
#include "finden.h"

int untergrenze = 0, obergrenze = 10;

void setzeUnterGrenze( int eingabe );
void setzeOberGrenze( int eingabe );

/*
 * Autor: Christian Rösch
 *
 * Zuletzt geändert am 11.01.2010, 08:09
 *
 * Programm um in einem eingebbaren (positiven) Zahlenbereich eine gedachte
 * (natürliche) Zahl zu finden.
 * Die beiden Grenzen des Zahlenbereichs sind eingeschlossen bei der Suche der Zahl.
 * Die Summe beider Grenzen wird halbiert, was der Vorschlag des Programms für die
 * gedachte Zahl ist. Die benachbarte (ob gesuchte Zahl größer oder kleiner ist) Zahl
 * der vorgeschlagenen Zahl bildet die neue Ober-/Untergrenze des Zahlenbereichs.
 */
int main() {

    int untergrenze_eingabe, obergrenze_eingabe;
    printf( "ZAHLENRATEN V. 1.1:\n\n" );

    printf( "Gib die Untergrenze des Zahlenbereichs ein\nUntergrenze: " );
    scanf( "%i", &untergrenze_eingabe );
    setzeUnterGrenze( untergrenze_eingabe );

    printf( "\nGib die Obergrenze des Zahlenbereichs ein\nObergrenze: " );
    scanf( "%i", &obergrenze_eingabe );
    setzeOberGrenze( obergrenze_eingabe );

    printf( "\n\nDenke dir eine ganze Zahl zwischen %i und %i aus und merke sie dir!\n\n", untergrenze, obergrenze );
    findeZahl( untergrenze, obergrenze );

    return ( EXIT_SUCCESS );
}

/*
 * Autor: Christian Rösch
 *
 * Zuletzt geändert am 11.01.2010, 08:09
 *
 * Setzt die Untergrenze für den Zahlenbereich in dem die zu suchende Zahl liegt.
 */
void setzeUnterGrenze( int eingabe ) {

    if( eingabe >= untergrenze ) {

	untergrenze = eingabe;

    }
    //Benutze Wert von "untergrenze" falls "eingabe" kleiner als dieser ist.
}

/*
 * Autor: Christian Rösch
 *
 * Zuletzt geändert am 11.01.2010, 08:09
 *
 * Setzt die Obergrenze für den Zahlenbereich in dem die zu suchende Zahl liegt.
 */
void setzeOberGrenze( int eingabe ) {

    if( eingabe > untergrenze ) {

	obergrenze = eingabe;

    } else if( eingabe < untergrenze ) {
	/*
	 * Die kleinere Grenze wird zur Untergrenze und die bisherige größere
	 * Untergrenze wird zur Obergrenze
	 */
	obergrenze = untergrenze;

	if( eingabe < 0 ) {

	    untergrenze = 0;

	} else {

	    untergrenze = eingabe;

	}
    } else {
	/*
	 * Sind die eingegebenen Grenzen des Zahlenbereichs gleich, so wird
	 * die Obergrenze 10 größer als die Untergrenze gewählt.
	 */
	printf( "Zahlenbereich zu klein. Automatisch vergroessert!" );
	obergrenze += untergrenze;

    }
}
