/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:51:40 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/16 22:16:08 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char **set_environ(char **environ)
// {
//     int     i;
//     int j;
//     char **env;
    
//     i = 0;
//     j = 0;
//     while (environ[i] != NULL)
//         i++;
//     env =malloc(i*sizeof(char*));
//     while(environ[j] != '\0')
//     {
//         if (ft_strncmp(environ[j], "OLDPWD", 6) != 0)
//             env[j] = strdup(environ[j]);
//         j++;
//     }
//     env[j] = NULL;
//     return (env);
// }

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

// void modify_env(char **environ, char *name,char *var)
// {
//     int     i;
//     char **find;
//     char *env;
//     char *tmp;

//     env = ft_strjoin(name,var);
//     i = 0;
//     while(environ[i] != NULL)
//     {
//         find = ft_split(environ[i],'=');
//         if(strcmp(find[0], name) == 0)
//         {
//             tmp = env;
//             env = ft_strjoin(name,"=");
//             free(tmp);
//             tmp = env;
//             env = ft_strjoin(env,var);
//             free(tmp);
//             strcpy(environ[i],env);
//             free(env);
//         }
//         i++;
//         free_tab(find);
//     }
// }

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

int    check_in_env(t_list *env)
{
    t_list     *tmp;

    tmp = env;
    while (tmp != NULL)
    {
        if (ft_strncmp(tmp->content, "OLDPWD", 6) == 0)
            return (1);
        tmp = tmp->next;
    }
    return (0);
    
}