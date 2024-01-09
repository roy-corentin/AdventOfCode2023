#include "solution.h"

engine_params *create_engine_params(char **matrix, int nb_lines, int line_size,
                                    linked_list *symboles) {
  engine_params *params = malloc(sizeof(engine_params));
  params->matrix = matrix;
  params->nb_lines = nb_lines;
  params->line_size = line_size;
  params->symboles = symboles;

  return params;
}
