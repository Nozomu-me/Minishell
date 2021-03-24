/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 18:15:05 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/03/24 15:33:50 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

int 	count_back(char *line)
{
    int cp = 0;
    while (*line == '\\')
    {
        cp++;
        line--;
	}
	if (cp % 2 == 0)
		return (1);
    return (0);
}

char	*double_quote(char *line)
{
	int cp;

	cp = 0;
	while (*line)
	{
		if (*line == '"' && count_back(line - 1))
			cp++;
		if (cp % 2 == 0 && cp != 0)
			break;
		line++;
	}
	if (cp % 2 == 0)
		puts("DOULE QUOTE WORK");
	else
		puts("ERROR DOULE QUOTE");
	return (line);
}

char	*single_quote(char *line)
{
	int cp;

	cp = 0;
	while (*line)
	{
		if (*line == '\'')
			cp++;
		if (cp % 2 == 0 && cp != 0)
			break;
		line++;
	}
	if (cp % 2 == 0)
		puts("SINGLE QUOTE WORK");
	else
		puts("ERROR SINGLE QUOTE");
	return (line);
}

void	check_quote(char *line)
{
	while (*line)
	{
		if (*line == '"')
			line = double_quote(line);
		else if (*line == '\'')
			line = single_quote(line);
		line++;
	}
}

int main()
{
	char	*line;
	char *minishel = "\n\e[1;32m$minishel\033[1;34m=> \033[0m";
	line = NULL;
	while(1337)
	{
		write(1, minishel,ft_strlen(minishel));
		get_next_line(&line);
		check_quote(line);
		free(line);
		line = NULL;
	}
}
