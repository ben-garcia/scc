#include "../include/compiler_driver.h"

static void remove_file_extension(const char *const filename,
                                  const char *buffer) {
  strcpy((char *)buffer, filename);
  strtok((char *)buffer, ".");
}

static void add_file_extension(const char *file, const char *extension) {
  strncat((char *)file, extension, strlen(extension));
}

static int remove_file(const char *const filename) {
  int status_code = remove(filename);
  if (status_code != 0) {
    fprintf(stderr, "printf failed to remove '%s'\n", filename);
    return status_code;
  }

  return 0;
}

static int run_preprocessor(const char *const filename,
                            const char *preprocessed_file) {
  char compiler[10] = "";
  char command[50];  // variable to store the formatted command
  remove_file_extension(filename, preprocessed_file);

#if defined(__APPLE__) && defined(__MACH__)
  strncat(compiler, "clang", 6);  // clang for linux and macOS
#else
  strncat(compiler, "gcc", 4);  // gcc for windows through mingw
#endif
  int bytes_written =
      sprintf(command, "gcc -E -P %s -o %s.i", filename, preprocessed_file);
  if (bytes_written < 0) {
    SCC_PANIC("sprintf failed")
  }

  int status_code = system(command);
  if (status_code != 0) {
    // -1 indicates the child process could not be created or it's status code
    // could not be retrieved.
    // 127 indicates the child process could not run the command
    return status_code;
  }

  return 0;
}

static int run_compiler(const char *const preprocessed_file) {
  char compiler[10] = "";
  char command[100];
#if defined(__APPLE__) && defined(__MACH__)
  strncat(compiler, "clang", 6);  // clang for linux and macOS
#endif
  strncat(compiler, "gcc", 4);  // gcc for windows through mingw

  int bytes_written = sprintf(command, "%s -S %s.i -o %s.s", compiler,
                              preprocessed_file, preprocessed_file);
  if (bytes_written < 0) {
    SCC_PANIC("sprintf failed")
  }

  int status_code = system(command);
  if (status_code != 0) {
    // -1 indicates the child process could not be created or it's status code
    // could not be retrieved.
    // 127 indicates the child process could not run the command
    return status_code;
  }

  add_file_extension(preprocessed_file, ".i");
  remove_file(preprocessed_file);
  remove_file_extension(preprocessed_file, preprocessed_file);

  return 0;
}

static int run_assembler_and_linker(const char *const compiled_file) {
  char compiler[10] = "";
  char command[50];

#if defined(__APPLE__) && defined(__MACH__)
  strncat(compiler, "clang", 6);  // clang for linux and macOS
#else
  strncat(compiler, "gcc", 4);  // gcc for windows through mingw
#endif
  int bytes_written =
      sprintf(command, "%s %s.s -o %s", compiler, compiled_file, compiled_file);
  if (bytes_written < 0) {
    SCC_PANIC("sprintf failed")
  }

  int status_code = system(command);
  if (status_code != 0) {
    // -1 indicates the child process could not be created or it's status code
    // could not be retrieved.
    // 127 indicates the child process could not run the command
    return status_code;
  }

  add_file_extension(compiled_file, ".s");
  remove_file(compiled_file);

  return 0;
}

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
    SCC_PANIC("compiler faiiled");
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
