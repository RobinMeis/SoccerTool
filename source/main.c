#include <gtk/gtk.h>
#include "windows/admin.h"
#include "windows/beamer.h"

int main(int argc, char **argv) {
  gtk_init(&argc, &argv);

  init_admin();
  init_beamer();

  gtk_main();
  return 0;
}
