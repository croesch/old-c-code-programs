#include <stdio.h>
#include <math.h>

/*
Gibt alle Ergebnisse der Übungen vom 07.12.2009 aus. Mit dazugehörigem Quellcode.
Dazu # der Aufgabe im lfd. Programm eingeben

Author: Christian Rösch
Revision 1.0 (Date: 2009-12-08 10:33h)
*/
int main ()
{
    int Aufgabe = 0;

    printf("Dieses Programm zeigt die Ergebnisse der Uebungsaufgaben vom 07.12.2009 an.\n\
Hierzu geben Sie bitte die Nummer der Aufgabe ein, die Sie ansehen wollen:\n\
Nummer der Aufgabe: ");
	while(1){

	int check = scanf("%i",&Aufgabe);
	if(check == 0 || Aufgabe >8 || Aufgabe<=0){
			printf("\nUngueltige Eingabe!\nNummer der Aufgabe: ");
			fflush(stdin);
			continue;
		}
		printf("\n");
		if(Aufgabe == 1){
			printf("Aufgabe 1:\n");
			printf("Gib folgenden String aus: \"Heute ist der 04.05.2009.\" Wobei jede Zahl des Datums sowie das Wort");
			printf(" \"Heute\" aus einer Variable ausgelesen werden soll.\n\n");

			printf("a) Was passiert, wenn das Hochkomma am Ende fehlt?\n");
			printf("b) Was passiert, wenn du dich bei print verschreibst?\n");
			printf("c) Was passiert, wenn du Klammern um den String machst?\n\n");

			printf("\tLoesung:\n");
			char *relTag = "Heute", *tag = "04", *monat = "05", *jahr = "2009";
			printf("\t\"%s ist der %s.%s.%s.\"\n\n",relTag,tag,monat,jahr);
			char *del = "%s";
			printf("\tCode:\n");
			printf("\tchar *relTag = \"Heute\", *tag = \"04\", *monat = \"05\", *jahr = \"2009\";\n");
			printf("\tprintf(\"\\\"%s ist der %s.%s.%s.\\\"\\n\",relTag,tag,monat,jahr);\n\n",del,del,del,del);

			printf("\ta) CompilerError: missing terminating \" character\n");
			printf("\tb) CompilerError: undefined reference to '_preintf'\n");
			printf("\tc) Ausserhalb der Hochkommata: Nichts aendert sich,\n\tinnerhalb: Sie werden mit ausgegeben\n\n");
		}
		else if(Aufgabe == 2){
			printf("Aufgabe 2:\n");
			printf("Du laeufst 2km in 6Minuten. Wie ist deine Durchschnittsgeschwindigkeit in km/h?\n");
			printf("Und in m/s? Wieviele km laeufst du in 45 Minuten? Was ist deine Durchschnittszeit pro km?\n\n");

			float km = 2,min = 6;
			float durchschnitt = km / (min/60);
			float mpros = durchschnitt/3.6;
			float wie45 = durchschnitt*(3.0/4.0);
			float zeit = min / km;
			printf("\tAntwort:\n");
			printf("\tDurchschnittsgeschwindigkeit in km/h:\t%f\n",durchschnitt);
			printf("\tIn m/s:\t\t\t\t\t%f\n",mpros);
			printf("\tIn 45 Minuten: \t\t\t\t%f km\n",wie45);
			printf("\tZeit pro km: \t\t\t\t%f Minuten\n\n",zeit);

			printf("\tCode:\n");
			printf("\tfloat km = 2,min = 6;\n");
			printf("\tfloat durchschnitt = km / (min/60);\n");
			printf("\tfloat mpros = durchschnitt/3.6;\n");
			printf("\tfloat wie45 = durchschnitt*(3.0/4.0);\n");
			printf("\tfloat zeit = min / km;\n");
			char *del = "%f";
			printf("\tprintf(\"Durchschnittsgeschwindigkeit in km/h:\\t%s\\n\",durchschnitt);\n",del);
			printf("\tprintf(\"In m/s:\\t\\t\\t\\t\\t%s\\n\",mpros);\n",del);
			printf("\tprintf(\"In 45 Minuten: \\t\\t\\t\\t%s km\\n\",wie45);\n",del);
			printf("\tprintf(\"Zeit pro km: \\t\\t\\t\\t%s Minuten\\n\\n\",zeit);\n\n",del);
		}
		else if(Aufgabe == 3){
			printf("Aufgabe 3:\n");
			printf("Folgende Variablen werden deklariert:\n");
			printf("1. int width = 17;\n");
			printf("2. float height = 12.0f;\n");
			printf("3. char delimiter = '.';\n\n");
			printf("Schreibe den Typ und den Wert der folgenden Ausdruecke auf und ueberpruefe deine Annahmen danach:\n\n");
			printf("1. width/2\t\t[Annahme: 8 (weil int)]\n");
			printf("2. width/2.0\t\t[Annahme: 8.5 (weil durch float geteilt wird)]\n");
			printf("3. height/3\t\t[Annahme: 4 (weil durch int geteilt wird)]\n");
			printf("4. 1 + 2 * 5\t\t[Annahme: 11]\n");
			printf("5. delimiter * 5\t[Annahme: int-Wert von '.' * 5]\n\n");

			int width = 17;
			float height = 12.0f;
			char delimiter = '.';

			printf("\tAntwort:\n");
			printf("\theight = %f; width = %i\n",height,width);
			printf("\twidth / 2 = %i\n",width/2);
			printf("\twidth / 2.0 = %f\n",width/2.0);
			printf("\theight / 3 = %f\n",height/3);
			printf("\t1+2*5 = %i\n",1+2*5);
			printf("\tdelimiter * 5 = %i\n\n",delimiter*5);

		}
		else if(Aufgabe == 4){
			printf("Aufgabe 4:\n");
			printf("Wieviel Volumen hat eine Kugel mit dem Radius 3? Radius 5? Radius 13.6?\n\n");

			float radius[] = {3,5,13.6};
			int i = 0;
			printf("\tAntwort:\n");
			for(i = 0; i < sizeof(radius)/sizeof(float);i++){
				printf("\tRadius: %f\n",radius[i]);
				float volumen = pow(radius[i],3.0)*(4.0/3.0)*3.14159265358979323846f;
				printf("\tVolumen: %f\n\n",volumen);
			}

			printf("\tCode:\n");
			printf("\tfloat radius[] = {3,5,13.6};\n");
			printf("\tint i = 0;\n");
			printf("\tfor(i = 0; i < sizeof(radius)/sizeof(float);i++){\n");
			char *del = "%f";
			printf("\t\tprintf(\"Radius: %s\\n\",radius[i]);\n",del);
			printf("\t\tfloat volumen = pow(radius[i],3.0)*(4.0/3.0)*3.14159265358979323846f;\n");
			printf("\t\tprintf(\"Volumen: %s\\n\\n\",volumen);\n",del);
			printf("\t}\n\n");

		}
		else if(Aufgabe == 5){
			printf("Aufgabe 5:\n");
			printf("Ein Buch kostet 24,95EUR pro Stueck. Buecherlaeden erhalten 30% Rabatt. Versand fuer das erste Buch \
kostet 6,90EUR, fuer jedes weitere 4EUR. Wieviel kosten 60 Buecher.\n\n");

			float buchpreis = 24.95, anzahl = 60, rabatt = 30, versandeins = 6.90, versandandere = 4.0;
			float preis = buchpreis*rabatt/100*anzahl+versandeins+(anzahl-1)*versandandere;
			printf("\tAntwort:\n");
			printf("\t%f Buecher kosten %f Euro.\n\n",anzahl,preis);

			char *del = "%f";
			printf("\tCode:\n");
			printf("\tfloat buchpreis = 24.95, anzahl = 60, rabatt = 30, versandeins = 6.90, versandandere = 4.0;\n");
			printf("\tfloat preis = buchpreis*rabatt/100*anzahl+versandeins+(anzahl-1)*versandandere;\n");
			printf("\tprintf(\"%s Buecher kosten %s Euro.\\n\\n\",anzahl,preis);\n\n",del,del);
		}
		else if(Aufgabe == 6){
			printf("Aufgabe 6:\n");
			printf("Du verlaesst dein Haus um 6:52 und laeufst einen Kilometer gemuetlich in 5 Minuten \
dann drei Kilometer in je 4 Minuten und zum Abschluss einen Kilometer in 6:00 Minuten. Wann bist du zurueck zum Fruehstueck?\n\n");

			printf("Antwort:\n");
			printf("Ich bin um (6:52 + 5min + 3*(4min) + 6min) 7:15 Uhr zum Fruehstueck zurueck!!!\n\n");
		}
		else if(Aufgabe == 7){
			printf("Aufgabe 7:\n");
			printf("Stelle ein Grid wie folgendes dar:\n");
			printf("+----+----+\n|    |    |\n|    |    |\n|    |    |\n|    |    |\n+----+----+\n");
			printf("|    |    |\n|    |    |\n|    |    |\n|    |    |\n+----+----+\n");
		}
		else if(Aufgabe == 8){
			printf("Aufgabe 8:\n");
			printf("Stelle ein Grid mit vier Zeilen und vier Spalten dar:\n");
			int i,j,k,spalten=4,zeilen=4;
			for(i = 0; i<zeilen;i++){
				for(j = 0;j<spalten;j++){
					printf("+----");
				}
				printf("+\n");
				for(j = 0;j<4;j++){
					for(k = 0;k<spalten;k++){
						printf("|    ");
					}
					printf("|\n");
				}

			}
			for(j = 0;j<spalten;j++){
				printf("+----");
			}
			printf("+\n");
		}

	printf("Gib 0 ein zum Beenden - Gib 1 ein um weitere Aufgaben anzusehen.\n");
	int weiter = 1;
	scanf("%d",&weiter);
	if(weiter==0)
		break;
		printf("Nummer der Aufgabe: ");
	}
    printf("\n");
    return 0;
}

