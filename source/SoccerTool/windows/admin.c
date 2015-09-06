#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include "../libraries/sound.h"
#include "../libraries/stoppuhr.h"
#include "../libraries/spielplan.h"

GtkWidget *fenster, *table;
GtkWidget *admin_name[2][2], *admin_tore[2][2]; //Keys: Spielfeld, Team
GtkWidget *admin_zeit[2]; //Key: Spielfeld

void admin_refresh(void) {
  char buffer[6];
  int team, feld;

  gtk_label_set_label (GTK_LABEL(admin_name[0][0]), get_team(0,0)); //Teams anzeigen
  gtk_label_set_label (GTK_LABEL(admin_name[0][1]), get_team(0,1));
  gtk_label_set_label (GTK_LABEL(admin_name[1][0]), get_team(1,0));
  gtk_label_set_label (GTK_LABEL(admin_name[1][1]), get_team(1,1));

  for (feld=0; feld<2; ++feld) //Tore anzeigen
    for (team=0; team<2; ++team) {
      snprintf(buffer, 5, "%d", get_tore(feld,team));
      gtk_label_set_label (GTK_LABEL(admin_tore[feld][team]), buffer);
    }
}

void check_button_press_cb(GtkWidget *widget, gpointer data) {
  if (!strcmp("pfeife", (char *)data))
    play_whistle(1);
  else if (!strcmp("start_gemeinsam", (char *)data)) {
    stoppuhr_start(0);
    stoppuhr_start(1);
  } else if (!strcmp("stop_gemeinsam", (char *)data)) {
    stoppuhr_stop(0);
    stoppuhr_stop(1);
  } else if (!strcmp("team1start", (char *)data))
    stoppuhr_start(0);
  else if (!strcmp("team1stop", (char *)data))
    stoppuhr_stop(0);
  else if (!strcmp("team2start", (char *)data))
    stoppuhr_start(1);
  else if (!strcmp("team2stop", (char *)data))
    stoppuhr_stop(1);
  else if (!strcmp("naechstes_spiel", (char *)data))
    naechstes_spiel();
  else if (!strcmp("vorheriges_spiel", (char *)data))
    vorheriges_spiel();
  else if (!strcmp("team11plus", (char *)data))
    tor_inkrementieren(0,0);
  else if (!strcmp("team11minus", (char *)data))
    tor_dekrementieren(0,0);
  else if (!strcmp("team12plus", (char *)data))
    tor_inkrementieren(0,1);
  else if (!strcmp("team12minus", (char *)data))
    tor_dekrementieren(0,1);
  else if (!strcmp("team21plus", (char *)data))
    tor_inkrementieren(1,0);
  else if (!strcmp("team21minus", (char *)data))
    tor_dekrementieren(1,0);
  else if (!strcmp("team22plus", (char *)data))
    tor_inkrementieren(1,1);
  else if (!strcmp("team22minus", (char *)data))
    tor_dekrementieren(1,1);
  else
   g_print("Unbekanntes Event: %s\n",(char *)data);
   admin_refresh();
}

void *thread_admin_refresh(void *none) {
  time_t rawtime;
  struct tm *info;
  char buffer[6];

  for(;;) {
    rawtime=stoppuhr_get(0); //Feld 1
    info = localtime( &rawtime );
    strftime(buffer,6,"%M:%S", info);
    gtk_label_set_label (GTK_LABEL(admin_zeit[0]), buffer);

    rawtime=stoppuhr_get(1); //Feld 2
    info = localtime( &rawtime );
    strftime(buffer,6,"%M:%S", info);
    gtk_label_set_label (GTK_LABEL(admin_zeit[1]), buffer);
    admin_refresh(); //TODO Remove!
    sleep(1); //TODO: Decrease
  }
}

