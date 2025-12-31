#include "include/compiler_driver.h"
#include "include/args.h"
#include "include/macros.h"

int main(int argc, char *argv[]) {
  arg_flag flag;

  args_parse(&flag, argc, argv);
  compiler_driver_run(argv[1]);

  SCC_INFO("Finished\n");

  return 0;
}
