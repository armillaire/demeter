#ifndef UTIL_H_
#define UTIL_H_

#define bool int
#define TRUE 1
#define FALSE 0

#include <stdlib.h>

#define panic(msg, ...)                       \
  do {                                        \
    fprintf(stderr, msg "\n", ##__VA_ARGS__); \
    exit(1);                                  \
  } while (0)

typedef struct {
  size_t size;
  char *raw;
} str;

#endif /* UTIL_H_ */
