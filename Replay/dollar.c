/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:30:58 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/13 17:56:27 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_turn_dollar(t_symbol *smbl, char *line, int i)
{
	if (smbl->s_quote == ON)
		line[i] *= -1;
	return (line);
}

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

char	*get_path(t_parse *parse, char *line, int *j)
{
	while (line[++(*j)])
		if (ft_strchr(parse->check_env, line[*j]))
			break;
	return (ft_substr(line, 0, *j));
}

char	*dollar(t_parse *parse, char *line)
{
	char	*path;
	int		i;
	int		j;

	j = -1;
	i = -1;
	
	path = get_path(parse, line, &j);
	printf("\t\t|%s|\n", path);
	i = 0;
	while (parse->env[i])
	{
		parse->split = ft_split(parse->env[i], '=');
		if (compare(path, "_"))
		{
			if (parse->already_pipe == 0)
				return (ft_strjoin(last_word(parse->under_score), line + j));
			else
				return(line + j);
		}
		else if (compare(parse->split[0], path))
			return (ft_strjoin(parse->split[1], line + j));
		i++;
	}
	free(path);
	return (line + j);
}

char	*check_dollr(t_parse *parse, char *line)
{
	char *new;
	int i;

	i = 0;
	new = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$' && !count_back(line + (i - 1)) &&
			!ft_strchr(parse->check_env, line[i + 1]))
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
	// free(new);
	return line;
}
