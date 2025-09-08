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
    // get path basename
    while (p < e) {
      if (*p++ == '/') {
        b = p;
      }
    }

    if (strcmp(b, expression) == 0) {
      fprintf(1, "%s\n", path);
    }
    break;
  case T_DIR:
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)) {
      if (de.inum == 0 || strcmp(de.name, ".") == 0 || 
          strcmp(de.name, "..") == 0) { // ??
        continue;
      }
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

