/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 15:50:30 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/26 15:51:02 by amouassi         ###   ########.fr       */
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
