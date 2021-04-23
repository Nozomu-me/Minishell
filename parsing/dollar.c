/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:30:58 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/22 16:17:33 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*check_path(t_mini *mini, char *path, char *line, int j)
{
	t_env	*curr;
	int		i;

	curr = mini->env2;
	i = -2;
	while (curr)
	{
		if (compare(path, "OLDPWD"))
		{
			if (mini->glob.oldpwd != NULL)
				return (ft_strjoin(last_word(mini->glob.oldpwd), line + j));
			else
				return (ft_strdup(line + j));
		}
		else if (compare(path, "_"))
			return (ft_strjoin(last_word(mini->under_score), line + j));
		else if (compare(curr->name, path))
			return (ft_strjoin(curr->value, line + j));
		curr = curr->next;
	}
	while (line[i] && line[i] == ' ')
		i--;
	if (line[i] == '>' || line[i] == '<')
		return (file_dollar(line + j, path));
	return (ft_strdup(line + j));
}

char	*dollar(t_mini *mini, char *line)
{
	char	*path;
	char	*tmp;
	int		j;

	j = -1;
	path = get_path_dollar(mini, line, &j);
	tmp = check_path(mini, path, line, j);
	free(path);
	return (tmp);
}

char	*check_dollr(t_mini *mini, char *line)
{
	char	*new;
	char	*tmp;
	int		i;

	i = -1;
	new = NULL;
	while (line[++i])
	{
		if (line[i] == '$' && !count_back(line + (i - 1))
			&& !ft_strchr(mini->check_env, line[i + 1]))
		{
			new = dollar(mini, line + i + 1);
			line[i] = 0;
			tmp = ft_strjoin(line, new);
			if (line)
				free(line);
			line = tmp;
			i = 0;
			if (new != NULL)
				free(new);
		}
		else if ((line[i] == '$') && count_back(line + (i - 1)))
			line[i] *= -1;
	}
	return (line);
}
