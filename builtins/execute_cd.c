/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 20:46:17 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/21 00:14:01 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    mod_oldpwd(t_list *env)
{
    char    cwd[PATH_MAX];
    char    *oldpwd;
    
    getcwd(cwd, PATH_MAX);
    oldpwd = ft_strjoin("OLDPWD=", cwd);
    if (check_in_env(env, "OLDPWD") == 0)
        ft_lstadd_back(&env, ft_lstnew(oldpwd));
    else
        mod_env(env, "OLDPWD", oldpwd);
}

char    *get_path(t_list *env, int b)
{
    char    **path;
    char    cwd[PATH_MAX];

    path = NULL;
    if (b == 0)
    {
        mod_oldpwd(env);
        path = ft_getenv("HOME",env);
        if (path == NULL)
        {
            ft_putstr("minishell: cd: HOME not set\n");
            exit_status = 1;
            return (NULL);
        }
    }
    else if (b == 1)
    {
        path = ft_getenv("OLDPWD",env);
		if (path == NULL)
        {
			ft_putstr("minishell : cd: OLDPWD not set\n");
            exit_status = 1;
            return (NULL);
        }
        mod_oldpwd(env);
    }
    free(path[0]);
    return (path[1]);
}

void    execute_cd(t_minishell *mini)
{
    char    *path;
    char    *tmp_path;
    int     check_dir;
	char	cwd[PATH_MAX];

    if (mini->cmd[1] == NULL)
    {
        path = get_path(mini->env, 0);
        check_dir = chdir(path);
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
            exit_status = errno;
        }
    }
    else if (ft_strcmp(mini->cmd[1], "-") == 0)
    {
        path = get_path(mini->env, 1);
        if (path != NULL)
        {
            check_dir = chdir(path);
            if (check_dir == -1)
            {
                error_cd(path, errno);
                exit_status = errno;
                return ;
            }
        }
        if (path != NULL)
            printf("%s\n", path);
    }
    else if (ft_strcmp(mini->cmd[1], ".") == 0)
    {
        if (getcwd(cwd, PATH_MAX) == NULL)
        {
            ft_putstr_fd("cd: error retrieving current directory:", 1);
            ft_putstr_fd(" getcwd: cannot access parent directories:", 1);
            ft_putendl_fd(" No such file or directory", 1);
        }
    }
    else
    {
        mod_oldpwd(mini->env);
        check_dir = chdir(mini->cmd[1]);
		if (check_dir == -1)
        {
			error_cd(mini->cmd[1], errno);
            exit_status = errno;
        }
    }
    // free(path);
}