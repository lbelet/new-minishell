CC = gcc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g

NAME = minishell

SRC = minishell.c\
		get_path.c\
		split_modif.c\
		signals.c\
		builtins.c\
		parsing.c\
		one_cmd.c\
		multi_cmds.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	make -C libft
#	$(CC) $(CFLAGS) $(OBJ) libft/libft.a -lreadline -o $(NAME)
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a -I$(HOME)/.brew/Cellar/readline/8.1.2/include -lreadline -L$(HOME)/.brew/Cellar/readline/8.1.2/lib -o $(NAME)


clean:
	make clean -C libft
	rm -f $(OBJ)

fclean : clean
	make fclean -C libft
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
