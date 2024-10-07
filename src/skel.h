#ifndef SKEL_H_
#define SKEL_H_

#include "util.h"

typedef struct {
  char *input;
  char *output;
  bool end; /* indicates if this is the last symlink */
            /* used for actually looping through the symlinks */
} Sym;

Sym *read_skel(const char *filename);
void free_sym(Sym *symlinks);

#endif /* SKEL_H_ */
