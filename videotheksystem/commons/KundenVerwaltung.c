/* Datei: KundenVerwaltung.c */
/* Prototyp zum Suchen eines Kunden-Datensatzes in der Kundenverwaltung */

#include "KundenVerwaltung.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Globale Variable to switch on debugging messages
 * 0 = off
 * 1 = only entry-data and found-data
 * 2 = additional data for each record read
 */
const int d_e_b_u_g = 0;

/* lokale Hilfsfunktion für Prototyp zum Prüfen, ob s2 in s1 enthalten ist */
int s2_is_in_s1(char *s1, char *s2);

/* Funktion KundeSuchen */
/* Parameter KundenDatensatz als Ein-/Ausgabe vom Typ tKundenDatensatz */
/*   Die KundenNummmer 0 steht für eine beliebige Kundennummer. */
/*   KundenName, Geburtstag, Adresse werden in den Kundendaten als Teilstring gesucht. */
/*   Stammkunde wird als Eingabe zum Suchen ignoriert. */
/* Wenn die Eingabedaten auf genau einen Kunden passen wird der KundenDatensatz vervollständigt und der Wert 0 zurückgegeben. */
/* Wenn die Eingabedaten auf keinen Kunden passen wird der Wert 1 zurückgegeben. */
/* Wenn die Eingabedaten auf mehrere Kunden passen wird der Wert 2 zurückgegeben. */uint8 KundeSuchen(
		tKundenDatensatz *KundenDatensatz) {
	/* ****************************************************** */
	/* Prototyp-Implementierung als Rapid-Prodotyp            */
	/* ****************************************************** */
	/* Kunden-DB ist eine Textdatei mit folgender Syntax:     */
	/* Kundennummer#KundenName#Geburtstag#Adresse#Stammkunde# */
	/* ****************************************************** */
	const char * FileName = "data/KundenVerwaltung.txt";
	uint8 rc;
	FILE * KV;
	char K[204];
	char * KNr;
	uint32 kNr;
	char * KN;
	char * KG;
	char * KA;
	char * KS;
	uint8 kS;
	int end;
	tKundenDatensatz KD;
	KV = fopen(FileName, "r");
	if (KV == NULL) {
		printf("\n\nKundenVerwaltung - Fehler: Datei '%s' kann nicht gelesen werden!\n\n", FileName);
		return (1);
	}
	rc = 1;
	end = 0;
	if (d_e_b_u_g) {
		printf("KundenVerwaltung - Info:  KundenDatensatz->KundenNummer = '%lu'\n", KundenDatensatz->KundenNummer);
		printf("KundenVerwaltung - Info:  KundenDatensatz->KundenName = '%s'\n", KundenDatensatz->KundenName);
		printf("KundenVerwaltung - Info:  KundenDatensatz->Geburtstag = '%s'\n", KundenDatensatz->Geburtstag);
		printf("KundenVerwaltung - Info:  KundenDatensatz->Adresse = '%s'\n", KundenDatensatz->Adresse);
		printf("KundenVerwaltung - Info:  KundenDatensatz->Stammkunde = '%d'\n", (int) KundenDatensatz->Stammkunde);
	}
	while (!feof(KV) && (!end)) {
		if (fgets(K, 203, KV) != NULL) {
			strtok(K, "\n");
			if (d_e_b_u_g > 1)
				printf("KundenVerwaltung - Info:  Read Line: '%s'\n", K);
			KNr = strtok(K, "#");
			if (KNr != NULL)
				kNr = (uint32) strtoul(KNr, NULL, 10);
			else
				kNr = 0;
			KN = strtok(NULL, "#");
			if (KN == NULL)
				KN = "";
			KG = strtok(NULL, "#");
			if (KG == NULL)
				KG = "";
			KA = strtok(NULL, "#");
			if (KA == NULL)
				KA = "";
			KS = strtok(NULL, "#");
			if (KS != NULL)
				kS = (uint8) atoi(KS);
			else
				kS = 0;
			if (d_e_b_u_g > 1) {
				printf("KundenVerwaltung - Info:  Read KundenNummer = '%lu'\n", kNr);
				printf("KundenVerwaltung - Info:  Read KundenName = '%s'\n", KN);
				printf("KundenVerwaltung - Info:  Read Geburtstag = '%s'\n", KG);
				printf("KundenVerwaltung - Info:  Read Adresse = '%s'\n", KA);
				printf("KundenVerwaltung - Info:  Read Stammkunde = '%d'\n", (int) kS);
			}
			if (((KundenDatensatz->KundenNummer == 0) || (KundenDatensatz->KundenNummer == kNr))
					&& ((*(KundenDatensatz->KundenName) == '\0') || s2_is_in_s1(KN, KundenDatensatz->KundenName))
					&& ((*(KundenDatensatz->Geburtstag) == '\0') || s2_is_in_s1(KG, KundenDatensatz->Geburtstag))
					&& ((*(KundenDatensatz->Adresse) == '\0') || s2_is_in_s1(KA, KundenDatensatz->Adresse))) {
				/* Kunde gefunden */
				if (rc == 0) {
					rc = 2;
					end = 1;
					if (d_e_b_u_g) {
						printf("KundenVerwaltung - Info:  Found Second KundenNummer = '%lu'\n", kNr);
						printf("KundenVerwaltung - Info:  Found Second KundenName = '%s'\n", KN);
						printf("KundenVerwaltung - Info:  Found Second Geburtstag = '%s'\n", KG);
						printf("KundenVerwaltung - Info:  Found Second Adresse = '%s'\n", KA);
						printf("KundenVerwaltung - Info:  Found Second Stammkunde = '%d'\n", (int) kS);
					}
				}
				if (rc == 1) {
					rc = 0;
					KD.KundenNummer = kNr;
					strcpy(KD.KundenName, KN);
					strcpy(KD.Geburtstag, KG);
					strcpy(KD.Adresse, KA);
					KD.Stammkunde = kS;
					if (d_e_b_u_g) {
						printf("KundenVerwaltung - Info:  Found First KundenNummer = '%lu'\n", kNr);
						printf("KundenVerwaltung - Info:  Found First KundenName = '%s'\n", KN);
						printf("KundenVerwaltung - Info:  Found First Geburtstag = '%s'\n", KG);
						printf("KundenVerwaltung - Info:  Found First Adresse = '%s'\n", KA);
						printf("KundenVerwaltung - Info:  Found First Stammkunde = '%d'\n", (int) kS);
					}
				}
			}
		} else
			printf("\n\nKundenVerwaltung - Fehler beim Lesen in Datei '%s'!\n\n", FileName);
	}
	fclose(KV);
	if (rc == 0) {
		KundenDatensatz->KundenNummer = KD.KundenNummer;
		strcpy(KundenDatensatz->KundenName, KD.KundenName);
		strcpy(KundenDatensatz->Geburtstag, KD.Geburtstag);
		strcpy(KundenDatensatz->Adresse, KD.Adresse);
		KundenDatensatz->Stammkunde = KD.Stammkunde;
	}
	return (rc);
}

/* lokale Hilfsfunktion für Prototyp zum Prüfen, ob s2 in s1 enthalten ist */
int s2_is_in_s1(char *s1, char *s2) {
	if (!*s2) {
		return (1);
	}
	for (; *s1; ++s1) {
		if (toupper(*s1) == toupper(*s2)) {
			char *h, *n;
			for (h = s1, n = s2; *h && *n; ++h, ++n) {
				if (toupper(*h) != toupper(*n)) {
					break;
				}
			}
			if (!*n) {
				return (1);
			}
		}
	}
	return (0);
}

/* Ende Funktion KundeSuchen */
