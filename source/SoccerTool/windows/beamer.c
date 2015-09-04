#include <gtk/gtk.h>
GtkWidget *fenster, *table, *trennstrich;
GtkWidget *name[2][2], *tore[2][2]; //Keys: Spielfeld, Team
GtkWidget *zeit[2]; //Key: Spielfeld

void beamer_init(void) {
  fenster = gtk_window_new(GTK_WINDOW_TOPLEVEL); //Fenster initialisieren
  gtk_signal_connect(GTK_OBJECT(fenster), "destroy",GTK_SIGNAL_FUNC(gtk_main_quit),NULL);
  gtk_window_set_default_size(GTK_WINDOW(fenster), 1024, 768);
  gtk_window_set_title(GTK_WINDOW(fenster), "Beamer");
  gtk_widget_show(fenster);
  table = gtk_table_new(6,3,FALSE);

  zeit[0]  = gtk_label_new("10:00"); //Feld 1
  name[0][0]  = gtk_label_new("BGM");
  name[0][1]  = gtk_label_new("G11");
  tore[0][0]  = gtk_label_new("1");
  tore[0][1]  = gtk_label_new("2");

  gtk_widget_modify_font (zeit[0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (name[0][0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (name[0][1],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (tore[0][0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (tore[0][1],pango_font_description_from_string ("Arial 50"));


  gtk_table_attach(GTK_TABLE(table), tore[0][0], 0,1, 0,1, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), name[0][0], 1,2, 0,1, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), zeit[0], 0,2, 1,2, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), tore[0][1], 0,1, 2,3, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), name[0][1], 1,2, 2,3, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);

  zeit[1]  = gtk_label_new("10:00"); //Feld 2
  name[1][0]  = gtk_label_new("BGE");
  name[1][1]  = gtk_label_new("SOB");
  tore[1][0]  = gtk_label_new("3");
  tore[1][1]  = gtk_label_new("4");

  gtk_widget_modify_font (zeit[1],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (name[1][0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (name[1][1],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (tore[1][0],pango_font_description_from_string ("Arial 50"));
  gtk_widget_modify_font (tore[1][1],pango_font_description_from_string ("Arial 50"));

  gtk_table_attach(GTK_TABLE(table), name[1][0], 3,4, 0,1, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), tore[1][0], 4,5, 0,1, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), zeit[1], 3,5, 1,2, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), name[1][1], 3,4, 2,3, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);
  gtk_table_attach(GTK_TABLE(table), tore[1][1], 4,5, 2,3, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);


  trennstrich = gtk_image_new_from_file ("binaries/images/trennstrich.png");
  gtk_table_attach(GTK_TABLE(table), trennstrich, 2,3, 0,3, GTK_FILL|GTK_EXPAND|GTK_SHRINK,GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,0);

  gtk_container_add(GTK_CONTAINER(fenster),table); //Widgets anzeigen
  gtk_label_set_text (name[0][0], "Hallo");
  gtk_widget_show_all(fenster);
}

int beamer_set_team(int feld, int team, const char *team_name) {
  if (feld < 0 || feld > 1 || team < 0 || team > 1)
    return 0;
  //gtk_label_set_text (name[feld][team], team_name);
  return 1;
}
