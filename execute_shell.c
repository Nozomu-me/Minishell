/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:09:05 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/20 23:08:35 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     call_execve(t_minishell *mini,char *path, char **env)
{
    int pid;
    int ret;
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
        // ft_putstr(realpath);
        execve(realpath, mini->cmd, env);
        // printf("ret1=%d\n", ret);
    }
    else
        wait(&pid);
    // printf("ret2=%d\n", ret);
    free(realpath);
    free(tmppath);
    return (ret);
    
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
    char            *cpath;

    i = 0;
    check = 0;
    path = ft_getenv("PATH",mini->env);
    if (path == NULL)
    {
        getcwd(cwd, PATH_MAX);
        // cpath = ft_strjoin(cwd, mini->cmd[0]);
        // printf("%s\n", cwd);
        // printf("%s\n", cpath);
        call_execve(mini, cwd, tab);
        return ;
    }
    split = ft_split(path[1], ':');
    buf = malloc(sizeof(struct stat));
    tab = list_to_tab(mini->env);
    while (split[i] != NULL)
    {
        if (stat(split[i], buf) == 0)
        {
            check = call_execve(mini,split[i], tab);
            // ft_putendl_fd(ft_itoa(check), 1);
            // if (check != -1)
            // {
            //     printf("here\n");
            //     break;
            // }
        }
        i++;
    }
    // if (check == -1)
    //     printf("minishell: %s: command not found\n", mini->cmd[0]);
    free_tab(tab);
    free(buf);
    free_tab(split);
    free_tab(path);
}