#include <gtk/gtk.h>

int beamer_state=1; //1=On, 0=Off
GtkWidget *beamer_fenster_ptr;

void beamer_control_init(GtkWidget *fenster_ptr) {
  beamer_fenster_ptr = fenster_ptr;
  gtk_widget_modify_font (beamer_fenster_ptr,pango_font_description_from_string ("Arial 50"));

}

void beamer_off() {
  beamer_state=0;
  GdkColor color;
  color.red = 0x0000;
  color.green = 0x0000;
  color.blue = 0x0000;
  gtk_widget_modify_bg(beamer_fenster_ptr, GTK_STATE_NORMAL, &color);
}

void beamer_on() {
  beamer_state=1;
  GdkColor color;
  color.red = 0xffff;
  color.green = 0xffff;
  color.blue = 0xffff;
  gtk_widget_modify_bg(beamer_fenster_ptr, GTK_STATE_NORMAL, &color);


}

void beamer_on_off() {
  if (beamer_state==1) beamer_off();
  else beamer_on();
}
