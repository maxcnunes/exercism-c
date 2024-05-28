#include "reverse_string.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *reverse(const char *value) { return reverse_v1(value); }

// First version, built on my own
char *reverse_v1(const char *value) {
  int len = strlen(value);
  char *reversed = calloc(len, sizeof(char));

  int li = 0;
  for (int ri = len - 1; ri >= 0; ri--) {
    reversed[li] = value[ri];
    li++;
  }

  return reversed;
}

// Second version based on
// https://exercism.org/tracks/c/exercises/reverse-string/solutions/bobahop
// It works based on pointers instead of values.
// It uses pointer arithmetic to manipulate the content of value and reversed
// variables.
char *reverse_v2(const char *value) {
  if (!value)
    return NULL;

  int len = strlen(value);
  char *reversed = calloc(len + 1, sizeof(char));

  for (reversed += len; *value; value++) {
    *(--reversed) = *value;
  }

  return reversed;
}
