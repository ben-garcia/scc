/**
 * @file compiler_driver.h
 * @brief Serves as the wrapper for the whole c compilation process.
 *
 * Compiler driver exposes a single function.
 *
 * @author ben
 * @date 12/29/2025
 */

#ifndef SCC_COMPILER_DRIVER_H
#define SCC_COMPILER_DRIVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Compile C source code.
 *
 * Generate an executable file from source code.
 *
 * @param filename file that be compiled
 * @return 0 on success, positive integer otherwise
 */
int compiler_driver_run(const char *const filename);

#endif  // SCC_COMPILER_DRIVER_H
