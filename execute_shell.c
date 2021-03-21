/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:09:05 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/21 18:21:47 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     call_execve(t_minishell *mini,char *path, char **env)
{
    int pid;
    int stat;
    int ret = 0;
    char *realpath;
    char *tmppath;

    pid = fork();
    tmppath = ft_strjoin(path,"/");
    realpath = ft_strjoin(tmppath, mini->cmd[0]);
    if (pid == -1)
    {
        exit_status = errno;
        ft_putstr(strerror(errno));
    }
    else if (pid == 0)
    {
        execve(realpath, mini->cmd, env);
        exit(2);
    }
    else
        wait(&stat);
    free(realpath);
    free(tmppath);
    return (stat);
}

void    execute_shell(t_minishell *mini)
{
    char            **path;
    char            **split;
    struct stat     *buf;
    int             i;
    char            **tab;
    int             check;
    char            cwd[PATH_MAX];

    i = 0;
    check = 0;
    path = ft_getenv("PATH",mini->env);
    tab = list_to_tab(mini->env);
    if (path == NULL)
    {
        getcwd(cwd, PATH_MAX);
        call_execve(mini, cwd, tab);
        free_tab(tab);
        return ;
    }
    split = ft_split(path[1], ':');
    buf = malloc(sizeof(struct stat));
    while (split[i] != NULL)
    {
        if (stat(split[i], buf) == 0)
        {
            check = call_execve(mini,split[i], tab);
            if (check == 0)
                break ;
        }
        i++;
    }
    free_tab(tab);
    free(buf);
    free_tab(split);
    free_tab(path);
}