#include "skel.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static str read_file(const char *filename);

Sym*
read_skel(const char *filename) {
  const str contents = read_file(filename);

  Sym *symlinks = (Sym *)malloc(sizeof(Sym));

  symlinks[0] = (Sym){0};

  int start_index = 0;
  int sym_index = 0;
  for (int i = 0; i <= contents.size; i++) {
    Sym *sym = &symlinks[sym_index];
    char c = contents.raw[i];

    /* TODO clean this up */
    if (c == ':') {
      sym->input = (char *)malloc(contents.size);
      
      strncpy(sym->input, contents.raw + start_index, i - start_index);
      sym->input[i - start_index] = '\0';
      
      sym->input = (char *)realloc(sym->input, i - start_index);
      start_index = i + 1;
    } else if (c == '\n' || c == '\0') {
      sym->output = (char *)malloc(contents.size);
      
      strncpy(sym->output, contents.raw + start_index, i - start_index);
      sym->output[i - start_index] = '\0';

      sym->output = (char *)realloc(sym->output, i - start_index);

      if (strlen(sym->input) != 0 && strlen(sym->output) != 0) {
        sym_index += 1;
        symlinks = (Sym *)realloc(symlinks, (sym_index + 1) * sizeof(Sym));
        
        symlinks[sym_index] = (Sym){0};
      }
    }
  }

  symlinks[sym_index - 1].end = TRUE;

  return symlinks;
}

void
free_sym(Sym *symlinks) {
  /* this could be wrong, but iirc just freeing symlinks wouldn't free the
     individual strings inside of the array */
  for (int i = 0;; i++) {
    free(symlinks[i].input);
    free(symlinks[i].output);

    if (symlinks[i].end)
      break;
  }

  free(symlinks);
}

static str
read_file(const char *filename) {
  FILE *file_stream = {0};

  if ((file_stream = fopen(filename, "r")) == NULL)
    panic("cannot open file \"%s\"", filename);

  /* moving the pointer to the end to get the filesize */
  fseek(file_stream, 0, SEEK_END);
  size_t file_size = (size_t)ftell(file_stream);

  /* moving the file pointer back to the start */
  rewind(file_stream);

  str file_contents = {0};

  file_contents.size = file_size;
  file_contents.raw = (char *)malloc(file_size + 1);

  if (!file_contents.raw)
    panic("failed to allocate memory!");

  fread(file_contents.raw, 1, file_size, file_stream);
  file_contents.raw[file_size] = '\0';

  fclose(file_stream);

  return file_contents;
}

static Sym
create_sym(const size_t in, const size_t out) {
  Sym new = {0};
  
  return new;
}
