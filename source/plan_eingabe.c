#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMALE_ANZAHL_TEAMS_PRO_GRUPPE 30 //malloc ist besser, hat es aber in sich für mehrdimmensionale arrays mit Strings
#define MAXIMALE_LAENGE_MANNSCHAFTSNAME  10 //Anzahl Zeichen im Mannschaftsnamen

int mannschaften[2]; //Anzahl Mannschaften in den Gruppen
char teams[2][MAXIMALE_ANZAHL_TEAMS_PRO_GRUPPE][MAXIMALE_LAENGE_MANNSCHAFTSNAME]; //Gruppe, TeamID, TeamName
void ende(void) {
  printf("Enter druecken zum Beenden"); //TODO: fgets kann das besser als scanf
  scanf("%d");
  exit(0);
}

int existiert_teamname(char *name) {
  int i;
  for (i=0; i<mannschaften[0]; ++i)
    if (strcmp(teams[0][i],name) == 0)
      return 1;

  for (i=0; i<mannschaften[1]; ++i)
    if (strcmp(teams[1][i],name) == 0)
      return 1;

  return 0;
}

void teamnamen_eingeben(int gruppe) {
  int i;
  char buffer [MAXIMALE_LAENGE_MANNSCHAFTSNAME];
  printf("Anzahl der Mannschaften in Gruppe %i: ", gruppe+1);
  scanf("%d", &mannschaften[gruppe]);
  if (mannschaften[gruppe]>MAXIMALE_ANZAHL_TEAMS_PRO_GRUPPE) {
    printf("Fehler: Es koennen maximal %d Teams pro Gruppe eingegeben werden!\n",MAXIMALE_ANZAHL_TEAMS_PRO_GRUPPE);
    ende();
  }
  for (i=0; i<mannschaften[gruppe]; ++i) {
    printf("  Team %d: ", i+1);
    scanf("%s", &buffer);
    if (existiert_teamname(buffer)) {
      --i;
      printf("    Fehler: Der Mannschaftsname existiert bereits\n");
      continue;
    }
    strcpy(teams[gruppe][i], buffer);
  }
  printf("\n");
}

void team_liste(void) {
  int i;
  printf("+---------------------------------+\n");
  printf("|    Gruppe 1    |    Gruppe 2    |\n");
  for (i=0; i<mannschaften[0] || i<mannschaften[1]; ++i) {
    printf("|");
    if (i<mannschaften[0]) printf("%-16s", teams[0][i]); else printf("       -        ");
    printf("|");
    if (i<mannschaften[1]) printf("%-16s",  teams[1][i]); else printf("       -        ");
    printf("|\n");
  }
  printf("+---------------------------------+\n\n");
}

void spielplan_eingeben(void) {
  unlink ("spielplan.txt");
  /*FILE *f = fopen("file.txt", "w");
if (f == NULL)
{
    printf("Error opening file!\n");
    exit(1);
}

/* print some text
const char *text = "Write this to the file";
fprintf(f, "Some text: %s\n", text);*/



  int i, anzahl_spiele;
  char team_1[MAXIMALE_LAENGE_MANNSCHAFTSNAME], team_2[MAXIMALE_LAENGE_MANNSCHAFTSNAME];
  printf("Anzahl der Spiele in der Vorrunde: ");
  scanf("%d", &anzahl_spiele);
  printf("Teamnamen wie oben eingeben!");
  for (i=0; i<anzahl_spiele; ++i) {
    printf("\n  Spiel %d: Team ", i+1);
    scanf("%s", &team_1);
    if (!existiert_teamname(team_1)) {
      --i;
      printf("    Fehler: Der Teamname existiert nicht\n");
      continue;
    }
    printf("     gegen Team ");
    scanf("%s", &team_2);
    if (!existiert_teamname(team_2)) {
      --i;
      printf("    Fehler: Der Teamname existiert nicht\n");
      continue;
    } else if (strcmp(team_1, team_2)==0) {
      --i;
      printf("    Fehler: Die Mannschaft kann nicht gegen sich selbst spielen\n");
      continue;
    }
  }
}

int main(void) {

  printf("Spielplan Eingabe V 1.0\n\n");

  teamnamen_eingeben(0);
  teamnamen_eingeben(1);
  team_liste();
  spielplan_eingeben();
  ende();

  return 0;
}
