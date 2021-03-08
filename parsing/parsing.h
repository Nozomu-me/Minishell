#ifndef PARSING_H
#define PARSING_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	ft_putchar(char c);
void	ft_putstr(char *str);
int		get_next_line(char **line);
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
int		is_n(char *str);
char	*ft_strjoin(char *str1, char *str2);
char	*my_strcut(char *str, int n);
int		fill_line(char **content, char **line);
int		count_word(char *str);
char	*write_word(char *str, int *n);
char	**ft_split(char *str);

#endif