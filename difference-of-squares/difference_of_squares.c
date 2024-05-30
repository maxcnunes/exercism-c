#include "difference_of_squares.h"

unsigned int sum_of_squares(unsigned int number) {
  return sum_of_squares_v2(number);
}

unsigned int square_of_sum(unsigned int number) {
  return square_of_sum_v2(number);
}

unsigned int difference_of_squares(unsigned int number) {
  return difference_of_squares_v2(number);
}

// v1 functions, the first implementation built on my own.
// It uses loops to compute square sum, which has a time complexity of O(n).
unsigned int sum_of_squares_v1(unsigned int number) {
  unsigned int sum = 0;

  for (unsigned int i = 1; i <= number; i++)
    sum += (i * i);

  return sum;
}

unsigned int square_of_sum_v1(unsigned int number) {
  unsigned int sum = 0;

  for (unsigned int i = 1; i <= number; i++)
    sum += i;

  return sum * sum;
}

// difference_of_squares repeat the implementation for both
// sum_of_squares and square_of_sum functions so it can compute
// the sum with a single loop processing.
unsigned int difference_of_squares_v1(unsigned int number) {
  unsigned int result_sum_of_squares = 0;
  unsigned int result_square_of_sum = 0;

  for (unsigned int i = 1; i <= number; i++) {
    result_sum_of_squares += (i * i);
    result_square_of_sum += i;
  }

  return (result_square_of_sum * result_square_of_sum) - result_sum_of_squares;
}

// v2 functions, the second implementation using math formules, which gives
// a time complexity of O(1).
// Forumles based on
// https://learnersbucket.com/examples/algorithms/difference-between-square-of-sum-of-numbers-and-sum-of-square-of-numbers/
unsigned int sum_of_squares_v2(unsigned int number) {
  return (number * (number + 1) * ((number * 2) + 1)) / 6;
}

unsigned int square_of_sum_v2(unsigned int number) {
  unsigned int sum = (number * (number + 1)) / 2;
  return sum * sum;
}

// difference_of_squares repeat the implementation for both
// sum_of_squares and square_of_sum functions so it can compute
// the sum with a single loop processing.
unsigned int difference_of_squares_v2(unsigned int number) {
  return square_of_sum_v2(number) - sum_of_squares(number);
}
