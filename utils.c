/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:51:40 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/04 12:38:04 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char *ft_strfcpy(char *str, int n)
// {
// 	int		i;
// 	int		j;
// 	char	*s;

// 	i = n;
// 	j = 0;
// 	s = malloc((ft_strlen(str) - 1)*sizeof(char));
// 	while(str[i] != '\0')
// 	{
// 		s[j] = str[i];
// 		i++;
// 		j++;
// 	}
// 	return (s);
// }

int ft_sort_str(char *s1, char *s2)
{
    int i;
    
    i = 0;
    while(s1[i] != '\0' && s2[i] != '\0')
    {
        if(s1[i] > s2[i])
        {
            return (1);
        }
        else if (s1[i] < s2[i])
            return (2);
        i++;
    }
    return (0);
}

void ft_sort_tab(char **tab)
{
    char *s;
    int d;
    int i=0;
    int j=0;

    while(tab[i]!= NULL)
    {
        j = 0;
        while(tab[j]!=NULL)
        {
            d = ft_sort_str(tab[i], tab[j]);
            if(d == 2)
            {
                s = tab[i];
                tab[i] = tab[j];
                tab[j] = s;
            }
            j++;
        }
        i++;
    }
}

char **set_environ(char **environ)
{
    int     i;
    int j;
    char **env;
    
    i = 0;
    j = 0;
    while (environ[i] != NULL)
        i++;
    env =malloc(i*sizeof(char*));
    while(environ[j] != '\0')
    {
        env[j] = strdup(environ[j]);
        j++;
    }
    env[j] = NULL;
    return (env);
}

char **ft_getenv(char *name, char **env)
{
    int i;
    char **find;

    i = 0;
    if (name == NULL || env == NULL)
		return (NULL);
    while(env[i] != NULL)
    {
        find = ft_split(env[i], '=');
        if (ft_strcmp(find[0], name) == 0)
        {
            return (find);
        }
        free_tab(find);
        i++;
    }
    return (NULL);
}

void modify_env(char **environ, char *name,char *var)
{
    int     i;
    char **find;
    char *env;
    char *tmp;

    env = ft_strjoin(name,var);
    i = 0;
    while(environ[i] != NULL)
    {
        find = ft_split(environ[i],'=');
        if(strcmp(find[0], name) == 0)
        {
            tmp = env;
            env = ft_strjoin(name,"=");
            free(tmp);
            tmp = env;
            env = ft_strjoin(env,var);
            free(tmp);
            strcpy(environ[i],env);
            free(env);
        }
        i++;
        free_tab(find);
    }
}
