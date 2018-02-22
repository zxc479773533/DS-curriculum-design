/*
 * PY execute
 * Developed by Pan Yue
 * zxc479773533@gmail.com
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../avltree.h"
#include "../hashtable.h"

/* Function prototypes */
void print_help(void);

int builtin_cmd(char **argv) {
  /* Not a built-in command */
  if (!strcmp(argv[0], "quit")) {
    printf("[INFO] User-exit. Terminated!\n");
    exit(0);
  }
  if (!strcmp(argv[0], "help()")) {
    print_help();
    return 1;
  }
  if (!strcmp(argv[0], "show")) {
    return 1;
  }
  return 0;
}

void py_execute(char *func , int argc, char **argv) {
  
}