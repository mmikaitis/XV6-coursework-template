#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

void execute_line(char *line, char *args[], int skip) {

  int f = fork();
  if (f < 0) {
    fprintf(2, "xargs: fork failed\n");
    exit(1);
  } else if(f == 0) { // child
    int ws = 1;
    char **a, *l;

    // Args contains an array of pointers to the strings
    // given as input arguments to args (the command).
    // We go through a line of standard input and append to
    // args pointers to separate words in the line.
    a = &args[skip];
    l = line;
    while (*l != '\0') {
      // PLACE YOUR CODE HERE
    }

    // Call exec() by passing the modified
    // args array to it.
    // PLACE YOUR CODE HERE
  } else { // parent
    wait((int *) 0);
  }
}

int main(int argc, char *argv[]) {
  char *args[MAXARG] = { 0 };
  char buf[512], *b;
  b = buf;

  for (int i = 1; i < argc; i++) {
    args[i - 1] = argv[i];
  }

  // Read each line of stdin into the buffer and execute
  // the command given as args. This routine replaces
  // newlines with nulls to terminate the string.
  while (read(0, b, 1) > 0) {
    if (*b == '\n') {
      // Terminate the string with '\0' and call
      // execute_line.
      // PLACE YOUR CODE HERE
      b = buf;
    }
    b++;
  }
  exit(0);
}
