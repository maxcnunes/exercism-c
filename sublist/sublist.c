#include "sublist.h"
#include <math.h>
#include <stdbool.h>
#include <string.h>

comparison_result_t check_lists(int *list_to_compare, int *base_list,
                                size_t list_to_compare_element_count,
                                size_t base_list_element_count) {
  return check_lists_v2(list_to_compare, base_list,
                        list_to_compare_element_count, base_list_element_count);
}

// First solution, built on my own.
comparison_result_t check_lists_v1(int *list_to_compare, int *base_list,
                                   size_t list_to_compare_element_count,
                                   size_t base_list_element_count) {
  if (base_list_element_count == 0 && list_to_compare_element_count == 0) {
    return EQUAL;
  }

  if (base_list_element_count > 0 && list_to_compare_element_count == 0) {
    return SUBLIST;
  }

  if (base_list_element_count == 0 && list_to_compare_element_count > 0) {
    return SUPERLIST;
  }

  size_t li = 0;            // Index of the list_to_compare array
  size_t bi = 0;            // Index of the base_list array
  size_t section_count = 0; // Total matching records in a section.
  int index_section = -1;   // Index where a section
                            // with matching records started from.

  while (bi < base_list_element_count) {
    for (; li < list_to_compare_element_count; li++) {
      if (base_list[bi] == list_to_compare[li]) {
        if (section_count == 0) {
          // Keep track where the section has started from,
          // so in case the section doesnt' match the list completely,
          // the iteration can start back over again from
          // the next item after this point.
          index_section = bi;
        }

        section_count++;
        break;
      }

      section_count = 0;
    }

    if (section_count == list_to_compare_element_count ||
        section_count == base_list_element_count) {
      break;
    }

    // Item didn't match.
    if (section_count == 0) {
      if (index_section != -1) {
        // There was a matching section, but the last item didn't
        // match. Discard the section and start over the base list
        // iteration from the next item after the first section item.
        bi = index_section + 1;
        index_section = -1;
      } else {
        // There was no section, just move direct to the next base list
        // item.
        bi++;
      }

      li = 0;
      continue;
    }

    // Matching item, move forward to next item.
    li++;
    bi++;
  }

  if (section_count != list_to_compare_element_count &&
      section_count != base_list_element_count) {
    return UNEQUAL;
  }

  if (section_count == list_to_compare_element_count &&
      base_list_element_count > list_to_compare_element_count) {
    return SUBLIST;
  }

  if (section_count == base_list_element_count &&
      list_to_compare_element_count > base_list_element_count) {
    return SUPERLIST;
  }

  return EQUAL;
}

// Second solution, based on
// https://exercism.org/tracks/c/exercises/sublist/solutions/shikov
// It uses memcpm to compare n bytes of memory.
comparison_result_t check_lists_v2(int *list_to_compare, int *base_list,
                                   size_t list_to_compare_element_count,
                                   size_t base_list_element_count) {
  bool sublist = list_to_compare_element_count <= base_list_element_count;

  const int *smaller_list = sublist ? list_to_compare : base_list;
  const int *greater_list = sublist ? base_list : list_to_compare;

  size_t min_count =
      (size_t)fmin(list_to_compare_element_count, base_list_element_count);
  size_t max_count =
      (size_t)fmax(list_to_compare_element_count, base_list_element_count);

  for (size_t i = 0; i <= max_count - min_count; i++) {
    const int compare_size = min_count * sizeof(int);

    if (memcmp(smaller_list, &greater_list[i], compare_size) == 0) {
      if (min_count == max_count) {
        return EQUAL;
      }

      if (sublist) {
        return SUBLIST;
      }

      return SUPERLIST;
    }
  }

  return UNEQUAL;
}
