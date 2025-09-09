#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

/* Print the prompt ">>> " and read a line of characters
   from stdin. */
int getcmd(char *buf, int nbuf) {

  // ##### Place your code here

  return 0;
}

/*
  A recursive function which parses the command
  at *buf and executes it.
*/
__attribute__((noreturn))
void run_command(char *buf, int nbuf, int *pcp) {

  /* Useful data structures and flags. */
  char *arguments[10];
  int numargs = 0;
  /* Flags to mark word start/end */
  int ws = 1;
  int we = 0;

  /* Flags to mark redirection direction */
  int redirection_left = 0;
  int redirection_right = 0;

  /* File names supplied in the command */
  char *file_name_l = 0;
  char *file_name_r = 0;

  int p[2];
  int pipe_cmd = 0;

  /* Flag to mark sequence command */
  int sequence_cmd = 0;

  int i = 0;
  /* Parse the command character by character. */
  for (; i < nbuf; i++) {

    /* Parse the current character and set-up various flags:
       sequence_cmd, redirection, pipe_cmd and similar. */

    /* ##### Place your code here. */

    if (!(redirection_left || redirection_right)) {
      /* No redirection, continue parsing command. */

      // Place your code here.
    } else {
      /* Redirection command. Capture the file names. */

      // ##### Place your code here.
    }
  }

  /*
    Sequence command. Continue this command in a new process.
    Wait for it to complete and execute the command following ';'.
  */
  if (sequence_cmd) {
    sequence_cmd = 0;
    if (fork() != 0) {
      wait(0);
      // ##### Place your code here.
      // Call run_command recursively
    }
  }

  /*
    If this is a redirection command,
    tie the specified files to std in/out.
  */
  if (redirection_left) {
    // ##### Place your code here.
  }
  if (redirection_right) {
    // ##### Place your code here.
  }

  /* Parsing done. Execute the command. */

  /*
    If this command is a CD command, write the arguments to the pcp pipe
    and exit with '2' to tell the parent process about this.
  */
  if (strcmp(arguments[0], "cd") == 0) {
    // ##### Place your code here.
  } else {
    /*
      Pipe command: fork twice. Execute the left hand side directly.
      Call run_command recursion for the right side of the pipe.
    */
    if (pipe_cmd) {
      // ##### Place your code here.
    } else {
      // ##### Place your code here.
      // Simple command; call exec()
    }
  }
  exit(0);
}

int main(void) {

  static char buf[100];

  int pcp[2];
  pipe(pcp);

  /* Read and run input commands. */
  while(getcmd(buf, sizeof(buf)) >= 0){
    if(fork() == 0)
      run_command(buf, 100, pcp);

    /*
      Check if run_command found this is
      a CD command and run it if required.
    */
    int child_status;
    // ##### Place your code here
  }
  exit(0);
}
