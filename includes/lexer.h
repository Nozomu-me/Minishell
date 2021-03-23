/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:57:29 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/03/22 16:52:23 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "../src/libft/libft.h"

# define green	"\e[1;32m"
# define red	"\e[0;31m"
# define white	"\033[0m"

char	**cmd;

typedef	enum	e_token_type
{
	NONE,
	WORD,
	SEMI,
	PIPE,
	G_S_QUOTE,
	L_S_QUOTE,
	D_QUOTE,
	END
}				t_token_type;

typedef	struct	s_token
{
	int				index;
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}				t_token;

typedef enum	e_bool
{
	FALSE,
	TRUE
}				t_bool;

void				ft_putchar(char c);
void				ft_putstr(char *str);
int					get_next_line(char **line);
int					is_n(char *str);
char				*my_strcut(char *str, int n);
int					fill_line(char **content, char **line);
static	char		*put_word(char const *s, char c, int *n);
char				*write_word(char *str, int *n);
char				**ft_split(char const *s, char c);

t_token		*lexer_line(char *line);
void		check_line(t_token *token);
void		ft_lstadd_back(t_token **alst, t_token *new);
t_token		*ft_lstnew(int index, t_token_type type, char *value);
#endif
