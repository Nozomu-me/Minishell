cmake_minimum_required(VERSION 3.15)
project(minishell_)

set(CMAKE_CXX_STANDARD 14)

include_directories(Replay)
include_directories(Replay/libft)

add_executable(minishell_
        Replay/error/error.c
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
        Replay/libft/libft.h
        Replay/dollar.c
        Replay/parsing.h
        Replay/redirection.c
        Replay/parsing.c
        Replay/struct.c
        Replay/change_to_sp.c
        Replay/switch_new_line.c
        Replay/push_to_struct.c
        Replay/free.c
        Replay/symbols.c)
