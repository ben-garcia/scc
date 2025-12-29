/**
 * @file macros.h
 * @brief Header file for helper macros. 
 *
 * This file contains macros used throughout the project.
 *
 * @author ben 
 * @date 12/29/2025
 */

#ifndef SCC_MACROS_H
#define SCC_MACROS_H

// ANSI color escape sequences
#define TERMINAL_RED "\033[31m"
#define TERMINAL_BLUE "\033[34m"
#define TERMINAL_YELLOW "\033[33m"
#define TERMINAL_RESET "\033[0m"

/**
 * @brief Prints a fatal error message and aborts.
 *
 * @param format formatted printf string 
 * @param ... variable args passed to fprintf 
 */
#define SCC_PANIC(format, ...)                            \
    fprintf(stderr, TERMINAL_RED "fatal error" TERMINAL_RESET ": " format "\n", \
          ##__VA_ARGS__)

/**
 * @brief Prints a error message.
 *
 * @param format formatted printf string 
 * @param ... variable args passed to fprintf 
 */
#define SCC_ERROR(format, ...)                                          \
  fprintf(stderr, TERMINAL_RED "error" TERMINAL_RESET ": " format "\n", \
          ##__VA_ARGS__)

/**
 * @brief Prints a warning message.
 *
 * @param format formatted printf string 
 * @param ... variable args passed to printf 
 */
#define SCC_WARN(format, ...)                                                \
  printf(stderr, TERMINAL_YELLOW "warning" TERMINAL_RESET ": " format "\n", \
          ##__VA_ARGS__)

/**
 * @brief Prints a informational message.
 *
 * @param format formatted printf string 
 * @param ... variable args passed to printf 
 */
#define SCC_INFO(format, ...)                                           \
  printf(stderr, TERMINAL_BLUE "info" TERMINAL_RESET ": " format "\n", \
          ##__VA_ARGS__)

/**
 * @brief Prints a debug message.
 *
 * @param format formatted printf string 
 * @param ... variable args passed to printf 
 */
#define SCC_DEBUG(format, ...) \
  printf(stderr, "debug: " format "\n", ##__VA_ARGS__)

#endif // SCC_MACROS_H
