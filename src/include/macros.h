/**
 * @file macros.h
 * @brief Header file for helper macros.
 *
 * This file contains macros used throughout the project.
 *
 * @author ben
 * @date 12/31/2025
 */

#ifndef SCC_MACROS_H
#define SCC_MACROS_H

#include <stdio.h>
#include <stdlib.h>

// ANSI color escape sequences
#define TERMINAL_RED "\033[31m"
#define TERMINAL_BLUE "\033[34m"
#define TERMINAL_YELLOW "\033[33m"
#define TERMINAL_RESET "\033[0m"

#define PROGRAM_NAME "scc"

/**
 * @brief error status codes
 *
 * Possible status codes for the program.
 */
enum scc_status_codes {
  SCC_SUCCESS,
  SCC_FAILURE,
  SCC_ERROR_INVALID_NUMBER_OF_ARGS,
  SCC_ERROR_INVALID_ARGS,
  SSC_ERROR_NOT_C_FILE,
  SCC_ERROR_FILE_NOT_FOUND,
};

/**
 * @brief Prints a fatal error message and aborts.
 *
 * @param format formatted printf string
 * @param ... variable args passed to fprintf
 */
#define SCC_PANIC(format, ...)                                                \
  fprintf(stderr, PROGRAM_NAME ": " TERMINAL_RED "fatal error" TERMINAL_RESET ": " format "\n", \
          ##__VA_ARGS__)

/**
 * @brief Prints a error message.
 *
 * @param format formatted printf string
 * @param ... variable args passed to fprintf
 */
#define SCC_ERROR(format, ...)                                          \
  fprintf(stderr, PROGRAM_NAME ": " TERMINAL_RED "error" TERMINAL_RESET ": " format "\n", \
          ##__VA_ARGS__)

/**
 * @brief Prints a warning message.
 *
 * @param format formatted printf string
 * @param ... variable args passed to printf
 */
#define SCC_WARN(format, ...)                                               \
  printf(stderr, PROGRAM_NAME ": " TERMINAL_YELLOW "warning" TERMINAL_RESET ": " format "\n", \
         ##__VA_ARGS__)

/**
 * @brief Prints a informational message.
 *
 * @param format formatted printf string
 * @param ... variable args passed to printf
 */
#define SCC_INFO(format, ...) printf(format "\n", ##__VA_ARGS__)

/**
 * @brief Prints a debug message.
 *
 * @param format formatted printf string
 * @param ... variable args passed to printf
 */
#define SCC_DEBUG(format, ...) \
  printf(PROGRAM_NAME ": " "debug:%s:%d " format "\n", __FILE_NAME__, __LINE__, ##__VA_ARGS__)

/**
 * @brief Terminate the program.
 *
 * @param code exit code
 *
 */
#define SCC_EXIT(code) exit((code))

#endif  // SCC_MACROS_H
