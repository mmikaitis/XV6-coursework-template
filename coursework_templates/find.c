#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"
#include "user/user.h"

void usage() {
  fprintf(1, "usage: find path expression\n");
}

void find(char *path, char *expression) {
  char buf[512], *p, *e, *b;
  int fd;
  struct stat st;
  struct dirent de;

  if ((fd = open(path, O_RDONLY)) < 0) {
    fprintf(2, "find: cannot open %s\n", path);
    exit(1);
  }

  if (fstat(fd, &st) < 0) {
    fprintf(2, "find: cannot stat %s\n", path);
    exit(1);
  }

  switch (st.type) {
  case T_FILE:
    p = path;
    e = p + strlen(path);
    b = p;
    // Move pointer p character by character until it is
    // equivalent to e (end of the path). When '/' is met,
    // save the pointer to b, so that at the end b contains
    // the pointer to the last '/' in the path.
    while (p < e) {
      // PLACE YOUR CODE HERE
    }

    // If the string at pointer b is equal to the string
    // that we are searching for, print out the path.

    // PLACE YOUR CODE HERE
    break;
  case T_DIR:
    strcpy(buf, path);
    p = buf + strlen(buf);
    // Add '/' at the end of this path.
    // PLACE YOUR CODE HERE

    // Read each item in the directory, add the name of the item
    // to the end of the path in buf, and run find() recursively.
    while(read(fd, &de, sizeof(de)) == sizeof(de)) {
      // Skip if no items are found, of if '.' or '..' found
      // PLACE YOUR CODE HERE

      // Move the name of the item to the end of the path in buff
      // and call find() with the new path.
      memmove(p, de.name, DIRSIZ);
      // Terminate the extended string.
      p[DIRSIZ] = '\0';
      find(buf, expression);
    }
    break;
  }
  close(fd);
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    usage();
    exit(1);
  }

  find(argv[1], argv[2]);
  exit(0);
}
