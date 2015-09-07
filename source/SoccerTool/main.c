#include <gtk/gtk.h>
#include "windows/admin.h"
#include "windows/beamer.h"
#include "libraries/spielplan.h"
#include "libraries/stoppuhr.h"

GMainContext *context;

static gboolean refresh (gpointer userdata) {
  admin_time_refresh();
  beamer_refresh();
  return G_SOURCE_REMOVE;
}

static gpointer thread_func(gpointer user_data) {
  int n_thread = GPOINTER_TO_INT(user_data);
  int n;
  GSource *source;

  g_print("Countdown Thread gestartet");
  for(;;) {
    source = g_idle_source_new();
    g_source_set_callback(source, refresh, NULL, NULL);
    g_source_attach(source, context);
    g_source_unref(source);
    sleep(1); //TODO: Decrease
  }
  g_print("Fehler: Countdown Thread beendet\n");
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

  context = g_main_context_default();

  thread = g_thread_new(NULL, thread_func, GINT_TO_POINTER(3));
  gtk_main();
  return 0;
}
