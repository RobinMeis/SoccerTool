#include <gtk/gtk.h>
GtkWidget *fenster;

void init_beamer(void) {
  fenster = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_signal_connect(GTK_OBJECT(fenster), "destroy",GTK_SIGNAL_FUNC(gtk_main_quit),NULL);
   gtk_window_set_default_size(GTK_WINDOW(fenster), 1024, 768);
  gtk_window_set_title(GTK_WINDOW(fenster), "Beamer");
  gtk_widget_show(fenster);
}
