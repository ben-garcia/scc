#ifndef SCC_COMPILER_DRIVER_H
#define SCC_COMPILER_DRIVER_H

// Serves as a wrapper for the following:
// 1. Preprocessor
// 2. Compiler
// 3. Assembler
// 4. Linker

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCC_PANIC(message)                      \
  do {                                          \
    fprintf(stderr, "Error: %s \n", (message)); \
    abort();                                    \
  } while (0);

int compiler_driver_run(const char *const filename);

#endif  // SCC_COMPILER_DRIVER_H
