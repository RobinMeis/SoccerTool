#include <gtk/gtk.h>
#include "../libraries/sound.h"
GtkWidget *fenster, *table, *trennstrich;
GtkWidget *name[2][2], *tore[2][2]; //Keys: Spielfeld, Team
GtkWidget *zeit[2]; //Key: Spielfeld

void check_button_press_cb(GtkWidget *widget, gpointer data) {
  if (!strcmp("pfeife", (char *)data))
    play_whistle(1);

 if(strcmp("Button 1", (char *)data) == 0)
   g_print("Button 1 wurde gedrückt\n");
 else if(strcmp("Button 2", (char *)data) == 0)
   g_print("Button 2 wurde gedrückt\n");
 else if(strcmp("Button 3", (char *)data) == 0)
   g_print("Button 3 wurde gedrückt\n");
 else if(strcmp("Button 4", (char *)data) == 0)
   g_print("Button 4 wurde gedrückt\n");
 else
   g_print("%s\n",(char *)data);
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

  zeit[0]  = gtk_label_new("10:00"); //Feld 1
  name[0][0]  = gtk_label_new("-");
  name[0][1]  = gtk_label_new("-");
  tore[0][0]  = gtk_label_new("0");
  tore[0][1]  = gtk_label_new("0");

  gtk_widget_modify_font (zeit[0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (name[0][0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (name[0][1],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (tore[0][0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (tore[0][1],pango_font_description_from_string ("Arial 50"));

  gtk_table_attach(GTK_TABLE(table), tore[0][0], 0,1, 1,2, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), name[0][0], 1,2, 1,2, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), zeit[0], 0,1, 3,5, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), tore[0][1], 0,1, 7,8, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), name[0][1], 1,2, 7,8, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);

  zeit[1]  = gtk_label_new("10:00"); //Feld 2
  name[1][0]  = gtk_label_new("-");
  name[1][1]  = gtk_label_new("-");
  tore[1][0]  = gtk_label_new("0");
  tore[1][1]  = gtk_label_new("0");

  gtk_widget_modify_font (zeit[1],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (name[1][0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (name[1][1],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (tore[1][0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (tore[1][1],pango_font_description_from_string ("Arial 50"));

  gtk_table_attach(GTK_TABLE(table), name[1][0], 5,6, 1,2, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), tore[1][0], 6,7, 1,2, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), zeit[1], 6,7, 3,5, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), name[1][1], 5,6, 7,8, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), tore[1][1], 6,7, 7,8, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);

  trennstrich = gtk_image_new_from_file ("images/trennstrich.png");
  //gtk_table_attach(GTK_TABLE(table), trennstrich, 0,6, 0,7, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);

  button_team11minus = gtk_button_new_with_label("-"); //Buttons Feld 1
  button_team11plus = gtk_button_new_with_label("+");
  button_team12plus = gtk_button_new_with_label("+");
  button_team12minus = gtk_button_new_with_label("-");
  button_start1 = gtk_button_new_with_label("Start");
  button_stop1 = gtk_button_new_with_label("Stop");

  gtk_signal_connect(GTK_OBJECT(button_team11plus), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb),"button_team11plus");
  gtk_signal_connect(GTK_OBJECT(button_team11minus), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb), "button_team11minus");
  gtk_signal_connect(GTK_OBJECT(button_team12plus), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb),"button_team12plus");
  gtk_signal_connect(GTK_OBJECT(button_team12minus), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb), "button_team12minus");

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

  gtk_signal_connect(GTK_OBJECT(button_team21plus), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb),"button_team21plus");
  gtk_signal_connect(GTK_OBJECT(button_team21minus), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb), "button_team21minus");
  gtk_signal_connect(GTK_OBJECT(button_team22plus), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb),"button_team22plus");
  gtk_signal_connect(GTK_OBJECT(button_team22minus), "clicked", GTK_SIGNAL_FUNC(check_button_press_cb), "button_team22minus");

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

  gtk_table_attach(GTK_TABLE(table), button_start_gemeinsam, 4,5, 3,4, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), button_stop_gemeinsam, 4,5, 4,5, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);

  gtk_table_attach(GTK_TABLE(table), button_vorheriges_spiel, 1,2, 9,10, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), button_naechstes_spiel, 5,6, 9,10, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), button_beamer_aus, 0,1, 9,10, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), button_beamer_invertieren, 6,7, 9,10, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), button_pfeife, 4,5, 9,10, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_EXPAND|GTK_SHRINK,0,0);


  gtk_container_add(GTK_CONTAINER(fenster),table); //Widgets anzeigen
  gtk_widget_show_all(fenster);
}
