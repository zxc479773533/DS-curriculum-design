/*
 * PY prompt
 * Developed by Pan Yue
 * zxc479773533@gmail.com
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "py_exec.c"

/* Constants */
#define MAXLINE 1024
#define MAXARGS 128

/* Global variables */
char prompt[] = "py_prompt > ";
char theme[] = "Here to control a friend and followers management system";

/* Founction prototypes */
void eval(char *cmdline);
int parseline(const char *cmdline, char **argv);

/* Print usage messages */
void print_usage(void) {
  printf("Usage: py_manager\n");
  printf("Options:\n");
  printf("\t-h: print this massges\n");
  printf("\t-p: hide the prompt\n");
  printf("\tdefault: start shell\n");
}

int Start_Shell(int argc, char **argv) {
  char ch;
  /* The command line */
  char cmdline[MAXLINE];
  /* Decide whether print a prompt, default yes*/
  int emit_prompt = 1;

  /* Parse the command line */
  while ((ch = getopt(argc, argv, "hp")) != EOF) {
    switch(ch) {
    case 'h':
      print_usage();
      exit(0);
    case 'p':
      emit_prompt = 0;
      break;
    default:
      print_usage();
      exit(1);
    }
  }

  /* Print informations */
  printf("[INFO] Wherecome to Pan Yue's interactive shell!\n");
  printf("[INFO] %s\n", theme);
  printf("[INFO] Try help to see how to use this Controller\n");

  /* Excute the shell's read/eval loop */
  while (1) {

    /* Print prompt */
    if (emit_prompt) {
      printf("%s", prompt);
      fflush(stdout);
    }
    if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin)) {
      printf("fgets error\n");
      exit(1);
    }
    if (feof(stdin)) {
      printf("[EXIT] Parser reached end-of-file. Terminated!\n");
      fflush(stdout);
      exit(0);
    }

    /* Evaluate the command line */
    eval(cmdline);
    fflush(stdout);
  }

  return 0;
}

/*
 * eval - Evaluate the command line that the user has just typed in
 * 
 * If the user has requseted a built-in command, then excute it immediately.
 */
void eval(char *cmdline) {
  char *argv[MAXARGS];
  char buf[MAXLINE];
  int argc;

  /* Parse command */
  strcpy(buf, cmdline);
  argc = parseline(buf, argv);

  if (argv[0] == NULL)
    return;
  
  if (!builtin_cmd(argv)) {
    if (!py_execute(argv[0], argc, argv))
      printf("[INFO] pysh: command not found.\n");
    else
      printf("[INFO] Operation finished.\n\n");
  }
}

/*
 * parseline - Parse the command line and build the argv array.
 */
int parseline(const char *cmdline, char **argv) {
  /* Holds local copy of command line */
  static char array[MAXLINE];
  char *buf = array;
  char *delim;
  int argc;
  
  strcpy(buf, cmdline);
  buf[strlen(buf) - 1] = ' ';
  /* Ignore leading spaces */
  while (*buf && (*buf == ' '))
    buf++;

  /* Build the argv list */
  argc = 0;
  if (*buf == '\'') {
    buf++;
    delim = strchr(buf, '\'');
  }
  else {
    delim = strchr(buf, ' ');
  }

  while(delim) {
    argv[argc++] = buf;
    *delim = '\0';
    buf = delim + 1;
    while (*buf && (*buf == ' '))
      buf++;
    
    if (*buf == '\'') {
      buf++;
      delim = strchr(buf, '\'');
    }
    else {
      delim = strchr(buf, ' ');
    }
  }
  argv[argc] = NULL;
  return argc;
}