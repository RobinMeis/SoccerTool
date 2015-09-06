#include <gtk/gtk.h>
#include "windows/admin.h"
#include "windows/beamer.h"
#include "libraries/spielplan.h"
#include "libraries/stoppuhr.h"

int main(int argc, char **argv) {
  stoppuhr_init();
  open_spielplan();
  close_spielplan();

  gtk_init(&argc, &argv);

  beamer_init(); //TODO: Swap
  admin_init(); //TODO: Swap
  gtk_main();
  return 0;
}
