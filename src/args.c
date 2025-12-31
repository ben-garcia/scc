/**
 * @file args.c
 * @brief This file exposes the API for the argument parser.
 *
 * This header file define functions to parser the command-line arguments.
 *
 * @author ben
 * @date 12/31/2025
 */

#include "include/args.h"

#include <string.h>

#include "include/macros.h"

/**
 * @brief Prints a message about how use the program.
 *
 * @note An argument flag can be added befor or after the <source_file> param.
 */
static void print_usage() {
  SCC_INFO("usage: ./build/scc [option] <source_file>\n");
  SCC_INFO(
      "Description: Processes the source file and generates an output file "
      "based on the specified option.\n");
  SCC_INFO(
      "Options:\n"
      "  --lex           Run the lexer, but stop before parsing.\n"
      "  --parse         Run the lexer and parser, but stop before assembly "
      "generation\n"
      "  --codegen       Run the lexer, parser, and assembly generation, but "
      "stop "
      "before code emission\n"
      "  -S              Generate an assembly file\n");
  SCC_INFO(
      "Arguments:\n"
      "  <source_file>   The C source file to compile.\n");
  SCC_INFO(
      "Examples:\n"
      "  ./build/scc --lex  main.c\n"
      "  ./build/scc main.c --lex\n");
}

/**
 * @brief Validate a command-line flag.
 *
 * Checks that the flag param is a one of the following:
 *  '--lex', '--parse', '--codegen', and '-S'
 *
 * @param flag command-line flag to validate
 * @return 0 on success, 1 on otherwise
 */
static bool is_valid_flag(const char *const flag) {
  char *valid_flags[4] = {"--lex", "--parse", "--codegen", "-S"};

  for (int i = 0; i < 4; i++) {
    if (strcmp(flag, valid_flags[i]) == 0) {
      return SCC_SUCCESS;
    }
  }
  return SCC_FAILURE;
}

/**
 * @brief Validate a C file.
 *
 * This function checks that the file exists, and has '.c' extension.
 *
 * @param filename file to validate
 * @return true on success, false on file no found, not c file error.
 */
static bool is_valid_c_file(const char *const filename) {
  // make sure the file has the c extension before trying to open it.
  if (strcmp(filename + strlen(filename) - 2, ".c") != 0) {
    SCC_ERROR("invalid c file detected '%s'", filename);
    return false;
  }

  FILE *file;
  // check that file exists
  if ((file = fopen(filename, "r")) == NULL) {
    SCC_ERROR("file not found '%s'", filename);
    return false;
  }

  fclose(file);
  return true;
}

/**
 * @brief Verify command-line arguments.
 *
 * Loops through the arguments array and validate them.
 * For source file, make sure it has an .c extension.
 * For flags, make sure only the valid flag are passed in.
 *            valid flags are '--lex', '--parse', '--codegen', and '-S'
 *
 * @param argc number of arguments
 * @param argv array of arguments
 * @return 0 on success, 3 on invalid arguements error
 */
static int validate_args(int argc, char *argv[]) {
  bool has_invalid_flag = false;
  bool has_invalid_c_file = false;

  for (int i = 1; i < argc; i++) {  // ignore argv[0]
    if (argv[i][0] == '-') {
      if (is_valid_flag(argv[i]) == 0) {
        continue;
      } else {
        has_invalid_flag = true;
        SCC_ERROR("invalid flag detected '%s'", argv[i]);
      }
    } else {
      if (is_valid_c_file(argv[i])) {
        continue;
      } else {
        has_invalid_c_file = true;
      }
    }
  }
  if (has_invalid_flag || has_invalid_c_file) {
    return SCC_ERROR_INVALID_ARGS;
  }

  return SCC_SUCCESS;
}

/**
 * @brief Checks what flag was passed in.
 *
 * Set the flag param to the correct enum value.
 *
 * @param flag enum to modify based on the argument passed in.
 * @param arg argument to check
 */
static void check_flag(arg_flag *flag, const char *const arg) {
  if (arg[1] == 'S') {
    // found -S flag
    *flag = SCC_FLAG_S;
  } else if (arg[2] == 'l') {
    // found --lex flag
    *flag = SCC_FLAG_LEX;
  } else if (arg[2] == 'p') {
    // found --parse flag
    *flag = SCC_FLAG_PARSE;
  } else if (arg[2] == 'c') {
    // found --codegen flag
    *flag = SCC_FLAG_CODEGEN;
  }
}

/**
 * @brief Parse command-line arguments.
 *
 * Loop through the argv array, identify the valid flag and
 * modify the flag param.
 *
 * @param flag modify based on the argument falg passed in.
 * @param argc number of arguments
 * @param argv array of arguments
 */
void args_parse(arg_flag *flag, int argc, char *argv[]) {
  if (argc != 2 && argc != 3) {
    print_usage();
    SCC_EXIT(SCC_ERROR_INVALID_NUMBER_OF_ARGS);
  }

  if (argc == 2) {
    if (!is_valid_c_file(argv[1])) {
      // invalid source file passed in
      SCC_ERROR("invalid source file '%s'", argv[1]);
      print_usage();
      SCC_EXIT(SSC_ERROR_NOT_C_FILE);  // terminate if file is not a c file
    }

    // No flags were passed in, so nothing to do.
    *flag = SCC_FLAG_NOT_SET;
    return;
  }

  if (validate_args(argc, argv) != 0) {
    SCC_EXIT(SCC_ERROR_INVALID_ARGS);  // invalid argments, terminate
  }

  // a flag was passed in, set the flag accordingly.
  if (argv[1][0] == '-') {
    // flag was passed in before the source file
    // e.g. ./build/scc --lex source_file.c

    check_flag(flag, argv[1]);
  } else {
    // flag was passed after the source file
    // e.g. ./build/scc source_file.c --lex

    check_flag(flag, argv[2]);
  }
}
