/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_old_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:32:55 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/20 12:04:20 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mod_oldpwd(t_mini *mini)
{
	char	cwd[PATH_MAX];
	char	*old;

	old = NULL;
	getcwd(cwd, PATH_MAX);
	old = ft_strjoin("OLDPWD=", cwd);
	if (check_in_env(mini->env, "OLDPWD") == 0 && mini->glob.oldpwd_env == 0)
		ft_lstadd_back(&mini->env, ft_lstnew(ft_strdup(old)));
	else if (check_in_env(mini->env, "OLDPWD") == 1
		&& mini->glob.oldpwd_env == 0)
		mod_env(mini->env, "OLDPWD", old);
	if (check_in_env(mini->export_env, "OLDPWD") == 1
		&& mini->glob.oldpwd_env == 0)
		mod_env(mini->export_env, "OLDPWD", old);
	free(old);
	if (mini->glob.oldpwd != NULL)
		free(mini->glob.oldpwd);
	mini->glob.oldpwd = ft_strdup(cwd);
}

void	reset_oldpwd(t_mini *mini, char *save_oldpwd)
{
	char	*old;

	old = ft_strjoin("OLDPWD=", save_oldpwd);
	if (check_in_env(mini->env, "OLDPWD") == 0 && mini->glob.oldpwd_env == 0)
		ft_lstadd_back(&mini->env, ft_lstnew(ft_strdup(old)));
	else if (check_in_env(mini->env, "OLDPWD") == 1
		&& mini->glob.oldpwd_env == 0)
		mod_env(mini->env, "OLDPWD", old);
	if (check_in_env(mini->export_env, "OLDPWD") == 1
		&& mini->glob.oldpwd_env == 0)
		mod_env(mini->export_env, "OLDPWD", old);
	free(old);
	if (mini->glob.oldpwd != NULL)
		free(mini->glob.oldpwd);
	mini->glob.oldpwd = ft_strdup(save_oldpwd);
}

void	mod_pwd(t_mini *mini)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	pwd = NULL;
	getcwd(cwd, PATH_MAX);
	pwd = ft_strjoin("PWD=", cwd);
	if (check_in_env(mini->env, "PWD") == 0 && mini->glob.pwd_env == 0)
		ft_lstadd_back(&mini->env, ft_lstnew(ft_strdup(pwd)));
	if (check_in_env(mini->export_env, "PWD") == 0 && mini->glob.pwd_env == 0)
		ft_lstadd_back(&mini->export_env, ft_lstnew(ft_strdup(pwd)));
	if (check_in_env(mini->env, "PWD") == 1)
		mod_env(mini->env, "PWD", pwd);
	if (check_in_env(mini->export_env, "PWD") == 1)
		mod_env(mini->export_env, "PWD", pwd);
	if (pwd != NULL)
		free(pwd);
}

void	mod_old(t_mini *mini, char *cwd)
{
	char	*old;

	old = ft_strjoin("OLDPWD=", cwd);
	if (check_in_env(mini->env, "OLDPWD") == 0 && mini->glob.oldpwd_env == 0)
		ft_lstadd_back(&mini->env, ft_lstnew(ft_strdup(old)));
	else if (check_in_env(mini->env, "OLDPWD") == 1
		&& mini->glob.oldpwd_env == 0)
		mod_env(mini->env, "OLDPWD", old);
	if (check_in_env(mini->export_env, "OLDPWD") == 1
		&& mini->glob.oldpwd_env == 0)
		mod_env(mini->export_env, "OLDPWD", old);
	mod_pwd(mini);
	free(old);
	free(cwd);
}
