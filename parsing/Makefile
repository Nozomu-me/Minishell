NAME = minishell
LIBFT = libft/libft.a

SRCS =	parsing.c \
		symbols.c \
		struct.c \
		dollar.c \
		error.c\
		switch_new_line.c\
		redirection.c\
		search_replace.c\
		push_to_struct.c\
		free.c\
		pipe_semi.c

OBJ_DIR		=	./objs
OBJ = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	@gcc -g $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "\n\033[32m--------- successfully ---------\033[0m"

$(LIBFT): force
	@make -C libft/


$(OBJ): $(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@gcc -g -c $< -o $@

force:

clean :
	@make clean -C libft/
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C libft/
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean force
