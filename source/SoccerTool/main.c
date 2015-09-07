#include <gtk/gtk.h>
#include "windows/admin.h"
#include "windows/beamer.h"
#include "libraries/spielplan.h"
#include "libraries/stoppuhr.h"

static gpointer refresh (gpointer userdata) {
  for(;;) {
    gdk_threads_enter();
    admin_time_refresh();
    beamer_refresh();
    gdk_threads_leave();
    sleep(1); //TODO: Decrease
  }
  return NULL;
}

int main(int argc, char **argv) {
  GThread *thread;

  stoppuhr_init();
  open_spielplan();
  close_spielplan();

  gtk_init(&argc, &argv);

  beamer_init(); //TODO: Swap
  admin_init(); //TODO: Swap

  g_main_context_default(); //TODO: Remove

  thread = g_thread_new(NULL, refresh, GINT_TO_POINTER(3));
  gtk_main();
  return 0;
}
