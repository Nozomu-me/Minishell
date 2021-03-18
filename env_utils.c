/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:51:40 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/18 20:35:40 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list   *init_environ(char **environ)
{
    t_list   *env;
    int     i;

    i = 1;
    env = ft_lstnew(strdup(environ[0]));
    while(environ[i] != NULL)
    {
        if (strncmp(environ[i], "OLDPWD", 6) != 0)
            ft_lstadd_back(&env, ft_lstnew(strdup(environ[i])));
        i++;
    }
    return (env);
}

char **ft_getenv(char *name, t_list *env)
{
    char **find;
    t_list *tmp;

    tmp = env;
    if (name == NULL || env == NULL)
		return (NULL);
    while(tmp != NULL)
    {
        find = ft_split(tmp->content, '=');
        if (strcmp(find[0], name) == 0)
        {
            return (find);
        }
        free_tab(find);
        tmp = tmp->next;
    }
    return (NULL);
}

void    mod_env(t_list *env, char *name,char *var)
{
    t_list  *tmp;

    tmp = env;
    while (tmp != NULL)
    {
        if (strncmp(tmp->content, name, ft_strlen(name)) == 0)
        {
            free(tmp->content);
            tmp->content = ft_strdup(var);
        }
        tmp = tmp->next;
    }
}

int    check_in_env(t_list *env, char *str)
{
    t_list     *tmp;

    tmp = env;
    while (tmp != NULL)
    {
        if (ft_strncmp(tmp->content, str, ft_strlen(str)) == 0)
            return (1);
        tmp = tmp->next;
    }
    return (0);
}
