#include "solution.h"

void remove_number_from_point(engine_params *params, int x, int y) {
  for (int i = x; i < params->line_size && is_number(params->matrix[y][i]); i++)
    params->matrix[y][i] = '.';
}

int get_num_here(engine_params *params, int x, int y) {
  int left_ptr = x;

  while (left_ptr > 0 && is_number(params->matrix[y][left_ptr - 1]))
    left_ptr--;

  int result = atoi(params->matrix[y] + left_ptr);

  remove_number_from_point(params, left_ptr, y);

  return result;
}

int get_sum_here(engine_params *params, int y, int x) {
  int sum = 0;
  int nb = 0;
  int neighboors_y[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int neighboors_x[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

  for (int i = 0; i < 8; i++) {
    int current_check_y = y + neighboors_y[i];
    int current_check_x = x + neighboors_x[i];

    if (is_in_range(current_check_x, 0, params->line_size) &&
        is_in_range(current_check_y, 0, params->nb_lines) &&
        is_number(params->matrix[current_check_y][current_check_x]))
      sum += get_num_here(params, current_check_x, current_check_y);
  }
  return sum;
}

int get_engine_sum(engine_params *params) {
  int nb = 0;
  int sum = 0;

  for (int y = 0; y < params->nb_lines; y++)
    for (int x = 0; x < params->line_size; x++)
      if (is_symbole(params->matrix[y][x], params->symboles))
        sum += get_sum_here(params, y, x);

  for (int i = 0; i < params->nb_lines; i++)
    printf("%s\n", params->matrix[i]);

  return sum;
}
