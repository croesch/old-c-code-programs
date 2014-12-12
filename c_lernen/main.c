/* struct_arr2.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 30

static int x = 0;
static int x_gesch = 0;
static int x_eink = 0;

struct adres {
   char vname[MAX];
   char nname[MAX];
   long PLZ;
   char ort[MAX];
   int geburtsjahr;
} adressen[100];

struct gesch{
   char name[MAX];
   long ID;
} geschaefte[100];

struct eink{

} einkauefe[10000];

void Eingabe(int nr, struct adres neu[]) {
   printf("Vorname : ");
   fgets(neu[nr].vname, MAX, stdin);
   printf("Nachname : ");
   fgets(neu[nr].nname, MAX, stdin);
   printf("Postleitzahl: ");
   do {
      scanf("%5ld",&neu[nr].PLZ);
   } while(getchar()!= '\n');
   printf("Wohnort : ");
   fgets(neu[nr].ort, MAX, stdin);
   printf("Geburtsjahr : ");
   do {
      scanf("%4d",&neu[nr].geburtsjahr);
   }while(getchar()!= '\n');
}

void Suche(struct adres search[], char buchstabe, int nr) {
   int i;

   for(i = 0; i <= nr; i++) {
      if(search[i].nname[0] == buchstabe) {
         printf("\n\nGefunden unter Buchstabe "
                ":\"%c\"\n\n", buchstabe);
         printf("Vorname......:%s",search[i].vname);
         printf("Nachname.....:%s",search[i].nname);
         printf("Postleitzahl.:%ld\n",search[i].PLZ);
         printf("Ort..........:%s",search[i].ort);
         printf("Geburtsjahr..:%d\n", search[i].geburtsjahr);
         printf("\n\tWeiter mit <ENTER>\n");
         getchar();
      }
   }
}

void Ausgabe(struct adres all[],int nr) {
   int i;

   for(i = 0; i < nr; i++) {
      printf("Vorname.........:%s",all[i].vname);
      printf("Nachname........:%s",all[i].nname);
      printf("Postleitzahl....:%ld\n",all[i].PLZ);
      printf("Ort.............:%s",all[i].ort);
      printf("Geburtsjahr.....:%d\n\n",all[i].geburtsjahr);

      if((!(i%2))&& i!=0) {
         printf("\n\tWeiter mit <Enter>\n\n");
         getchar();
      }
   }
}

void Sort(struct adres sort[], int nr) {
   int i,j;
   struct adres *temp;

   temp = malloc(sizeof(struct adres *));
   if(NULL == temp) {
      printf("Konnte keinen Speicher reservieren...\n");
      return;
   }
   for(i = 0; i < nr; i++) {
      for(j=i+1;j<nr;j++) {
         if(strcmp(sort[i].nname, sort[j].nname) > 0) {
            *temp=sort[j];
            sort[j]=sort[i];
            sort[i]=*temp;
         }
      }
   }
   printf(".....Sortiert!!\n\n");
}

void createGeschaeft(int nr, struct neu[]){
   printf("Name : ");
   fgets(neu[nr].name, MAX, stdin);
   printf("ID: ");
   do {
      scanf("%10ld",&neu[nr].ID);
   } while(getchar()!= '\n');
}

void createEinkauf(int nr, struct neu[]{
	printf("... not yet implemented ...");
}

int main(void) {
   int auswahl;
   char c;

   do {
      printf("-10- Neues Geschäft anlegen\n");
      printf("-11- Neuen Einkauf verfassen\n");
      printf("-1- Neue Adresse eingeben\n");
      printf("-2- Bestimmte Adresse ausgeben\n");
      printf("-3- Alle Adressen ausgeben\n");
      printf("-4- Adressen sortieren\n");
      printf("-5- Programm beenden\n");
      printf("\nIhre Auswahl : ");
      scanf("%d",&auswahl);
      /* fflush(stdin); */
      getchar();

      switch(auswahl) {
      	 case 10: createGeschaeft(x_gesch++,geschaefte);
				  break;
		 case 11: createEinkauf(x_eink++,einkauefe);
				  break;
         case 1 : Eingabe(x++,adressen);
                  break;
         case 2 : printf("Anfangsbuchstabe des Nachnamens :");
                  do {
                     scanf("%c",&c);
                  } while(getchar()!= '\n');
                  Suche(adressen,c,x);
                  break;
         case 3 : Ausgabe(adressen,x);
                  break;
         case 4 : Sort(adressen,x);
                  break;
         case 5 : printf("Ende....\n");
                  break;
         default: printf("Falsche Eingabe\n");
				  auswahl = 0;
      }
   }while(auswahl !=5);
   return EXIT_SUCCESS;
}
