NAME = minishell

SRCS =	ft_strjoin.c \
		get_next_line.c \
		ft_strlen.c \
		redirection.c \
		ft_substr.c \
		ft_strdup.c \

# OBJ = $(SRCS:.c=.o)
OBJ = $(SRCS:.c=.o)
CFLAGS = #-Wall -Wextra -Werror

all: $(NAME)

$(NAME) : $(OBJ)
	@gcc -g $(OBJ) -o $(NAME)
	@echo "\n\033[32m--------- successfully ---------\033[0m"

clean :
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean force
