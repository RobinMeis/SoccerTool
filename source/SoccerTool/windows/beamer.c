#include <gtk/gtk.h>
#include "../libraries/stoppuhr.h"
GtkWidget *fenster, *table, *trennstrich;
GtkWidget *beamer_name[2][2], *beamer_tore[2][2]; //Keys: Spielfeld, Team
GtkWidget *beamer_zeit[2]; //Key: Spielfeld

void *thread_beamer_refresh(void *none) {
  time_t rawtime;
  struct tm *info;
  char buffer[6];

  for(;;) {
    rawtime=stoppuhr_get(0); //Feld 1
    info = localtime( &rawtime );
    strftime(buffer,6,"%M:%S", info);
    gtk_label_set_label (beamer_zeit[0], buffer);

    rawtime=stoppuhr_get(1); //Feld 2
    info = localtime( &rawtime );
    strftime(buffer,6,"%M:%S", info);
    gtk_label_set_label (beamer_zeit[1], buffer);
    sleep(1);
  }
}

void beamer_init(void) {
  fenster = gtk_window_new(GTK_WINDOW_TOPLEVEL); //Fenster initialisieren
  gtk_signal_connect(GTK_OBJECT(fenster), "destroy",GTK_SIGNAL_FUNC(gtk_main_quit),NULL);
  gtk_window_set_default_size(GTK_WINDOW(fenster), 1024, 768);
  gtk_window_set_title(GTK_WINDOW(fenster), "Beamer");
  gtk_widget_show(fenster);
  table = gtk_table_new(5,3,FALSE);

  beamer_zeit[0]  = gtk_label_new("10:00"); //Feld 1
  beamer_name[0][0]  = gtk_label_new("-");
  beamer_name[0][1]  = gtk_label_new("-");
  beamer_tore[0][0]  = gtk_label_new("0");
  beamer_tore[0][1]  = gtk_label_new("0");

  gtk_widget_modify_font (beamer_zeit[0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (beamer_name[0][0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (beamer_name[0][1],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (beamer_tore[0][0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (beamer_tore[0][1],pango_font_description_from_string ("Arial 50"));


  gtk_table_attach(GTK_TABLE(table), beamer_tore[0][0], 0,1, 0,1, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), beamer_name[0][0], 1,2, 0,1, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), beamer_zeit[0], 0,2, 1,2, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), beamer_tore[0][1], 0,1, 2,3, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), beamer_name[0][1], 1,2, 2,3, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);

  beamer_zeit[1]  = gtk_label_new("10:00"); //Feld 2
  beamer_name[1][0]  = gtk_label_new("-");
  beamer_name[1][1]  = gtk_label_new("-");
  beamer_tore[1][0]  = gtk_label_new("0");
  beamer_tore[1][1]  = gtk_label_new("0");

  gtk_widget_modify_font (beamer_zeit[1],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (beamer_name[1][0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (beamer_name[1][1],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (beamer_tore[1][0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (beamer_tore[1][1],pango_font_description_from_string ("Arial 50"));

  gtk_table_attach(GTK_TABLE(table), beamer_name[1][0], 3,4, 0,1, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), beamer_tore[1][0], 4,5, 0,1, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), beamer_zeit[1], 3,5, 1,2, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), beamer_name[1][1], 3,4, 2,3, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), beamer_tore[1][1], 4,5, 2,3, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);


  trennstrich = gtk_image_new_from_file ("images/trennstrich.png");
  gtk_table_attach(GTK_TABLE(table), trennstrich, 0,6, 0,3, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);

  gtk_container_add(GTK_CONTAINER(fenster),table); //Widgets anzeigen
  gtk_widget_show_all(fenster);

  pthread_t inc_thread_beamer_refresh; //thread starten
  if(pthread_create(&inc_thread_beamer_refresh, NULL, thread_beamer_refresh, &beamer_zeit)) {
    fprintf(stderr, "Error creating thread\n");
    exit (1);
  }
}

int beamer_set_team(int feld, int team, const char *team_beamer_name) {
  if (feld < 0 || feld > 1 || team < 0 || team > 1) { g_print("Fehler set_team"); return 0; }
  gtk_label_set_text (beamer_name[feld][team], team_beamer_name);
  return 1;
}
