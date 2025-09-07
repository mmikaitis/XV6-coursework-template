#include <stdio.h>

int main(void) {
  // Define an array of 100 characters.
  char buffer[100];
  // Define a pointer to a chracter and point it
  // to the first character in the buffer.
  char* current_char = buffer;
  // Define an array of 20 points to characters and set
  // them to NULL.
  char* words[20] = {NULL};
  // Define some counters and flags.
  int i = 0;
  int prev_char_not_ordinary = 1;

  // Read a new character from stdin until EOF is detected.
  while ((*current_char = getchar()) != EOF) {
    // If the current character is a space, a new line,
    // or a tab, coming after an ordinary character
    // terminate the string by placing '\0' in the current
    // location of buffer.

    // PLACE YOUR CODE HERE

    // If the current character is an ordinary character
    // after a special character save the pointer to it in
    // the words[] array.
    else if (prev_char_not_ordinary) {
      // PLACE YOUR CODE HERE
    }
    // Move the pointer in buff by one place.
    // PLACE YOUR CODE HERE
  }
  *current_char = '\0';
  printf("\n");

  // Print out all the detected words in the stdin.
  for (int i = 0; i < 20; i++)
    if (words[i] != NULL)
      printf("%s \n", words[i]);
  return 0;
}

