/**
 * @file compiler_driver.c
 * @brief Compile C source code.
 *
 * Generates an execuatable file by invoking the following:
 *   1. Preprocessor (gcc on linux and windows, clang on macOS)
 *   2. Compiler (scc compiler)
 *   3. Assembler (gcc on linux and windows, clang on macOS)
 *   4. Linker (gcc on linux and windows, clang on macOS)
 *
 * @author ben
 * @date 12/29/2025
 */

#include "include/compiler_driver.h"

#include "include/macros.h"

/**
 * @brief Remove a file's extension.
 *
 * Modifies the filename by removing the file extension and putting the result
 * in the buffer param.
 *
 * @param filename file whose extension is to be removed.
 * @param buffer buffer that holds the the results of the function.
 *
 * @note This only works for files with a single extension. e.g. main.c
 */
static void remove_file_extension(const char *const filename,
                                  const char *buffer) {
  strcpy((char *)buffer, filename);
  strtok((char *)buffer, ".");
}

/** @brief Add an extension to a file.
 *
 * Modifies the file by adding the file extension.
 *
 * @param filename file that is to be modified.
 * @param extension file extension to add.
 */
static void add_file_extension(const char *file, const char *extension) {
  strncat((char *)file, extension, strlen(extension));
}

/**
 * @brief Deletes a file from the OS.
 *
 * Remove the genarated files from the compilation process.
 *
 * @param filename file whose extension is to be removed.
 * @return 0 on success, positive integer otherwise
 */
static int remove_file(const char *const filename) {
  int status_code = remove(filename);
  if (status_code != 0) {
    SCC_ERROR("failed to remove '%s'\n", filename);
    return status_code;
  }

  return 0;
}

/**
 * @brief Execute the C compiler to generate the correct file.
 *
 * Generates a file after each succesfull stage in the compilation process.
 * It generates a preprocessed file(<filename>.i) after preprocessor has
 * executed. It generates the assembly(<file>.s) after compilation has executed.
 * It generates a executable binary after assembler/linker have executed.
 *
 * @param filename file whose extension is to be removed.
 * @param buffer buffer that holds the the results of the function.
 */
static int run_c_compiler(const char *const flags) {
  char compiler[10] = "";
  char command[100];  // variable to store the formatted command
#if defined(__APPLE__) && defined(__MACH__)
  strncat(compiler, "clang", 6);  // clang for linux and macOS
#else
  strncat(compiler, "gcc", 4);  // gcc for windows through mingw
#endif
  int bytes_written = sprintf(command, "%s %s", compiler, flags);
  if (bytes_written < 0) {
    SCC_PANIC("sprintf failed");
  }

  int status_code = system(command);
  if (status_code != 0) {
    // -1 indicates the child process could not be created or it's status code
    // could not be retrieved.
    // 127 indicates the child process could not run the command
  }

  return status_code;
}

/**
 * @brief Executes the C preprocessor.
 *
 * Generate the preprocessed file with a .i extension.
 *
 * @param filename file whose extension is to be removed.
 * @param preprocessed_file file modified with the .i extension.
 * @return 0 on success, positive integer otherwise
 */
static int run_preprocessor(const char *const filename,
                            const char *preprocessed_file) {
  remove_file_extension(filename, preprocessed_file);
  char buffer[100] = "";
  sprintf(buffer, "-E -P %s -o %s.i", filename, preprocessed_file);
  return run_c_compiler(buffer);
}

/**
 * @brief Executes the C preprocessor.
 *
 * Generate the assmebly file with a .s extension.
 *
 * @param preprocessed_file file from the preprocessor stage.
 * @return 0 on success, positive integer otherwise .
 *
 * @note currently using gcc/clang, but will replace with scc(binary for this this project).
 */
static int run_compiler(const char *const preprocessed_file) {
  char buffer[100] = "";
  sprintf(buffer, "-S %s.i -o %s.s", preprocessed_file, preprocessed_file);
  run_c_compiler(buffer);
  add_file_extension(preprocessed_file, ".i");
  remove_file(preprocessed_file);
  remove_file_extension(preprocessed_file, preprocessed_file);

  return 0;
}

/**
 * @brief Executes the C aseembler/linker.
 *
 * Generate the execuatble binary of the C source code.
 *
 * @param compiled_file file from the compilation stage.
 * @return 0 on success, positive integer otherwise.
 */
static int run_assembler_and_linker(const char *const compiled_file) {
  char buffer[100] = "";
  sprintf(buffer, "%s.s -o %s", compiled_file, compiled_file);
  run_c_compiler(buffer);
  add_file_extension(compiled_file, ".s");
  remove_file(compiled_file);

  return 0;
}

/**
 * @brief Wrapper for the C compilation process.
 *
 * Call the necessary functions to go from a source code file an executable.
 *
 * @param filename file with C source code.
 * @return 0 on success, positive integer otherwise
 */
int compiler_driver_run(const char *const filename) {
#if defined(__linux__) || defined(__WIN32__) || \
    (defined(__APPLE__) && defined(__MACH__))
  // used to keep track of created files from previous pass
  char buffer[1000] = {0};
  int exit_code = run_preprocessor(filename, buffer);
  if (exit_code != 0) {
    SCC_PANIC("preprocessor failed");
  }

  exit_code = run_compiler(buffer);
  if (exit_code != 0) {
    SCC_PANIC("compiler failed");
  }

  exit_code = run_assembler_and_linker(buffer);
  if (exit_code != 0) {
    SCC_PANIC("assembler/linker failed");
  }
#else
  SCC_PANIC("Your OS is currently not supported");
#endif

  return 0;
}
