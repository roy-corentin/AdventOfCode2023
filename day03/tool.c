#include "solution.h"

int is_symbole(char target, linked_list *symboles) {
  linked_list *tmp = symboles;

  while (tmp) {
    if (tmp->value == target)
      return 1;
    tmp = tmp->next;
  }
  return 0;
}

int is_number(char c) {
  if (c >= 48 && c <= 57)
    return 1;
  return 0;
}
