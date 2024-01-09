SRC = solution.c \
      tool.c \
      engine.c \
      engine_params.c

NAME = solution

OBJ	= $(SRC:.c=.o)

FLAGS = -W -Wall -Werror -g -Iinclude

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)
	rm -rf *.gcno
	rm -rf *.gcda

fclean: clean
	rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re $(NAME)
