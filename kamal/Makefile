NAME = minishell

NAME_LIB = minishell.a

SRCS =	lexer.c\
		struct.c\
		libft/ft_strdup.c\
		libft/ft_strjoin.c\
		libft/ft_strlen.c\
		libft/get_next_line.c\
		main.c

OBJ = $(SRCS:.c=.o)

CFLAGS = #-Wall -Wextra -Werror 

all: $(NAME)

$(NAME) : $(OBJ)
	@ar rcs $(NAME_LIB) $(OBJ)
	@gcc $(NAME_LIB) -o $(NAME)
	@echo "\n\033[32m--------- successfully ---------\033[0m"
	./minishell
clean :
	@rm -f $(OBJ) $(NAME)
fclean: clean
	@rm -f $(NAME_LIB)

re : fclean all