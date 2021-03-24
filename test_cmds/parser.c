/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 18:15:05 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/03/24 16:46:47 by abdel-ke         ###   ########.fr       */
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
		printf("%sDOULE QUOTE WORK%s\n", BLUE, WHITE);
	else
		printf("%sERROR DOULE QUOTE%s\n", RED, WHITE);
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
		printf("%sSINGLE QUOTE WORK%s\n", BLUE, WHITE);
	else
		printf("%sERROR SINGLE QUOTE%s\n", RED, WHITE);
	return (line);
}

void	check_quote(char *line)
{
	while (*line)
	{
		if (*line == '"')
			line = double_quote(line);
		else if (*line == '\'' && count_back(line - 1))
			line = single_quote(line);
		line++;
	}
}

int		main()
{
	char	*line;

	line = NULL;
	while(1337)
	{
		write(1, MINISHELL,ft_strlen(MINISHELL));
		get_next_line(&line);
		check_quote(line);
		free(line);
		line = NULL;
	}
}
