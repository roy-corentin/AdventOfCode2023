#include "solution.h"
#include <stdio.h>

void free_linked_list(linked_list *head) {
  linked_list *tmp = head;
  linked_list *next = NULL;

  while (tmp) {
    next = tmp->next;
    free(tmp);
    tmp = next;
  }
}

void add_node(char value, linked_list **head) {
  linked_list *node = malloc(sizeof(linked_list));
  linked_list *tmp = *head;

  if (!node)
    return;

  node->value = value;
  node->next = NULL;

  if (!tmp) {
    *head = node;
    return;
  }

  while (tmp->next) {
    if (tmp->value == value)
      return;
    tmp = tmp->next;
  }

  node->next = tmp->next;
  tmp->next = node;
}

linked_list *get_symboles(char *buffer) {
  linked_list *head = NULL;

  for (int i = 0; i < strlen(buffer); i++) {
    if (buffer[i] != '.' && buffer[i] != '\n' && !is_number(buffer[i])) {

      printf("value: %c\n", buffer[i]);
      add_node(buffer[i], &head);
    }
  }

  return head;
}

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

int main(int ac, char **av) {
  char *buffer = read_file(av);
  char **matrix = malloc_matrix(buffer);
  int nb_lines_filled = fill_matrix(matrix, buffer);
  linked_list *symboles = get_symboles(buffer);
  engine_params *params = create_engine_params(matrix, nb_lines_filled,
                                               strlen(matrix[0]), symboles);

  int sum = get_engine_sum(params);
  printf("Sum: %d\n", sum);

  free(params);
  for (int i = 0; i < nb_lines_filled; i++)
    free(matrix[i]);
  free(matrix);
  free_linked_list(symboles);
  free(buffer);
  return 0;
}
