#include "phone_number.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *phone_number_clean(const char *input) {
  return phone_number_clean_v2(input);
}

// Second version; improved implementation based on
// https://exercism.org/tracks/c/exercises/phone-number/solutions/shikov.
// Less allocated variables, use calloc instead of malloc, no char to int cast,
// use strcpy to zero-out output for invalid data.
char *phone_number_clean_v2(const char *input) {
  const int phone_number_size = 10;
  const int len = strlen(input);

  char *output = calloc(phone_number_size, sizeof(char));
  int output_size = 0;
  char c;

  for (int i = 0; i < len; i++) {
    c = input[i];

    if (!isdigit(c)) {
      continue;
    }

    // Country code, filter it out of the output
    if (output_size == 0 && c == '1') {
      continue;
    }

    // The first and forth digits can only be a 2-9 number.
    if ((output_size == 0 || output_size == 3) && (c == '0' || c == '1')) {
      break;
    }

    if (output_size > phone_number_size - 1) {
      // Let it grown beyond the limit, so we know is is invalid later
      output_size += 1;
      break;
    }

    output[output_size] = c;
    output_size += 1;
  }

  if (output_size != phone_number_size) {
    // Zero-out all the current output data
    strcpy(output, "0000000000");
  }

  return output;
}

// First version; built on my own.
char *phone_number_clean_v1(const char *input) {
  const int phone_number_size = 10;
  const int len = strlen(input);

  char *output = (char *)malloc(sizeof(char) * phone_number_size);
  if (output == NULL) {
    return NULL;
  }

  int output_size = 0;
  bool is_valid = true;

  for (int i = 0; i < len; i++) {
    char c = input[i];

    if (!isdigit(c)) {
      continue;
    }

    // Country code, filter it out of the output
    if (output_size == 0 && c == '1') {
      continue;
    }

    // The first and forth digits can only be a 2-9 number.
    if (output_size == 0 || output_size == 3) {
      int n = c - '0'; // convert char to int
      if (n < 2) {
        is_valid = false;
        break;
      }
    }

    if (output_size > phone_number_size - 1) {
      is_valid = false;
      break;
    }

    output[output_size] = c;
    output_size += 1;
  }

  if (output_size != phone_number_size) {
    is_valid = false;
  }

  if (!is_valid) {
    // Zero-out all the current output data
    for (int i = 0; i < phone_number_size; i++) {
      output[i] = '0';
    }
  }

  output[phone_number_size] = '\0'; // mark the end of the string

  return output;
}
