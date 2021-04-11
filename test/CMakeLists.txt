cmake_minimum_required(VERSION 3.15)
project(test C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(test
        ft_strdup.c
        ft_strjoin.c
        ft_strlen.c
        ft_strnstr.c
        get_next_line.c
        libft.h
        parsing.h
        test.c)
