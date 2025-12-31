/**
 * @file args.h
 * @brief This file exposes the API for the argument parser.
 *
 * This header file define structs and functions to parse the command-line arguments.
 *
 * @author ben
 * @date 12/31/2025
 */

#ifndef SCC_ARGS_H
#define SCC_ARGS_H

#include <stdbool.h>


/**
 * @brief Enum for argument parser flags
 *
 * This enum represents all possible command-line flags.
 */
typedef enum {
  SCC_FLAG_LEX,  // Run the lexer, but stop before parsing.
  SCC_FLAG_PARSE, // Run the lexer and parser, but stop before
                  // assembly generation.
  SCC_FLAG_CODEGEN, // Perform lexing, parsing, and assembly,
                    // generation, but stop before code emission.
  SCC_FLAG_S,  // Generate an assembly file.
  SCC_FLAG_NOT_SET // no flag was set
} arg_flag;            

/**
 * @brief Parse command-line arguments.
 *
 * Identify the correct argument flag (if any).
 *
 * @param flag modify based on the argument falg passed in.
 * @param argc number of arguments
 * @param argv array of arguments
 * @return 0 on success, positive integer otherwise
 */
void args_parse(arg_flag *flag, int argc, char *argv[]);

#endif  // SCC_ARGS_H
