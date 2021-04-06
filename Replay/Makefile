NAME = minishell
LIBFT = libft/libft.a

SRCS =	splited.c \
		symbols.c \
		struct.c \
		error/error.c\
		switch_new_line.c

# OBJ = $(SRCS:.c=.o)
OBJ_DIR		=	./objs
OBJ = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))
# OBJ :=  $(addprefix $(OBJECT_FOLDER)/, $(OBJ))
CFLAGS = #-Wall -Wextra -Werror

all: $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	@gcc $(OBJ) $(LIBFT) -o $(NAME)
	@echo "\n\033[32m--------- successfully ---------\033[0m"

$(LIBFT): force
	@make -C libft/


$(OBJ): $(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@gcc -c $< -o $@

force:

clean :
	@make clean -C libft/
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C libft/
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean force
