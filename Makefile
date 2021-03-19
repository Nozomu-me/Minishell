# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/02 19:19:58 by amouassi          #+#    #+#              #
#    Updated: 2021/03/19 12:16:24 by amouassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell.a
CC = gcc
FLAGS = 
AR = ar rcs
LIBFT = libft
NAMELIBFT = libft.a
EXE = minishell

SRCLIB =  ft_atoi.c \
		  ft_bzero.c \
	      ft_calloc.c \
	  	  ft_isalnum.c \
	 	  ft_isalpha.c \
		  ft_isascii.c \
		  ft_isdigit.c \
		  ft_isprint.c \
		  ft_itoa.c \
		  ft_memccpy.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_memcpy.c \
		  ft_memmove.c \
		  ft_memset.c \
		  ft_putchar_fd.c \
		  ft_putnbr_fd.c \
		  ft_putstr_fd.c \
		  ft_putendl_fd.c \
		  ft_split.c \
		  ft_strchr.c \
		  ft_strdup.c \
		  ft_strjoin.c \
		  ft_strlcat.c \
		  ft_strlcpy.c \
		  ft_strlen.c \
		  ft_strmapi.c \
		  ft_strncmp.c \
		  ft_strnstr.c \
		  ft_strrchr.c \
		  ft_strtrim.c \
		  ft_substr.c \
		  ft_tolower.c \
		  ft_toupper.c \
		  ft_lstadd_back.c \
		  ft_lstadd_front.c \
		  ft_lstlast.c \
		  ft_lstnew.c \
		  ft_lstsize.c \
		  ft_lstdelone.c \
		  ft_lstclear.c \
		  ft_lstiter.c \
		  ft_lstmap.c \

SRC = utils/utils.c \
	  utils/env_utils.c \
	  utils/utils2.c \
	  utils/list_utils.c \
	  sig_handler.c \
	  free.c \
	  gnl/get_next_line.c \
	  gnl/get_next_line_utils.c \
	  builtins/execute_pwd.c \
	  builtins/execute_cd.c \
	  builtins/execute_env.c \
	  builtins/execute_export.c \
	  builtins/execute_unset.c \
	  errors/errors.c \
	  execute_cmd.c \
	  init_cmd.c \
	  execute_builtins.c \

MAIN = main.c
OBJ = $(SRC:.c=.o)
OBJLIB = $(addprefix $(LIBFT)/,$(SRCLIB:.c=.o))

all: $(NAME)

$(NAME): $(OBJ) $(OBJLIB)
	$(AR) $(NAME) $(OBJ) $(OBJLIB)
	$(CC) $(FLAG) $(MAIN) $(NAME) -o $(EXE)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(OBJLIB)
	rm -f main.o
fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)/$(NAMELIBFT)

re: fclean all