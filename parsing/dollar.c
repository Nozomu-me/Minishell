/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:30:58 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/19 10:10:55 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_turn_dollar(t_symbol *smbl, char *line, int i)
{
	if (smbl->s_quote == ON)
		line[i] *= -1;
	return (line);
}

char	*last_word(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (line[i - 1] && line[i - 1] != ' ')
		i--;
	return (line + i);
}

char	*get_path_dollar(t_parse *parse, char *line, int *j)
{
	while (line[++(*j)])
		if (ft_strchr(parse->check_env, line[*j]))
			break ;
	line = ft_substr(line, 0, *j);
	return (line);
}

char	*dollar(t_parse *parse, char *line)
{
	t_env	*curr;
	char	*path;
	int		j;

	j = -1;
	curr = parse->env2;
	path = get_path_dollar(parse, line, &j);
	while (curr)
	{
		if (compare(path, "_"))
		{
			free(path);
			return (ft_strjoin(last_word(parse->under_score), line + j));
		}
		else if (compare(curr->name, path))
		{
			free(path);
			return (ft_strjoin(curr->value, line + j));
		}
		curr = curr->next;
	}
	free(path);
	return (ft_strdup(line + j));
}

char	*check_dollr(t_parse *parse, char *line)
{
	char	*new;
	char	*tmp;
	int		i;

	i = -1;
	new = NULL;
	while (line[++i])
	{
		if (line[i] == '$' && !count_back(line + (i - 1))
			&& !ft_strchr(parse->check_env, line[i + 1]))
		{
			new = dollar(parse, line + i + 1);
			line[i] = 0;
			tmp = ft_strjoin(line, new);
			if (line)
				free(line);
			line = tmp;
			i = 0;
			if (new[0])
				free(new);
		}
		else if ((line[i] == '$') && count_back(line + (i - 1)))
			line[i] *= -1;
	}
	return (line);
}
