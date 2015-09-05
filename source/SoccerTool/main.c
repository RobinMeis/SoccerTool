#include <gtk/gtk.h>
#include "windows/admin.h"
#include "windows/beamer.h"
#include "libraries/spielplan.h"

int main(int argc, char **argv) {
  open_spielplan();
  close_spielplan();

  gtk_init(&argc, &argv);

  init_admin();
  beamer_init();
  beamer_set_team(0,0,"hans");
  gtk_main();
  return 0;
}
