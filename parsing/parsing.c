/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:04:10 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/03/09 12:43:24 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		check_quote(char *line,int *i, char c)
{
	++(*i);
	while (line[(*i)] && line[(*i)] != c)
		(*i)++;
	if (!line[*i])
	{
		ft_putstr("ERROR second  double quote not existe !!");
		return 1;
	}
	return 0;
}

void	check_line(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
			if (check_quote(line, &i,  '"'))
				break;
		if (line[i] == '\'')
			if (check_quote(line, &i, '\''))
				break;
		i++;
	}
}

int     ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while(s1[i] != '\0' || s2[i] != '\0')
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    return (s1[i] - s2[i]);
}

void	get_line()
{
	int		r;
	char	*line;

	line = NULL;
	ft_putstr("\e[1;32m$minishel\033[1;34m=>\033[0m");
	while((r = get_next_line(&line)) > 0)
	{
		if (ft_strcmp(line, "exit") == 0)
			exit(0);
		check_line(line);
		ft_putstr("\n\e[1;32m$minishel\033[1;34m=>\033[0m");
		free(line);
		line = NULL;
	}
}

int main(void)
{
	get_line();
}
