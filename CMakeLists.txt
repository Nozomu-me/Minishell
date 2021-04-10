cmake_minimum_required(VERSION 3.15)
project(minishell_)

set(CMAKE_CXX_STANDARD 14)

include_directories(Replay)
include_directories(Replay/libft)

add_executable(minishell_
        Replay/error/error.c
#        Replay/libft/objs/ft_atoi.o
#        Replay/libft/objs/ft_bzero.o
#        Replay/libft/objs/ft_calloc.o
#        Replay/libft/objs/ft_isalnum.o
#        Replay/libft/objs/ft_isalpha.o
#        Replay/libft/objs/ft_isascii.o
#        Replay/libft/objs/ft_isdigit.o
#        Replay/libft/objs/ft_isprint.o
#        Replay/libft/objs/ft_itoa.o
#        Replay/libft/objs/ft_memccpy.o
#        Replay/libft/objs/ft_memchr.o
#        Replay/libft/objs/ft_memcmp.o
#        Replay/libft/objs/ft_memcpy.o
#        Replay/libft/objs/ft_memmove.o
#        Replay/libft/objs/ft_memset.o
#        Replay/libft/objs/ft_putchar_fd.o
#        Replay/libft/objs/ft_putendl_fd.o
#        Replay/libft/objs/ft_putnbr_fd.o
#        Replay/libft/objs/ft_putstr_fd.o
#        Replay/libft/objs/ft_split.o
#        Replay/libft/objs/ft_strchr.o
#        Replay/libft/objs/ft_strdup.o
#        Replay/libft/objs/ft_strjoin.o
#        Replay/libft/objs/ft_strlcat.o
#        Replay/libft/objs/ft_strlcpy.o
#        Replay/libft/objs/ft_strlen.o
#        Replay/libft/objs/ft_strmapi.o
#        Replay/libft/objs/ft_strncmp.o
#        Replay/libft/objs/ft_strnstr.o
#        Replay/libft/objs/ft_strrchr.o
#        Replay/libft/objs/ft_strtrim.o
#        Replay/libft/objs/ft_substr.o
#        Replay/libft/objs/ft_tolower.o
#        Replay/libft/objs/ft_toupper.o
#        Replay/libft/objs/get_next_line.o
        Replay/libft/ft_atoi.c
        Replay/libft/ft_bzero.c
        Replay/libft/ft_calloc.c
        Replay/libft/ft_isalnum.c
        Replay/libft/ft_isalpha.c
        Replay/libft/ft_isascii.c
        Replay/libft/ft_isdigit.c
        Replay/libft/ft_isprint.c
        Replay/libft/ft_itoa.c
        Replay/libft/ft_memccpy.c
        Replay/libft/ft_memchr.c
        Replay/libft/ft_memcmp.c
        Replay/libft/ft_memcpy.c
        Replay/libft/ft_memmove.c
        Replay/libft/ft_memset.c
        Replay/libft/ft_putchar_fd.c
        Replay/libft/ft_putendl_fd.c
        Replay/libft/ft_putnbr_fd.c
        Replay/libft/ft_putstr_fd.c
        Replay/libft/ft_split.c
        Replay/libft/ft_strchr.c
        Replay/libft/ft_strdup.c
        Replay/libft/ft_strjoin.c
        Replay/libft/ft_strlcat.c
        Replay/libft/ft_strlcpy.c
        Replay/libft/ft_strlen.c
        Replay/libft/ft_strmapi.c
        Replay/libft/ft_strncmp.c
        Replay/libft/ft_strnstr.c
        Replay/libft/ft_strrchr.c
        Replay/libft/ft_strtrim.c
        Replay/libft/ft_substr.c
        Replay/libft/ft_tolower.c
        Replay/libft/ft_toupper.c
        Replay/libft/get_next_line.c
#        Replay/libft/libft.a
        Replay/libft/libft.h
#        Replay/libft/Makefile
#        Replay/objs/error/error.o
#        Replay/objs/dollar.o
#        Replay/objs/splited.o
#        Replay/objs/struct.o
#        Replay/objs/switch_new_line.o
#        Replay/objs/symbols.o
#        Replay/a.out
        Replay/dollar.c
#        Replay/Makefile
#        Replay/minishell
        Replay/parsing.h
        Replay/redirection.c
        Replay/sh_dollar.sh
        Replay/splited.c
        Replay/struct.c
        Replay/struct2.c
        Replay/switch_new_line.c
        Replay/symbols.c)
