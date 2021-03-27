/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 22:34:56 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/27 14:28:51 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_isbuiltin(char *cmd)
{
	if (cmd == NULL)
		return (2);
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
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void	execute_builtins(t_minishell *mini)
{
	if (ft_strcmp(mini->cmds->cmd[0], "pwd") == 0)
		execute_pwd(mini);
	else if (ft_strcmp(mini->cmds->cmd[0], "cd") == 0)
		execute_cd(mini);
	else if (ft_strcmp(mini->cmds->cmd[0], "echo") == 0)
		execute_echo(mini->cmds->cmd, mini);
	else if (ft_strcmp(mini->cmds->cmd[0], "export") == 0)
		execute_export(mini);
	else if (ft_strcmp(mini->cmds->cmd[0], "unset") == 0)
		execute_unset(mini);
	else if (ft_strcmp(mini->cmds->cmd[0], "env") == 0)
		execute_env(mini);
	else if (ft_strcmp(mini->cmds->cmd[0], "exit") == 0)
		execute_exit(mini);
}