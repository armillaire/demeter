#include "skel.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <pwd.h>
#include <limits.h>

static void create_symlink(Sym s);
static char *expand_path(char *c);

int
main(int argc, char **argv) {
  if (argc != 2)
    panic("usage: demeter <file>");

  Sym *symlinks = read_skel(argv[1]);

  for (int i = 0;; i++) {
    create_symlink(symlinks[i]);
    if (symlinks[i].end)
      break;
  }
}

static void
create_symlink(Sym s) {
  char *input = expand_path(s.input);
  char *output = expand_path(s.output);

  symlink(input, output);
  printf("%s -> %s\n", input, output);

  free(input);
  free(output);
}

static char*
expand_path(char *c) {
  char *o = NULL;

  struct passwd *pw = getpwuid(getuid());
  char *home_dir = pw->pw_dir;

  char cwd[PATH_MAX];
  getcwd(cwd, PATH_MAX);  

  if (c[0] == '~') {
    size_t size = (strlen(c) + strlen(home_dir) + 1) * sizeof(char);
    o = (char *)malloc(size);

    if (o == NULL)
      panic("malloc: %s", strerror(errno));

    snprintf(o, size, "%s%s", home_dir, c + 1);
  } else {
    size_t size = (strlen(c) + strlen(cwd) + 2) * sizeof(char);
    o = (char *)malloc(size);

    if (o == NULL)
      panic("malloc: %s", strerror(errno));

    snprintf(o, size, "%s/%s", cwd, c);
  }

  return o;
}
