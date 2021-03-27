/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:09:05 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/27 13:40:08 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     call_execve(t_minishell *mini,char *path, char **env)
{
    int pid;
    int stat;
    char *realpath;
    char *tmppath;

    pid = fork();
    stat = 0;
    tmppath = ft_strjoin(path,"/");
    realpath = ft_strjoin(tmppath, mini->cmds->cmd[0]);
    if (pid == -1)
    {
        mini->glob.exit_status = 1;
        ft_putstr(strerror(errno));
    }
    else if (pid == 0)
    {
        if (execve(realpath, mini->cmds->cmd, env) == -1)
            mini->glob.exit_status = 1;
        exit(mini->glob.exit_status);
    }
    else
    {
        // if (type == END)
            wait(&stat);
    }
    free(realpath);
    free(tmppath);
    return (stat);
}
void    help_execve(t_minishell *mini, char **env)
{
    pid_t pid;
    int stat;
    
    pid = fork();
    if (pid == -1)
    {
        mini->glob.exit_status = 1;
        ft_putstr(strerror(errno));
    }
    else if (pid == 0)
    {
        if (execve(mini->cmds->cmd[0], mini->cmds->cmd, env) == -1)
            mini->glob.exit_status = 1;
        exit(mini->glob.exit_status);
    }
    else
    {
        // if (type == END)
            wait(&stat);
    }
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
    if (mini->cmds->cmd[0][0] == '.' || mini->cmds->cmd[0][0] == '/')
    {
        help_execve(mini, tab);
    }
    split = ft_split(path[1], ':');
    buf = malloc(sizeof(struct stat));
    while (split[i] != NULL)
    {
        if (stat(split[i], buf) == 0)
        {
            check = call_execve(mini,split[i], tab);
            // printf("%d\n", check);
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