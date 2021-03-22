/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 20:46:17 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/22 17:52:07 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    mod_oldpwd(t_list *env)
{
    char    cwd[PATH_MAX];
    char    *old;
    
    getcwd(cwd, PATH_MAX);
    old = ft_strjoin("OLDPWD=", cwd);
    if (check_in_env(env, "OLDPWD") == 1)
        mod_env(env, "OLDPWD", old);
    oldpwd = ft_strdup(cwd);
}

char    *get_path(t_list *env, int b)
{
    char    *path;

    path = NULL;
    if (b == 0)
    {
        mod_oldpwd(env);
        path = home[1];
    }
    else if (b == 1)
    {
        path = oldpwd;
		if (path == NULL)
        {
			ft_putstr("minishell : cd: OLDPWD not set\n");
            exit_status = 1;
            return (NULL);
        }
        mod_oldpwd(env);
    }
    return (path);
}

void    current_dir_err()
{
    ft_putstr_fd("cd: error retrieving current directory:", 1);
    ft_putstr_fd(" getcwd: cannot access parent directories:", 1);
    ft_putendl_fd(" No such file or directory", 1);
}

void    help_execute_cd(t_minishell *mini)
{
    char    *path;
	char	cwd[PATH_MAX];

    if (ft_strcmp(mini->cmd[1], "-") == 0)
    {
        path = get_path(mini->env, 1);
        if (path != NULL)
        {
            if (chdir(path) == -1)
            {
                error_cd(path, errno);
                exit_status = 1;
                return ;
            }
        }
        if (path != NULL)
            ft_putendl_fd(path, 1);
    }
    else if (ft_strcmp(mini->cmd[1], ".") == 0)
    {
        if (getcwd(cwd, PATH_MAX) == NULL)
            current_dir_err();
    }
    else
    {
        mod_oldpwd(mini->env);
		if (chdir(mini->cmd[1]) == -1)
        {
			error_cd(mini->cmd[1], errno);
            exit_status = 1;
        }
    }
}

void    execute_cd(t_minishell *mini)
{
    char    *path;
    char    *tmp_path;
    int     check_dir;

    if (mini->cmd[1] == NULL)
    {
        path = get_path(mini->env, 0);
        check_dir = chdir(path);
        free(path);
    }
    else if (ft_strcmp(mini->cmd[1], "~") == 0)
    {
        path = get_path(mini->env, 0);
        mod_oldpwd(mini->env);
        tmp_path = search_replace(mini->cmd[1], "~", path);
        check_dir = chdir(tmp_path);
		if (check_dir == -1)
        {
			error_cd(tmp_path, errno);
            exit_status = 1;
        }
    }
    else
        help_execute_cd(mini);
}