void admin_init(void) {
  fenster = gtk_window_new(GTK_WINDOW_TOPLEVEL); //Fenster initialisieren
  GtkWidget *button_team11plus, *button_team11minus, *button_team12plus, *button_team12minus, *button_start1, *button_stop1; //Buttons Feld 1
  GtkWidget *button_team21plus, *button_team21minus, *button_team22plus, *button_team22minus, *button_start2, *button_stop2; //Buttons Feld 2
  GtkWidget *button_start_gemeinsam, *button_stop_gemeinsam, *button_naechstes_spiel, *button_vorheriges_spiel, *button_beamer_invertieren, *button_beamer_aus, *button_pfeife; //Systrembuttons
  gtk_signal_connect(GTK_OBJECT(fenster), "destroy",GTK_SIGNAL_FUNC(gtk_main_quit),NULL);
  gtk_window_set_default_size(GTK_WINDOW(fenster), 1024, 768);
  gtk_window_set_title(GTK_WINDOW(fenster), "Administration");
  gtk_widget_show(fenster);
  table = gtk_table_new(13,10,FALSE);

  admin_zeit[0]  = gtk_label_new("10:00"); //Feld 1
  admin_name[0][0]  = gtk_label_new("-");
  admin_name[0][1]  = gtk_label_new("-");
  admin_tore[0][0]  = gtk_label_new("0");
  admin_tore[0][1]  = gtk_label_new("0");

  gtk_widget_modify_font (admin_zeit[0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (admin_name[0][0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (admin_name[0][1],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (admin_tore[0][0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (admin_tore[0][1],pango_font_description_from_string ("Arial 50"));

  gtk_table_attach(GTK_TABLE(table), admin_tore[0][0], 0,1, 1,2, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), admin_name[0][0], 1,2, 1,2, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), admin_zeit[0], 0,1, 3,5, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), admin_tore[0][1], 0,1, 7,8, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), admin_name[0][1], 1,2, 7,8, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);

  admin_zeit[1]  = gtk_label_new("10:00"); //Feld 2
  admin_name[1][0]  = gtk_label_new("-");
  admin_name[1][1]  = gtk_label_new("-");
  admin_tore[1][0]  = gtk_label_new("0");
  admin_tore[1][1]  = gtk_label_new("0");

  gtk_widget_modify_font (admin_zeit[1],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (admin_name[1][0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (admin_name[1][1],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (admin_tore[1][0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (admin_tore[1][1],pango_font_description_from_string ("Arial 50"));

  gtk_table_attach(GTK_TABLE(table), admin_name[1][0], 5,6, 1,2, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), admin_tore[1][0], 6,7, 1,2, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), admin_zeit[1], 6,7, 3,5, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), admin_name[1][1], 5,6, 7,8, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), admin_tore[1][1], 6,7, 7,8, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);

  button_team11minus = gtk_button_new_with_label("-"); //Buttons Feld 1
  button_team11plus = gtk_button_new_with_label("+");
  button_team12plus = gtk_button_new_with_label("+");
  button_team12minus = gtk_button_new_with_label("-");
  button_start1 = gtk_button_new_with_label("Start");
  button_stop1 = gtk_button_new_with_label("Stop");

  gtk_signal_connect(GTK_OBJECT(button_team11plus), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb),"team11plus");
  gtk_signal_connect(GTK_OBJECT(button_team11minus), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb), "team11minus");
  gtk_signal_connect(GTK_OBJECT(button_team12plus), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb),"team12plus");
  gtk_signal_connect(GTK_OBJECT(button_team12minus), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb), "team12minus");
  gtk_signal_connect(GTK_OBJECT(button_start1), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb), "team1start");
  gtk_signal_connect(GTK_OBJECT(button_stop1), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb), "team1stop");

  gtk_table_attach(GTK_TABLE(table), button_team11minus, 0,1, 0,1, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), button_team11plus, 0,1, 2,3, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), button_start1, 0,1, 3,4, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), button_stop1, 0,1, 4,5, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), button_team12plus, 0,1, 6,7, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), button_team12minus, 0,1, 8,9, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);


  button_team21minus  = gtk_button_new_with_label("-"); //Buttons Feld 2
  button_team21plus  = gtk_button_new_with_label("+");
  button_team22plus  = gtk_button_new_with_label("+");
  button_team22minus  = gtk_button_new_with_label("-");
  button_start2 = gtk_button_new_with_label("Start");
  button_stop2 = gtk_button_new_with_label("Stop");

  gtk_signal_connect(GTK_OBJECT(button_team21plus), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb),"team21plus");
  gtk_signal_connect(GTK_OBJECT(button_team21minus), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb), "team21minus");
  gtk_signal_connect(GTK_OBJECT(button_team22plus), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb),"team22plus");
  gtk_signal_connect(GTK_OBJECT(button_team22minus), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb), "team22minus");
  gtk_signal_connect(GTK_OBJECT(button_start2), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb), "team2start");
  gtk_signal_connect(GTK_OBJECT(button_stop2), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb), "team2stop");

  gtk_table_attach(GTK_TABLE(table), button_team21minus, 6,7, 0,1, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), button_team21plus, 6,7, 2,3, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), button_start2, 6,7, 3,4, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), button_stop2, 6,7, 4,5, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), button_team22plus, 6,7, 6,7, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), button_team22minus, 6,7, 8,9, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);

  button_start_gemeinsam = gtk_button_new_with_label("Alle Start"); //Systembuttons
  button_stop_gemeinsam = gtk_button_new_with_label("Alle Stop");

  button_vorheriges_spiel = gtk_button_new_with_label("Vorheriges Spiel");
  button_naechstes_spiel = gtk_button_new_with_label("Nächstes Spiel");
  button_beamer_aus = gtk_button_new_with_label("Beamer an/aus");
  button_beamer_invertieren = gtk_button_new_with_label("Beamer invertieren");
  button_pfeife = gtk_button_new_with_label("Pfeife");

  gtk_signal_connect(GTK_OBJECT(button_pfeife), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb), "pfeife");
  gtk_signal_connect(GTK_OBJECT(button_start_gemeinsam), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb), "start_gemeinsam");
  gtk_signal_connect(GTK_OBJECT(button_stop_gemeinsam), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb), "stop_gemeinsam");
  gtk_signal_connect(GTK_OBJECT(button_vorheriges_spiel), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb), "vorheriges_spiel");
  gtk_signal_connect(GTK_OBJECT(button_naechstes_spiel), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb), "naechstes_spiel");

  gtk_table_attach(GTK_TABLE(table), button_start_gemeinsam, 4,5, 3,4, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), button_stop_gemeinsam, 4,5, 4,5, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);

  gtk_table_attach(GTK_TABLE(table), button_vorheriges_spiel, 1,2, 9,10, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), button_naechstes_spiel, 5,6, 9,10, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), button_beamer_aus, 0,1, 9,10, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), button_beamer_invertieren, 6,7, 9,10, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), button_pfeife, 4,5, 9,10, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);

  gtk_container_add(GTK_CONTAINER(fenster),table); //Widgets anzeigen
  gtk_widget_show_all(fenster);

  pthread_t inc_thread_admin_refresh; //thread starten
  if(pthread_create(&inc_thread_admin_refresh, NULL, thread_admin_refresh, &admin_zeit)) {
    fprintf(stderr, "Error creating thread\n");
    exit (1);
  }
}
