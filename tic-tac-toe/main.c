/* 
 * Datei:   main.c
 * AUTOR: Christian Rösch
 *
 * Zwei Spieler, die anfangs ihre Namen eintragen spielen gegeneinander.
 * Der erste Spieler hat X und Spieler 2 bekommt O.
 * Zum Spielen werden die Feldnummern 1-9 eingegeben.
 *
 * Nach dem Spiel wird gefragt ob erneut gespielt werden soll.
 *
 * Zuletzt geändert am 18. Januar 2010, 19:42
 */

#include <stdio.h>
#include <stdlib.h>

void anzeigeErstellen( int beispielAnzeigen );
void eingabeLesen( int spielZug );
void spielfeldAusgeben( int breite, int hoehe, int zellenHoehe, int hilfe );
void zellWertSchreiben( int zellenNummer, int hilfe );
int siegerPruefen( int zellenNr );
void zeigeEndbild( int spieler );
void leereBildschirm();

int zellWerte[9] = { 0 };
char spieler1[50] = "Spieler 1", spieler2[50] = "Spieler 2";


/*
 * Startet das Spiel. Namenseingabe nur vor erstem Spiel.
 * Nach Ende wir per scanf gefragt, ob nochmal gespielt werden soll. Falls nicht
 * wird das Programm beendet.
 *
 * AUTOR: Christian Rösch
 * Zuletzt geändert am 18. Januar 2010, 19:42
 */
int main() {

    int weiterSpielen = 0;
    leereBildschirm();

    printf( "NAMEN eingeben:\nSpieler 1, gib deinen Namen ein: " );
    scanf( "%s", &spieler1 );

    printf( "\nSpieler 2, gib deinen Namen ein: " );
    scanf( "%s", &spieler2 );
    
    do {
	int i;
	for( i = 0; i < 9; ++i ) {
	    zellWerte[i] = 0;
	}
	//Eigentlicher Start des Spielablaufs
        eingabeLesen( 0 );

	printf( "\n\nErneut spielen? Gib 0 fuer NEIN oder 1 fuer JA ein!\nAntwort: " );
	scanf( "%i", &weiterSpielen );

    } while ( weiterSpielen );


    return ( EXIT_SUCCESS );
}

/*
 * Gibt aus, wer gewonnen hat und ruft das Spielbrett auf.
 * spieler: 1,2 - Spielernummer / -1 - unentschieden
 *
 * AUTOR: Christian Rösch
 * Zuletzt geändert am 18. Januar 2010, 19:42
 */
void zeigeEndbild( int spieler ) {

    anzeigeErstellen( 0 );

    if( spieler > 0 ) {

	if( spieler == 1 ) {
	    printf( "%s", spieler1 );
	} else {
	    printf( "%s", spieler2 );
	}

	printf( " hat das Spiel gewonnen!\n" );

    } else {

	printf( "Das Spiel ist unentschieden!\n" );

    }

}

/*
 * Prüft ob zum jetzigen Zeitpunkt jemand gewonnen hat.
 * zellenNr: Nr. der Zelle, welche gerade gesetzt wurde
 *
 * return 0: Spiel zu Ende, ein Gewinner steht fest
 * return 1: Der aktuelle Spielzug hat keinen Gewinner hervorgebracht
 *
 * AUTOR: Christian Rösch
 * Zuletzt geändert am 18. Januar 2010, 19:42
 */
int siegerPruefen( int zellenNr ) {

    int spalte = zellenNr % 3;

    //Prüft ob die Zellen der Spalte der Zelle, welche gerade gesetzt wurde
    // gleich sind. Auf null muss nicht geprüft werden, da ja eine Zelle gesetzt wurde
    if( ( zellWerte[spalte] == zellWerte[spalte + 3] )
	    && ( zellWerte[spalte + 3] == zellWerte[spalte + 6] ) ) {
	//Spalte gewonnen :)
	return 0;
    }

    //Prüft ob die Zellen der Zeile der Zelle, welche gerade gesetzt wurde
    // gleich sind. Auf null muss nicht geprüft werden, da ja eine Zelle gesetzt wurde
    if( ( zellWerte[zellenNr - spalte] == zellWerte[zellenNr - spalte + 1] )
	    && ( zellWerte[zellenNr - spalte + 1] == zellWerte[zellenNr - spalte + 2] ) ) {
	//Zeile gewonnen :)
	return 0;
    }

    //Prüft, wenn die gesetzte Zelle in der Diagonalen von l.o. nach r.u. ist,
    //ob die Zellen gleich sind. null wird auch hier nicht geprüft.
    if( ( zellenNr % 4 == 0 )
	    && ( zellWerte[0] == zellWerte[4] )
	    && ( zellWerte[4] == zellWerte[8] ) ) {
	//links oben nach rechts unten gewonnen :)
	return 0;
    }

    //Prüft, wenn die gesetzte Zelle in der Diagonalen von r.o. nach l.u. ist,
    //ob die Zellen gleich sind. null wird auch hier nicht geprüft.
    if( ( zellenNr == 2 || zellenNr == 4 || zellenNr == 6 )
	    && ( zellWerte[2] == zellWerte[4] )
	    && ( zellWerte[4] == zellWerte[6] ) ) {
	//links unten nach rechts oben gewonen :)
	return 0;
    }

    //Kein Sieger steht fest
    return 1;
}

