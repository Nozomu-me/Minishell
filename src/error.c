/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:45:09 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/03/24 18:18:28 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

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

char	*double_quote(char *line, int *cp)
{
	while (*line)
	{
		if (*line == '"' && count_back(line - 1))
			(*cp)++;
		if ((*cp) % 2 == 0 && (*cp) != 0)
			break;
		line++;
	}
	if (((*cp) = (*cp) % 2) != 0)
		ft_error("ERROR DOUBLE QUOTE", RED, WHITE);
	return (line);
}

char	*single_quote(char *line, int *cp)
{
	while (*line)
	{
		if (*line == '\'')
			(*cp)++;
		if ((*cp) % 2 == 0 && (*cp) != 0)
			break;
		line++;
	}
	if (((*cp) = (*cp) % 2) != 0)
		ft_error("ERROR SINGLE QUOTE", RED, WHITE);
	return (line);
}

void	check_quote(char *line, int *check)
{
	while (*line)
	{
		if (*line == '"')
			line = double_quote(line, check);
		else if (*line == '\'' && count_back(line - 1))
			line = single_quote(line, check);
		line++;
	}
}
