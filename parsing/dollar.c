/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:30:58 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/22 15:08:04 by amouassi         ###   ########.fr       */
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

char	*get_path_dollar(t_mini *mini, char *line, int *j)
{
	while (line[++(*j)])
		if (ft_strchr(mini->check_env, line[*j]))
			break ;
	line = ft_substr(line, 0, *j);
	return (line);
}

char    *add_dollar_path(char *path)
{
    char    *new;
    int i = 0;
    new = malloc(sizeof(char) * ft_strlen(path) + 2);
    new[0] = '$' * -1;
    while (path[i])
    {
        new[i + 1] = path[i];
        i++;
    }
    free(path);
    return new;
}

char    *file_dollar(char *line, char *path)
{
    char    *path2;
    char    *new_line;
    path2 = add_dollar_path(path);
    new_line = ft_strjoin(path2, line);
    free(path2);
    return (new_line);
}

char	*dollar(t_mini *mini, char *line)
{
	t_env	*curr;
	char	*path;
	int		j;
	int 	i;

	j = -1;
	i = -2;
	curr = mini->env2;
	path = get_path_dollar(mini, line, &j);
	while (curr)
	{
		if (compare(path, "OLDPWD"))
		{
			free(path);
			if (mini->glob.oldpwd != NULL)
				return (ft_strjoin(last_word(mini->glob.oldpwd), line + j));
			else
				return (ft_strdup(line + j));
		}
		else if (compare(path, "_"))
		{
			free(path);
			return (ft_strjoin(last_word(mini->under_score), line + j));
		}
		else if (compare(curr->name, path))
		{
			free(path);
			return (ft_strjoin(curr->value, line + j));
		}
		curr = curr->next;
	}
	while (line[i] && line[i] == ' ')
        i--;
    if (line[i] == '>' || line[i] == '<')
        return(file_dollar(line + j, path));
	free(path);
	return (ft_strdup(line + j));
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
