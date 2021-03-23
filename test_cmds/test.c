/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 18:15:05 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/03/23 17:43:21 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
void	check_backslash(char *line)
{
	char *new;

	while (*line)
	{
		if (*line == '\\');
	}
}

char	*double_single_quote(char *line, char c, char *type)
{
	int cp =0;

	while (*line)
	{
		if (*line == c && line[-1] != '\\')
			cp++;
		if (cp % 2 == 0 && cp != 0)
			break;
		line++;
	}
	printf("|%d|\n", cp);
	if (cp % 2 == 0)
		printf("%s WORK", type);
	else
		printf("ERROR %s", type);
	return (line);
}

void	check_quote(char *line)
{
	while (*line)
	{
		if (*line == '"')
			line = double_single_quote(line, '"', "DOUBLE QUOTTE");
		else if (*line == '\'')
			line = double_single_quote(line, '\'', "SINGLE QUOTTE");
		line++;
	}
}

int main()
{
	char	*line;

	line = NULL;
	puts("\e[1;32m$minishel\033[1;34m=>\033[0m");
	while(1337)
	{
		get_next_line(&line);
		check_quote(line);
		puts("\n\e[1;32m$minishel\033[1;34m=>\033[0m");
		free(line);
		line = NULL;
	}
}