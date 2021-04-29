/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:37:46 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/29 00:06:07 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path_dollar(t_mini *mini, char *line, int *j)
{
	while (line[++(*j)])
		if (ft_strchr(mini->check_env, line[*j])
			|| line[*j] == ' ' * -1 || line[*j] == '\'' * -1
			|| line[*j] == '|' * -1 || line[*j] == ';' * -1
			|| line[*j] == '<' * -1 || line[*j] == '>' * -1)
			break ;
	line = ft_substr(line, 0, *j);
	return (line);
}

char	*add_dollar_path(char *path)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * ft_strlen(path) + 2);
	new[0] = '$' * -1;
	while (path[i])
	{
		new[i + 1] = path[i];
		i++;
	}
	return (new);
}

char	*file_dollar(char *line, char *path)
{
	char	*path2;
	char	*new_line;

	path2 = add_dollar_path(path);
	new_line = ft_strjoin(path2, line);
	free(path2);
	return (new_line);
}

char	*dollar_digit(char *line, int *i)
{
	char	*new;
	char	*tmp;

	if (line[*i + 1] == '0')
	{
		new = ft_strjoin("minishell", line + (*i) + 2);
		line[*i] = 0;
		tmp = ft_strjoin(line, new);
		if (line)
			free(line);
		line = tmp;
        if (line[*i] == '$')
            *i = -1;
        else
            *i = 0;
		if (new != NULL)
			free(new);
	}
	else
	{
		new = ft_strdup(line + (*i) + 2);
        line[*i] = 0;
        tmp = ft_strjoin(line, new);
        if (line)
            free(line);
        line = tmp;
        if (line[*i] == '$')
            *i = -1;
        else
            *i = 0;
        if (new != NULL)
            free(new);
	}
	return (line);
}

char    *dollar_simple(t_mini *mini, char *line, int *i)
{
    char    *new;
    char    *tmp;
    char    *tmp2;
    char    *itoa;
    new = dollar(mini, line + *i + 1);
    line[*i] = 0;
    if (new[0] == '?')
    {
        itoa = ft_itoa(g_check.exit_status);
        tmp2 = ft_strjoin(itoa, new + 1);
        tmp = ft_strjoin(line, tmp2);
        free(itoa);
        free(tmp2);
    }
    else
        tmp = ft_strjoin(line, new);
    if (line[*i] == '$')
        *i = -1;
    else
        *i = 0;
    if (line)
        free(line);
    line = tmp;
    if (new != NULL)
        free(new);
    return (line);
}
