/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:51:40 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/24 01:29:40 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*init_env_environ(char **environ)
{
	t_list	*env;
	int		i;

	i = 1;
	env = ft_lstnew(ft_strdup(environ[0]));
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], "OLDPWD", 6) != 0)
			ft_lstadd_back(&env, ft_lstnew(ft_strdup(environ[i])));
		i++;
	}
	return (env);
}

t_list	*init_export_environ(char **environ)
{
	t_list	*env;
	int		i;

	i = 1;
	env = ft_lstnew(ft_strdup(environ[0]));
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], "OLDPWD", 6) != 0)
			ft_lstadd_back(&env, ft_lstnew(ft_strdup(environ[i])));
		else
			ft_lstadd_back(&env, ft_lstnew(ft_strdup("OLDPWD")));
		i++;
	}
	return (env);
}

char	**ft_getenv(char *name, t_list *env)
{
	char	**find;
	t_list	*tmp;

	tmp = env;
	if (name == NULL || env == NULL)
		return (NULL);
	while (tmp != NULL)
	{
		find = ft_split(tmp->content, '=');
		if (ft_strcmp(find[0], name) == 0)
		{
			return (find);
		}
		free_tabl(find);
		tmp = tmp->next;
	}
	return (NULL);
}

void	mod_env(t_list *env, char *name, char *var)
{
	t_list	*tmp;
	char	**split;
	char	**split2;
	char	**split3;
	char	*str;
	char	*str2;

	tmp = env;
	while (tmp != NULL)
	{
		split = ft_split(tmp->content, '=');
		if (name[ft_strlen(name) - 1] != '+')
		{
			if (ft_strncmp(split[0], name, ft_strlen(split[0])) == 0)
			{
				free(tmp->content);
				tmp->content = ft_strdup(var);
			}
		}
		else
		{
			split2 = ft_split(name, '+');
			split3 = ft_split(var, '=');
			if (ft_strncmp(split[0], split2[0], ft_strlen(split[0])) == 0)
			{
				free(tmp->content);
				str2 = ft_strjoin(split[0], "=");
				str = ft_strjoin(str2, split[1]);
				tmp->content = ft_strjoin(str, split3[1]);
				free(str2);
				free(str);
			}
			free_tabl(split2);
			free_tabl(split3);
		}
		free_tabl(split);
		tmp = tmp->next;
	}
}

int	check_in_env(t_list *env, char *str)
{
	t_list	*tmp;
	char	**split;

	tmp = env;
	while (tmp != NULL)
	{
		if (str[ft_strlen(str) - 1] != '+')
		{
			split = ft_split(tmp->content, '=');
			if (ft_strncmp(tmp->content, str, ft_maxlen(str, split[0])) == 0)
			{
				free_tabl(split);
				return (1);
			}
			free_tabl(split);
		}
		else if (str[ft_strlen(str) - 1] == '+')
		{
			split = ft_split(str, '+');
			if (ft_strncmp(tmp->content, split[0], ft_strlen(split[0])) == 0)
			{
				free_tabl(split);
				return (1);
			}
			free_tabl(split);
		}
		tmp = tmp->next;
	}
	return (0);
}
