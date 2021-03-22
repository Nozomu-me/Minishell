/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 11:56:59 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/22 14:57:29 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
        // free_tab(find);
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
int     call_execve(char **argv,char *path, char **env)
{
    int pid;
    pid = fork();
    int ret;
    char *realpath;
    char *tmppath;
    char* arguments[] = {argv[1],argv[2], NULL };
    
    tmppath = ft_strjoin(path,"/");
    realpath = ft_strjoin(tmppath, argv[1]);
    if (pid == -1)
    {
        printf("error\n");
    }
    else if (pid == 0)
        ret = execve(realpath, arguments,env);
    else
        wait(&pid);
    return (ret);
    
}
int main(int argc, char **argv)
{
    char **path;
    char **split;
    extern char **environ;
    t_list *env;
    struct stat *buf;
    char buffer[PATH_MAX];

    buf = malloc(sizeof(struct stat));
    env = init_environ(environ);
    path = ft_getenv("PATH",env);
    split = ft_split(path[1], ':');
    int i = 0;
        while (split[i] != NULL)
        {
            if (stat(split[i], buf) == 0)
            {
                if (call_execve(argv,split[i], environ) == 0)
                    break;
            }
            // else
            // {
            //     printf("stat error %d", errno);
            // }
            i++;
        }
}