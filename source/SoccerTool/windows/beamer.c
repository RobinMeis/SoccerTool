#include <gtk/gtk.h>
#include <stdlib.h>
#include "../libraries/stoppuhr.h"
#include "../libraries/spielplan.h"
#include "../libraries/beamer_control.h"

GtkWidget *fenster, *table, *trennstrich;
GtkWidget *beamer_name[2][2], *beamer_tore[2][2], *feld_bezeichnung[2][2]; //Keys: Spielfeld, Team
GtkWidget *beamer_zeit[2]; //Key: Spielfeld

void beamer_refresh(void) {
  time_t rawtime;
  struct tm *info;
  char buffer[6];
  int feld, team;

    rawtime=stoppuhr_get(0); //Feld 1 TODO: nach link rücken
    info = localtime( &rawtime );
    strftime(buffer,6,"%M:%S", info);
    gtk_label_set_label (GTK_LABEL(beamer_zeit[0]), buffer);

    rawtime=stoppuhr_get(1); //Feld 2
    info = localtime( &rawtime );
    strftime(buffer,6,"%M:%S", info);
    gtk_label_set_label (GTK_LABEL(beamer_zeit[1]), buffer);

    gtk_label_set_label (GTK_LABEL(beamer_name[0][0]), get_team(0,0)); //Teams anzeigen
    gtk_label_set_label (GTK_LABEL(beamer_name[0][1]), get_team(0,1));
    gtk_label_set_label (GTK_LABEL(beamer_name[1][0]), get_team(1,0));
    gtk_label_set_label (GTK_LABEL(beamer_name[1][1]), get_team(1,1));

    for (feld=0; feld<2; ++feld) //Tore anzeigen
      for (team=0; team<2; ++team) {
        snprintf(buffer, 5, "%d", get_tore(feld,team));
        gtk_label_set_label (GTK_LABEL(beamer_tore[feld][team]), buffer);
      }
}

void beamer_init(void) {
  fenster = gtk_window_new(GTK_WINDOW_TOPLEVEL); //Fenster initialisieren
  gtk_signal_connect(GTK_OBJECT(fenster), "destroy",GTK_SIGNAL_FUNC(gtk_main_quit),NULL);
  gtk_window_set_default_size(GTK_WINDOW(fenster), 1024, 768);
  gtk_window_set_title(GTK_WINDOW(fenster), "Beamer");
  beamer_control_init(fenster);
  beamer_on();
  gtk_widget_show(fenster);
  table = gtk_table_new(5,6,FALSE);

  beamer_zeit[0]  = gtk_label_new("10:00"); //Feld 1
  beamer_name[0][0]  = gtk_label_new("-");
  beamer_name[0][1]  = gtk_label_new("-");
  beamer_tore[0][0]  = gtk_label_new("0");
  beamer_tore[0][1]  = gtk_label_new("0");
  feld_bezeichnung[0][0] = gtk_label_new("Feld 1A");
  feld_bezeichnung[0][1] = gtk_label_new("Feld 2A");

  gtk_widget_modify_font (beamer_zeit[0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (beamer_name[0][0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (beamer_name[0][1],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (beamer_tore[0][0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (beamer_tore[0][1],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (feld_bezeichnung[0][0],pango_font_description_from_string ("Arial 25"));
  gtk_widget_modify_font (feld_bezeichnung[0][1],pango_font_description_from_string ("Arial 25"));

  gtk_table_attach(GTK_TABLE(table), feld_bezeichnung[0][0], 0,2, 0,1, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), beamer_tore[0][0], 0,1, 1,2, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), beamer_name[0][0], 1,2, 1,2, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), beamer_zeit[0], 0,2, 2,3, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), feld_bezeichnung[0][1], 0,2, 3,4, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), beamer_tore[0][1], 0,1, 4,5, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), beamer_name[0][1], 1,2, 4,5, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);

  beamer_zeit[1]  = gtk_label_new("10:00"); //Feld 2
  beamer_name[1][0]  = gtk_label_new("-");
  beamer_name[1][1]  = gtk_label_new("-");
  beamer_tore[1][0]  = gtk_label_new("0");
  beamer_tore[1][1]  = gtk_label_new("0");
  feld_bezeichnung[1][0] = gtk_label_new("Feld 1B");
  feld_bezeichnung[1][1] = gtk_label_new("Feld 2B");

  gtk_widget_modify_font (beamer_zeit[1],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (beamer_name[1][0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (beamer_name[1][1],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (beamer_tore[1][0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (beamer_tore[1][1],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (feld_bezeichnung[1][0],pango_font_description_from_string ("Arial 25"));
  gtk_widget_modify_font (feld_bezeichnung[1][1],pango_font_description_from_string ("Arial 25"));

  gtk_table_attach(GTK_TABLE(table), feld_bezeichnung[1][0], 3,5, 0,1, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), beamer_name[1][0], 3,4, 1,2, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), beamer_tore[1][0], 4,5, 1,2, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), beamer_zeit[1], 3,5, 2,3, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), feld_bezeichnung[1][1], 3,5, 3,4, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), beamer_name[1][1], 3,4, 4,5, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), beamer_tore[1][1], 4,5, 4,5, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);


  trennstrich = gtk_image_new_from_file ("images/trennstrich.png");
  gtk_table_attach(GTK_TABLE(table), trennstrich, 0,6, 0,5, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);

  gtk_container_add(GTK_CONTAINER(fenster),table); //Widgets anzeigen
  gtk_widget_show_all(fenster);
}
