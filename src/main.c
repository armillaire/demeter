#include "skel.h"

#include <stdio.h>
#include <unistd.h>

int
main(int argc, char **argv) {
  if (argc != 2)
    panic("usage: demeter <file>");

  Sym *symlinks = read_skel(argv[1]);

  for (int i = 0;; i++) {
    int res = symlink(symlinks[i].input, symlinks[i].output);

    if (res != 0) {
      perror("symlink");
      exit(1);
    }
    
    printf("%s -> %s\n", symlinks[i].input, symlinks[i].output);
    
    if (symlinks[i].end)
      break;
  }
}
