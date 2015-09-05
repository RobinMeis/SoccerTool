#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *spielplan;
int spielzeit[4]; //Vorrunde, Halbfinale, Platz 3, Finale
char teams[2][30][10]; //Gruppe, Team (max. 30), Name
int anzahl_teams[2]; //Teams in Gruppen
char vorrunde[30][2][10]; //Spiele in der Vorrunde (max. 30)
int anzahl_spiele; //Spiele in der Vorrunde

void open_spielplan(void) {
  int modus=0, buffer_index, gruppe; //1=Beginn, 2=Spielzeit, 3=Gruppe 1, 4=Gruppe 2, 5=Vorrunde, 6=Ergebnisse, 7=Ende
  char *buffer, data[3][15]; //Buffer

  spielplan = fopen("spielplan.soc", "a+");
  if (spielplan == NULL) {
    g_print("Spielplan kann nicht geoeffnet werden!\n");
    exit(1);
  }

  char line [128];
  while (fgets(line, sizeof(line), spielplan) != NULL) {
    line[strlen(line) - 1] = '\0'; //Zeilenweise auslesen
    buffer_index=0;

    if (!strcmp(line,"+++beginn+++") && modus==0) modus=1; //TODO Ausrufezeichen statt 0
    else if (!strcmp(line,"---spielzeit---") && modus==1) modus=2;  //TODO Ausrufezeichen statt 0
    else if (!strcmp(line,"---gruppe1---") && modus==2) { modus=3; anzahl_teams[0]=0; gruppe=0; }
    else if (!strcmp(line,"---gruppe2---") && modus==3) { modus=4; anzahl_teams[1]=0; gruppe=1; }
    else if (!strcmp(line,"---vorrunde---") && modus==4) { modus=5; anzahl_spiele=0; }
    else if (!strcmp(line,"---ergebnisse---") && modus==5) { modus=6;}
    else if (modus==2 || modus==5) {
      buffer = strtok (line,"-:");
      while (buffer != NULL) {
        strcpy(data[buffer_index], buffer);
        ++buffer_index;
        buffer = strtok (NULL, ":");
      }

      if (modus==2) { //Spielzeit einlesen
        if (!strcmp(data[0],"vorrunde")) spielzeit[0] = atoi(data[1]);
        else if (!strcmp(data[0],"halbfinale")) spielzeit[1] = atoi(data[1]);
        else if (!strcmp(data[0],"platz3")) spielzeit[2] = atoi(data[1]);
        else if (!strcmp(data[0],"finale")) spielzeit[3] = atoi(data[1]);
      } else if (modus==5) { //Vorrunde einlesen
        if (anzahl_spiele<30) {
          strcpy(vorrunde[anzahl_spiele][0], data[1]);
          strcpy(vorrunde[anzahl_spiele][1], data[2]);
          ++anzahl_spiele;
        } else {
          g_print("Fehler: Zu viele Mannschaften in Gruppe %d\n", gruppe);
          exit(0);
        }
      }
    } else if (modus==3 || modus==4) {
      if (anzahl_teams[gruppe]<30) {
        strcpy(teams[gruppe][anzahl_teams[gruppe]], line);
        ++anzahl_teams[gruppe];
      } else {
        g_print("Fehler: Zu viele Mannschaften in Gruppe %d\n", gruppe);
        exit(0);
      }
    }
  }
}

void close_spielplan(void) {
  fclose(spielplan);
}

int get_spielzeit(int typ) { //0=Vorrunde, 1=Halbfinale, 2=Platz 3, 3=Finale
  if (typ>=0 && typ<=3) return spielzeit[typ];
  else return -1;
}
