NAME = minishell

NAME_LIB = minishell.a

SRCS =	src/lexer.c\
		src/struct.c\
		src/libft/ft_strdup.c\
		src/libft/ft_strjoin.c\
		src/libft/ft_strlen.c\
		src/libft/ft_putendl_fd.c\
		src/libft/ft_putstr_fd.c\
		src/libft/get_next_line.c\
		src/main.c\
		src/lets_parser.c

OBJ = $(SRCS:.c=.o)

CFLAGS = #-Wall -Wextra -Werror

all: $(NAME)

$(NAME) : $(OBJ)
	@ar rcs $(NAME_LIB) $(OBJ)
	@gcc $(NAME_LIB) -o $(NAME)
	@echo "\n\033[32m--------- successfully ---------\033[0m"
clean :
	@rm -f $(OBJ) $(NAME)
fclean: clean
	@rm -f $(NAME_LIB)

re : fclean all
