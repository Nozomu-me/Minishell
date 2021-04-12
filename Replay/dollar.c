/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:30:58 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/12 18:30:59 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		compare(char *str, char *str2)
{
	while (*str || *str2)
	{
		if (*str != *str2)
			return 0;
		str++;
		str2++;
	}
	return 1;
}

char	*last_word(char *line)
{
	int i;

	i = ft_strlen(line) - 1;
	while (line[i - 1] && line[i - 1] != ' ')
		i--;
	return (line + i);
}

char	*dollar(t_parse *parse, char *line)
{
	char **split;
	char *path;
	int i;
	int j;

	j = -1;
	i = -1;
	while (line[++j])
		if (ft_strchr(parse->check_env, line[j]))
			break;
	path = ft_substr(line, 0, j);
	i = 0;
	while (parse->env[i])
	{
		split = ft_split(parse->env[i], '=');
		if (compare(path, "_"))
		{
			if (parse->already_pipe == 0)
				return (ft_strjoin(last_word(parse->under_score), line + j));
			else
				return(line + j);
		} else 
		if (compare(split[0], path))
		{
			return (ft_strjoin(split[1], line + j));
		}
		i++;
	}
	return (line + j);
}

char	*check_dollr(t_parse *parse, char *line)
{
	char *new;
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && !count_back(line + (i - 1)) && !ft_strchr(parse->check_env, line[i + 1]))
		{
			new = dollar(parse, line + i + 1);
			line[i] = 0;
			line = ft_strjoin(line, new);
			i = 0;
		}
		else if (line[i] == '$' && count_back(line + (i - 1)))
			line[i] *= -1;
		i++;
	}
	return line;
}
