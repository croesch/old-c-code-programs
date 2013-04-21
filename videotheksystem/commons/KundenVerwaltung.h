/* Datei: KundenVerwaltung.h */
/* Definitionen zum Suchen eines Kunden-Datensatzes in der Kundenverwaltung */

#ifndef uint8
#define uint8 unsigned char
#endif

#ifndef uint32
#define uint32 unsigned long int
#endif

/* Strukturierter Datentyp "tKundenDatensatz" für einen Kunden-Datensatz */
typedef struct _KundenDatensatz {
	uint32 KundenNummer; /* 32-Bit Unsigned Integer */
	char KundenName[81]; /* max. 80 Zeichen für "Name, Vorname" + '\0' */
	char Geburtstag[11]; /* "JJJJ/MM/TT" + '\0' */
	char Adresse[95]; /* max. 94 Zeichen für "Straße Hausnummer, PLZ Ort" + '\0' */
	uint8 Stammkunde; /* 8-Bit Unsigned Integer: 0 für kein Stammkunde, 1 für Stammkunde */
} tKundenDatensatz;

/* Funktion KundeSuchen */
/* Parameter KundenDatensatz als Ein-/Ausgabe vom Typ tKundenDatensatz */
/*   Die KundenNummmer 0 steht für eine beliebige Kundennummer. */
/*   KundenName, Geburtstag, Adresse werden in den Kundendaten als Teilstring gesucht. */
/*   Stammkunde wird als Eingabe zum Suchen ignoriert. */
/* Wenn die Eingabedaten auf genau einen Kunden passen wird der KundenDatensatz vervollständigt und der Wert 0 zurückgegeben. */
/* Wenn die Eingabedaten auf keinen Kunden passen wird der Wert 1 zurückgegeben. */
/* Wenn die Eingabedaten auf mehrere Kunden passen wird der Wert 2 zurückgegeben. */uint8 KundeSuchen(
		tKundenDatensatz *KundenDatensatz);