/*
 * Liest die Benutzereingaben ein und ruft resultierende Funktionen auf.
 * spielZug: Anzahl der Spielzüge im Spiel, wenn 9 dann Spiel zu Ende
 *		=> wird benutzt um Spieler zu bestimmen, der an d. Reihe ist
 *
 * AUTOR: Christian Rösch
 * Zuletzt geändert am 18. Januar 2010, 19:42
 */
void eingabeLesen( int spielZug ) {

    anzeigeErstellen( 1 );

    if( spielZug >= 9 ) {
	zeigeEndbild( -1 ); //Spiel zu Ende - unentschieden
    } else {

	int spielerNr = ( spielZug % 2 ) + 1;
	int zellenNr = 10;

	if( spielerNr == 1 ) {
	    printf( "%s", spieler1 );
	    printf( " ist am Zug!\nGib die Nr. der Zelle, in die du dein " );
	    printf( "Kreuz setzen möchtest!\nZellennummer: " );

	} else {
	    printf( "%s", spieler2 );
	    printf( " ist am Zug!\nGib die Nr. der Zelle, in die du dein " );
	    printf( "Kreis setzen möchtest!\nZellennummer:" );
	}

	scanf( "%i", &zellenNr );
	--zellenNr; //Eingaben 1-9 - Array 0-8

	if( ( zellenNr >= 0 ) && ( zellenNr < 9 )
		&& ( zellWerte[zellenNr] == 0 ) ) {

	    zellWerte[zellenNr] = spielerNr;

	    if( siegerPruefen( zellenNr ) ) {
		eingabeLesen( ++spielZug );
	    } else {
		zeigeEndbild( spielerNr );
	    }

	} else {
	    eingabeLesen( spielZug ); //erneute Eingabe anfordern
	}
    }
}

/*
 * Schreibt auf Grundlage des Arrays zellWerte folgende Werte: X,O," "
 * Ist hilfe 1, dann werden 1-9 statt die Werte des Arrays ausgegeben
 *
 * zellenNummer: Nummer des Array-Elements in dem der Wert steht
 * hilfe: 1, wenn Ziffern 1-9 statt Zeichen ausgegeben werden sollen
 *
 * AUTOR: Christian Rösch
 * Zuletzt geändert am 18. Januar 2010, 19:42
 */
void zellWertSchreiben( int zellenNummer, int hilfe ) {

    if( hilfe ) {
	printf( "%i", zellenNummer + 1 );
    } else {

	switch( zellWerte[zellenNummer] ) {
	    case 1:
		printf( "X" );
		break;
	    case 2:
		printf( "O" );
		break;
	    default:
		printf( " " );
		break;
	}
    }
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
void spielfeldAusgeben( int breite, int hoehe, int zellenHoehe,  int hilfe ) {

    int i, j, k, l, m = 0; //Laufvariablen für verschachtelte Schleifen

    if( hilfe ) {
	printf( "Die Zellennummerierung sieht wie folgendes Beispiel aus.\n" );
    } else {
	printf( "Der Spielstand:\n" );
    }

    //Zeilen
    for( i = 1; i <= hoehe; i++ ) {
	//ZeilenZeilen (Zeilenhöhe)
	for( j = 1; j <= zellenHoehe; j++ ) {
	    //Spalten
	    for( k = 1; k <= breite; k++ ) {
		//SpaltenSpalten (Spaltenbreite)
		for( l = 1; l <= zellenHoehe * 2 - 1; ++l ) {

		    //Inhalt (ein Zeichen erwartet)
		    if( ( j == zellenHoehe / 2 + 1 ) && ( l == zellenHoehe ) ) {
			zellWertSchreiben( m++, hilfe );
		    } else {
			printf( " " );
		    }

		}
		if( k != breite ){

		    printf( "|" );
		}
	    }
	    printf( "\n" );
	}

	if( i == hoehe ) {
	    break;
	}
	//Trenn"linie" horizontal
	for( j = 1; j <= breite; j++ ) {
	    for( k = 1; k <= zellenHoehe * 2 - 1; ++k ) {
		printf( "-" );
	    }
	    if( j != breite ) {
		printf( "+" );
	    }
	}
	printf( "\n" );
    }
    printf( "\n" );
}

/*
 * Gibt i.d.R. zwei Spielfelder aus, es sei denn:
 * beispielAnzeigen: 0 Kein Beispielfeld mit den Ziffern 1-9 wird angezeigt
 * beispielAnzeigen: 1 Beispielfeld wird angezeigt, über Spielfeld
 *
 * AUTOR: Christian Rösch
 * Zuletzt geändert am 18. Januar 2010, 19:42
 */
void anzeigeErstellen( int beispielAnzeigen ) {

    leereBildschirm();

    if( beispielAnzeigen ) {
        spielfeldAusgeben( 3, 3, 1, 1 );
    }
    spielfeldAusgeben( 3, 3, 3, 0 );

}

/*
 * Leert den Bildschirm und schreibt den Programmtitel in die erste Zeile!
 *
 * AUTOR: Christian Rösch
 * Zuletzt geändert am 18. Januar 2010, 19:42
 */
void leereBildschirm() {

    system( "clear" );
    printf( "TicTacToe V. 1.0:\n" );
    
}