NAME = minishell

NAME_LIB = minishell.a

SRCS =	parsing.c\
		get_next_line.c\
		libft.c\
		ft_split.c\
		

OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror 

all : $(NAME)

$(NAME) : $(OBJ)
	@ar rcs $(NAME_LIB) $(OBJ)
	@gcc $(CFLAGS) $(NAME_LIB) -o $(NAME)
	@echo "\n\033[32m--------- successfully ---------\033[0m"
	@./minishell
clean :
	@rm -f $(OBJ) $(NAME)
fclean: clean
	@rm -f $(NAME_LIB)

re : fclean all