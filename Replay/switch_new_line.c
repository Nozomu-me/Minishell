/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_new_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:37:04 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/15 12:58:28 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// char	*ret(char *line, int i)
// {
// 	char	*new;
// 	int		j;

// 	j = -1;
// 	new = malloc(sizeof(char) * i + 1);
// 	while (++j < i)
// 		new[j] = line[j];
// 	new[j] = 0;
// 	return (new);
// }

char	*inverse_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] < 0)
			line[i] *= -1;
		i++;
	}
	return (line);
}

char	*delete_quote_off(t_parse *parse, char *line, int *i, int *j)
{
	if (line[*j] == '\\')
	{
		parse->cp ++;
		line[(*i)++] = line[++(*j)];
	}
	else
	{
		if (line[*j] == '"' && parse->cp % 2 == 0)
			parse->smbl->d_quote = ON;
		else if (line[*j] == '\'' && parse->cp % 2 == 0)
			parse->smbl->s_quote = ON;
		else
			line[(*i)++] = line[*j];
	}
	return (line);
}

char	*delete_quote_on(t_parse *parse, char *line, int *i, int *j)
{
	if (parse->smbl->d_quote == ON)
	{
		if (line[*j] == '"')
			parse->smbl->d_quote = OFF;
		else if (line[*j] == '\\' && line[(*j) + 1] == '\\')
			line[(*i)++] = line[++(*j)];
		else if (line[*j] == '\\' && line[(*j) + 1] < 0 && line[(*j) + 1]
			!= '\'' * -1)
			line[(*i)++] = line[++(*j)];
		else
			line[(*i)++] = line[*j];
	}
	else if (parse->smbl->s_quote == ON)
	{
		while (line[*j] != '\'')
			line[(*i)++] = line[(*j)++];
		parse->smbl->s_quote = OFF;
	}
	return (line);
}

char	*reverse_cmd(t_parse *parse, char *line, int i, int j)
{
	parse->cp = 0;
	while (line[++j])
	{
		if (parse->smbl->d_quote == OFF && parse->smbl->s_quote == OFF)
			line = delete_quote_off(parse, line, &i, &j);
		else
			line = delete_quote_on(parse, line, &i, &j);
		if (line[j] != '\\')
		{
			parse->cp = 0;
		}
	}
	line[i] = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] < 0)
			line[i] *= -1;
		i++;
	}
	return (inverse_line(line));
}
