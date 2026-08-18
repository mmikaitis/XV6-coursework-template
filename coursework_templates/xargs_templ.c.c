#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

/* This method takes a line of standard input, finds all
   the strings inside it, and puts the pointers to the starting
   characters of each string into the args[] array, starting
   at the element with an index 'skip'.
*/
void execute_line(char *line, char *args[], int skip) {

  int f = fork();
  if (f < 0) {
    fprintf(2, "xargs: fork failed\n");
    exit(1);
  } else if(f == 0) { // child
    // If this flag is '1' it says that the next ordinary (non-space)
    // chatacter we meet will constitute a start of a new word in the 'line'.
    // Set ws=0 when the pointer to the first character in a string is saved
    // to args. Next time you meet a space in the 'line', if ws=0, terminate
    // the string and set ws=1, otherwise, skip the space.
    int ws = 1;
    // Pointer 'a' points to a current empty argument in args
    // whilst pointer 'l' points to a current character in the 'line'.
    char **a, *l;

    // Args contains an array of pointers to the strings
    // given as input arguments to xargs (the command).
    // We go through a line of standard input and append to
    // args pointers to separate words in the line.
    a = &args[skip];
    l = line;
    // Go through every character in the line and terminate each string
    // with a '\0' and also save points to starts of each string into args[].
    // Move the pointer 'a' accordingly to point to a location in args[] that
    // follows the last argument placed in args[].
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
