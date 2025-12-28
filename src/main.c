#include "include/compiler_driver.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "usage: ./build/scc <source>\n");
    return EXIT_FAILURE;
  }

  compiler_driver_run(argv[1]);

  printf("Finished\n");

  return 0;
}
