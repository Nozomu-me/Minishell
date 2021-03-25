/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 10:41:28 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/25 14:12:23 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    mod_oldpwd(t_minishell *mini)
{
    char    cwd[PATH_MAX];
    char    *old;
    
    old = NULL;
    getcwd(cwd, PATH_MAX);
    old = ft_strjoin("OLDPWD=", cwd);
    // printf("glob-oldpwd=%d\n",mini->glob.oldpwd_env);
    if (check_in_env(mini->env,"OLDPWD") == 0 && mini->glob.oldpwd_env == 0)
    {
        // printf("hna1\n");
        ft_lstadd_back(&mini->env, ft_lstnew(ft_strdup(old)));
    }
    else if (check_in_env(mini->env,"OLDPWD") == 1 && mini->glob.oldpwd_env == 0)
    {
        //  printf("hna2\n");
        mod_env(mini->env, "OLDPWD", old);
    }
    if (check_in_env(mini->export_env,"OLDPWD") == 1 && mini->glob.oldpwd_env == 0)
    {
        //  printf("hna3\n");
        mod_env(mini->export_env, "OLDPWD", old);
    }
    free(old);
    if (mini->glob.oldpwd != NULL)
        free(mini->glob.oldpwd);
    mini->glob.oldpwd = ft_strdup(cwd);
}

void    current_dir_err()
{
    ft_putstr_fd("cd: error retrieving current directory:", 1);
    ft_putstr_fd(" getcwd: cannot access parent directories:", 1);
    ft_putendl_fd(" No such file or directory", 1);
}

void    execute_cd(t_minishell *mini)
{
    char    *tmp_path;
    int     check_dir;
	char	cwd[PATH_MAX];
    
    tmp_path = NULL;
    if (mini->cmd[1] == NULL)
    {
        mod_oldpwd(mini);
        check_dir = chdir(mini->glob.home[1]);
    }
    else if (ft_strncmp(mini->cmd[1], "~", 1) == 0)
    {
        mod_oldpwd(mini);
        tmp_path = search_replace(mini->cmd[1], "~", mini->glob.home[1]);
        check_dir = chdir(tmp_path);
		if (check_dir == -1)
        {
			error_cd(tmp_path, errno);
            mini->glob.exit_status = 1;
        }
    }
    else if (ft_strcmp(mini->cmd[1], ".") == 0)
    {
        if (getcwd(cwd, PATH_MAX) == NULL)
            current_dir_err();
        else
        {
            if (mini->glob.oldpwd != NULL)
                free(mini->glob.oldpwd);
            mini->glob.oldpwd = ft_strdup(cwd);
        }
        
    }
    else if (ft_strcmp(mini->cmd[1], "-") == 0)
    {
        if (mini->glob.oldpwd == NULL)
        {
			ft_putstr("minishell : cd: OLDPWD not set\n");
            mini->glob.exit_status = 1;
        }
        else
        {
            getcwd(cwd, PATH_MAX);
            if (chdir(mini->glob.oldpwd) == -1)
            {
                error_cd(mini->glob.oldpwd, errno);
                mini->glob.exit_status = 1;
                return ;
            }
            ft_putendl_fd(mini->glob.oldpwd, 1);
            if (mini->glob.oldpwd != NULL)
                free(mini->glob.oldpwd);
            mini->glob.oldpwd = ft_strdup(cwd);
        }   
    }
    else
    {
        mod_oldpwd(mini);
		if (chdir(mini->cmd[1]) == -1)
        {
			error_cd(mini->cmd[1], errno);
            mini->glob.exit_status = 1;
        }
    }
    free(tmp_path);
}