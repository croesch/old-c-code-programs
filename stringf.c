/*
 * Gibt die Anzahl Zeichen eines Strings bis zum ersten \0 zurück
 *
 * string: String, von dem die Länge bestimmt werden soll.
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 09.02.2010 - 20:20 Uhr
 */
int stringLaenge( char string[] ){
    int i = 0;

    while( string[i] != '\0' ) {
	++i;
    }
    
    return i;
}


/*
 * Zählt Anzahl der Buchstaben a-z + A-Z in einem String. Sucht bis zum \0
 * 
 * Gibt die Anzahl gefundener Buchstaben zurück.
 * 
 * string: String in dem die Buchstaben gesucht werden.
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 09.02.2010 - 20:20 Uhr
 */
int anzahlBuchstaben( char string[] ) {
    int i = 0, anzahl = 0;

    while( string[i] != '\0' ) {
	
	if( ( string[i] >= 'a' && string[i] <= 'z' ) ||
		( string[i] >= 'A' && string[i] <= 'Z' ) ) {
	    ++anzahl;
	}
	++i;

    }
    return anzahl;
}

/*
 * Prüft zwei Strings auf Identität.
 * Gibt 1 zurück, wenn beide Strings gleicher Länge und alle Zeichen gleich sind
 * Gibt 0 zurück, wenn die Strings nicht identisch sind
 *
 * string1,string2 zu prüfende Strings
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 09.02.2010 - 20:20 Uhr
 */
int vergleicheStrings( char string1[], char string2[] ) {
    int i = 0;

    int laenge1 = stringLaenge( string1 );

    if( laenge1 != stringLaenge( string2 ) ) {
	return 0;
    }

    for( i = 0; i < laenge1; ++i ) {

	if( string1[i] != string2[i] ) {
	    return 0;
	}
    }

    return 1;
}

/*
 * Prüft ob ein String in einem anderen enthalten ist.
 *
 * Gibt 1 zurück, wenn String gefunden
 * Gibt 0 zurück, wenn String nicht gefunden
 *
 * string: String, in dem ein anderer gesucht wird
 * stringInhalt: zu suchender String
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 09.02.2010 - 21:50 Uhr
 */
int enthaeltString( char string[], char stringInhalt[] ) {

    int laengeBehaelter = stringLaenge( string );

    int laengeInhalt = stringLaenge( stringInhalt );
    if( laengeInhalt > laengeBehaelter ) {
	return 0;
    }

    int i = 0, j = 0; //j - Anzahl übereinstimmender Zeichen am Stück
    int k = 0; //Speicher für Position von i im Falle vermeintlicher Treffer
    for( i = 0; i < laengeBehaelter; ++i) {

	if( string[i] == stringInhalt[j] ) {
	    if( k == 0 ) {
		//Speichere beim ersten Zeichen was übereinstimmt die Position
		//von i um bei einem späteren Fehlschlag von einer Position weiter
		//erneut zu suchen (fand sonst "test" in "tetest" nicht.
		k = 1+i;
	    }
	    ++j;

	    if( j == laengeInhalt ) {//Alle Zeichen wurden im Container gefunden
	    	return 1;
	    }
	    continue;
	}
	//Zeichen stimmen nicht überein, suche wieder nach dem ersten Zeichen
	//ab dem der vermeintliche Treffer anfing
	
	//setzt i auf k zurück, falls j noch einen Wert hatte, das heißt gerade
	//das erste Zeichen ist, was nicht übereinstimmt.
	if( j != 0 ) {
	    i = k;
	    k = 0;
	}
	j = 0;
    }

    return 0;
}

/*
 * Entfernt aus einem String alle '\n'.
 *
 * string: String aus dem die Zeichen entfernt werden sollen
 * * * * * * * * * * * * * * * * * * * * *
 *	Autor: Christian Rösch		 *
 * * * * * * * * * * * * * * * * * * * * *
 * Zuletzt geändert am: 09.02.2010 - 20:20 Uhr
 */
void entferneUmbruch( char string[] ) {

    int laenge = stringLaenge( string );
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
