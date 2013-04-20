#include <stdio.h>
#include <stdlib.h>
#include <string.h>

main()
{

FILE* fpdatei;
FILE* fpdateineu;
char suchen[500];
char gesucht[255];
char* gefunden;
char dateiname[255];
int i = 0;

fpdatei = fopen("datei.txt", "r");
if (fpdatei ==NULL)
{
return 1;
}
//fpdateineu = fopen("edit2.txt", "w");
while (!feof(fpdatei))
{
    fgets(suchen, 500, fpdatei);

    gefunden = (char*)strstr(suchen, gesucht);
    if (gefunden == NULL)
    {
        //fputs(suchen, fpdateineu);
        printf("Zeile: %s",suchen);
    }
    else
    {
        printf("Gefunden\n");
    }
}
fclose(fpdatei);
//fclose(fpdateineu);

printf("\n\n");
return 0;
}