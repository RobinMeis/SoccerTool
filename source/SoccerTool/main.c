#include <gtk/gtk.h>
#include "windows/admin.h"
#include "windows/beamer.h"

int main(int argc, char **argv) {
  gtk_init(&argc, &argv);

  init_admin();
  beamer_init();
  beamer_set_team(0,0,"hans");
  gtk_main();
  return 0;
}
