#include "kernel/types.h"
#include "user/user.h"

int main() {
  // Declare two pipes
  // p2c - a parent to a child communication
  // c2p - a child to a parent communication

  // Call the pipe() system call to create p2c and c2p

  // Declare one byte for sending to the child process
  char our_byte = 'P';

  // Fork a new process
  int pid = fork();
  if (pid > 0) {
    // 1. PLACE YOUR CODE HERE TO SEND A BYTE TO THE OTHER PROCESS
    // 5. PLACE YOUR CODE HERE TO RECEIVE THE MODIFIED BYTE
  }
  else if (pid == 0) {
    // 2. PLACE YOUR CODE HERE TO READ A BYTE IN THE PIPE p2c
    // 3. PLACE YOUR CODE HERE TO MODIFY THE BYTE TO LETTER 'R'
    // 4. PLACE YOUR CODE HERE TO SEND THE BYTE BACK OVER c2p PIPE
  }
  exit(0); // Exit parent process
}
