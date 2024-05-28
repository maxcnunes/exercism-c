#include "reverse_string.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *reverse(const char *value) { return reverse_v1(value); }

// First version, built on my own
char *reverse_v1(const char *value) {
  int len = strlen(value);

  // Allocates memory for len characters
  // plus one additional character for the null terminator.
  char *reversed = calloc(len + 1, sizeof(char));

  for (int i = len - 1; i >= 0; i--) {
    reversed[len - i - 1] = value[i];
  }

  reversed[len] = '\0'; // string null terminator

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

  // Allocates memory for len characters
  // plus one additional character for the null terminator.
  char *reversed = calloc(len + 1, sizeof(char));

  for (reversed += len; *value; value++) {
    *(--reversed) = *value;
  }

  reversed[len] = '\0'; // string null terminator

  return reversed;
}
