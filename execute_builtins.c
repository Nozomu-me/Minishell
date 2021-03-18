/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 22:34:56 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/18 12:29:52 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_isbuiltin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

void	execute_builtins(char **cmd, t_list *env, t_list *my_env)
{
	if (ft_strcmp(cmd[0], "pwd") == 0)
		execute_pwd();
	else if (ft_strcmp(cmd[0], "cd") == 0)
		execute_cd(cmd, env);
	// else if (ft_strcmp(cmd[0], "echo") == 0)
	// 	execute_echo(cmd);
	else if (ft_strcmp(cmd[0], "export") == 0)
		execute_export(cmd, env, my_env);
	// else if (ft_strcmp(cmd[0], "unset") == 0)
	// 	execute_unset(cmd);
	else if (ft_strcmp(cmd[0], "env") == 0)
		execute_env(cmd, env);
}