# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 14:54:25 by abdel-ke          #+#    #+#              #
#    Updated: 2021/04/01 19:38:08 by abdel-ke         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = ddd
CFLAGS = -Wall -Wextra -Werror
SRC =	ft_calloc.c		\
		ft_atoi.c		\
		ft_bzero.c		\
		ft_memset.c		\
		ft_memccpy.c	\
		ft_memcpy.c		\
		ft_memmove.c	\
		ft_memcmp.c		\
		ft_memchr.c		\
		ft_isalnum.c	\
		ft_isalpha.c	\
		ft_isascii.c	\
		ft_isdigit.c	\
		ft_isprint.c	\
		ft_tolower.c	\
		ft_toupper.c	\
		ft_strchr.c		\
		ft_strdup.c		\
		ft_strlen.c		\
		ft_strncmp.c	\
		ft_strrchr.c	\
		ft_strnstr.c	\
		ft_strlcpy.c	\
		ft_strlcat.c	\
		ft_substr.c		\
		ft_strjoin.c	\
		ft_strtrim.c	\
		ft_itoa.c		\
		ft_split.c		\
		ft_putchar_fd.c	\
		ft_putstr_fd.c	\
		ft_putnbr_fd.c	\
		ft_putendl_fd.c	\
		ft_strmapi.c \
		get_next_line.c

OBJ_DIR		=	./objs
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all		: $(NAME)
$(NAME)	: $(OBJ)
	ar rc $(NAME) $^
	ranlib $(NAME)

$(OBJ): $(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	gcc -c $< -o $@

clean 	:
	rm -f $(OBJ_DIR)/*.o
fclean 	: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)
re 		: fclean all
