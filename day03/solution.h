#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linked_list_s {
  char value;
  struct linked_list_s *next;
} linked_list;

typedef struct engine_params_s {
  char **matrix;
  int nb_lines;
  int line_size;
  linked_list *symboles;
} engine_params;

int get_engine_sum(engine_params *params);
int is_symbole(char, linked_list *);
int is_number(char c);

engine_params *create_engine_params(char **matrix, int nb_lines, int line_size,
                                    linked_list *symboles);

#endif // SOLUTION_H_
