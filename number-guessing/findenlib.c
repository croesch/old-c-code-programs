#include <stdio.h>

/*
 * Autor: Christian Rösch
 *
 * Zuletzt geändert am 11.01.2010, 08:09
 * 
 * Funktion um die Zahl rekursiv zu finden, wobei die übergebenen Argumente
 * die beiden Grenzen des Zahlenbereichs bilden.
 */
void findeZahl( int untereGrenze, int obereGrenze ) {
    /*
     * vorschlag: Die Zahl, die das Programm als gesuchte Zahl vorschlägt
     * rueckmeldung: Antwort welche der Benutzer über den Vorschlag abgibt (größer,
     * kleiner, gefunden) - standardmäßig = 0
     */
    int vorschlag = ( untereGrenze + obereGrenze ) / 2;
    int rueckmeldung = 0;

    printf( "Ist %i deine gedachte Zahl?\n", vorschlag );
    printf( "(Bitte gib eine Ziffer fuer folgende Optionen an)\n" );
    printf( "\t(1) Ja, das ist meine Zahl!\n" );

    //Zeige Option (2) nur, wenn vorgeschlagene Zahl größer als die Untergrenze ist.
    if( vorschlag > untereGrenze ) {
	printf( "\t(2) Meine Zahl ist kleiner\n" );
    }

    //Zeige Option (3) nur, wenn vorgeschlagene Zahl kleiner als die Obergrenze ist.
    if( vorschlag < obereGrenze ) {
        printf( "\t(3) Meine Zahl ist groesser\n" );
    }
    scanf( "%i", &rueckmeldung );

    switch( rueckmeldung ){
	case 1:

	    //gedachte Zahl = vorgeschlagene Zahl
            printf( "Zahl gefunden (%i) -> Programmende\n\n", vorschlag );
            break;

        case 2:

	    //gedachte Zahl < vorgeschlagene Zahl
            if( vorschlag > untereGrenze ) {
                findeZahl( untereGrenze, --vorschlag );
            }
            else {
		printf( "Logisch nicht moeglich!\n" );
		findeZahl( untereGrenze, obereGrenze );
	    }
	    break;

        case 3:

	    //gedachte Zahl > vorgeschlagene Zahl
            if( vorschlag < obereGrenze ) {
                findeZahl( ++vorschlag, obereGrenze );
            }
            else {
                printf( "Logisch nicht moeglich!\n" );
                findeZahl( untereGrenze, obereGrenze );
            }
            break;

        default:

	    printf( "Ungueltige Eingabe!\n" );
            findeZahl( untereGrenze, obereGrenze );
            break;
	    
    }
}
