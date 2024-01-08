#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_file(char **av) {
  long size;
  char *buffer;
  char *file_name;
  FILE *file;

  file_name = av[1];
  file = fopen(file_name, "r");

  if (file == NULL) {
    printf("Error: File not found\n");
    exit(1);
  }

  fseek(file, 0, SEEK_END);
  size = ftell(file);
  fseek(file, 0, SEEK_SET);

  buffer = malloc(size + 1);
  fread(buffer, 1, size, file);
  fclose(file);

  size[buffer] = 0;

  return buffer;
}

int get_line_size(char *buffer) {
  int result = 0;
  for (int i = 0; buffer[i] != '\n'; i++)
    result++;
  return result;
}

int get_nb_lines(char *buffer) {
  int result = 0;
  for (int i = 0; buffer[i] != '\0'; i++) {
    if (buffer[i] == '\n') {
      result++;
    }
  }
  return result;
}

char **malloc_matrix(char *buffer) {
  int i = 0;
  int j = 0;
  int line_size = get_line_size(buffer);
  int nb_lines = get_nb_lines(buffer);
  char **matrix = malloc(sizeof(char *) * nb_lines);

  while (buffer[i] != '\0') {
    if (buffer[i] == '\n') {
      matrix[j] = malloc(sizeof(char) * line_size + 1);
      j++;
    }
    i++;
  }

  return matrix;
}

int fill_matrix(char **matrix, char *buffer) {
  int i = 0;
  int j = 0;
  int k = 0;
  int line_size = get_line_size(buffer);
  int nb_lines = get_nb_lines(buffer);

  while (buffer[i] != '\0') {
    if (buffer[i] == '\n') {
      matrix[j][k] = '\0';
      j++;
      k = 0;
    } else {
      matrix[j][k] = buffer[i];
      k++;
    }
    i++;
  }

  return nb_lines;
}

int get_num_here(char **matrix, int i, int j) {
  int left_ptr = j;
  while (left_ptr > 0 && matrix[i][left_ptr] >= 48 && matrix[i][left_ptr] <= 57)
    left_ptr--;
  printf("left_ptr: %d\n", left_ptr);
  return atoi(&matrix[i][left_ptr]);
}

int get_sum_here(char **matrix, int i, int j) {
  int sum = 0;
  int nb = 0;
  int line_size = strlen(matrix[0]);

  if (i > 0 && j > 0 && matrix[i - 1][j - 1] >= 48 &&
      matrix[i - 1][j - 1] <= 57) {
    sum += get_num_here(matrix, i - 1, j - 1);
  }
  if (i > 0 && matrix[i - 1][j] >= 48 && matrix[i - 1][j] <= 57) {
    sum += get_num_here(matrix, i - 1, j);
  }
  if (i > 0 && j < line_size - 1 && matrix[i - 1][j + 1] >= 48 &&
      matrix[i - 1][j + 1] <= 57) {
    sum += get_num_here(matrix, i - 1, j + 1);
  }
  if (j > 0 && matrix[i][j - 1] >= 48 && matrix[i][j - 1] <= 57) {
    sum += get_num_here(matrix, i, j - 1);
  }
  if (j < line_size - 1 && matrix[i][j + 1] >= 48 && matrix[i][j + 1] <= 57) {
    sum += get_num_here(matrix, i, j + 1);
  }
  if (i < line_size - 1 && j > 0 && matrix[i + 1][j - 1] >= 48 &&
      matrix[i + 1][j - 1] <= 57) {
    sum += get_num_here(matrix, i + 1, j - 1);
  }
  if (i < line_size - 1 && matrix[i + 1][j] >= 48 && matrix[i + 1][j] <= 57) {
    sum += get_num_here(matrix, i + 1, j);
  }
  return sum;
}

int get_engine_sum(char **matrix, int nb_lines) {
  int line_size = strlen(matrix[0]);
  int nb = 0;
  int sum = 0;

  for (int i = 0; i < nb_lines; i++) {
    for (int j = 0; j < line_size; j++) {
      if (matrix[i][j] >= 33 && matrix[i][j] <= 45) {
        nb = get_sum_here(matrix, i, j);
        printf("Symbole !!: %c sum next to %d\n", matrix[i][j], nb);
        sum += nb;
      }
    }
  }
  return sum;
}

int main(int ac, char **av) {
  long size;
  char *buffer;
  char *file_name;
  FILE *file;

  buffer = read_file(av);
  char **matrix = malloc_matrix(buffer);

  int nb_lines_filled = fill_matrix(matrix, buffer);

  int sum = get_engine_sum(matrix, nb_lines_filled);

  printf("Sum: %d\n", sum);

  for (int i = 0; i < nb_lines_filled; i++)
    free(matrix[i]);
  free(matrix);
  free(buffer);
  return 0;
}
