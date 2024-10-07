#include "skel.h"

#include <stdio.h>
#include <unistd.h>

int
main(int argc, char **argv) {
  if (argc != 2)
    panic("usage: demeter <file>");

  Sym *symlinks = read_skel(argv[1]);

  for (int i = 0;; i++) {
    symlink(symlinks[i].input, symlinks[i].output);

    printf("%s -> %s\n", symlinks[i].input, symlinks[i].output);
    
    if (symlinks[i].end)
      break;
  }
}
