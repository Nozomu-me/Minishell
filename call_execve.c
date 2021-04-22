/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 11:47:31 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/22 14:50:52 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child(t_mini *mini, int fds, char **env, char *path)
{
	if (dup2(mini->glob.fd_in, 0) == -1)
		ft_putendl_fd(strerror(errno), 1);
	if (fds)
	{
		dup2(fds, 1);
		close(fds);
	}
	else if (mini->cmds.type == PIPE)
	{
		if (dup2(mini->fd[1], 1) == -1)
			ft_putendl_fd(strerror(errno), 1);
		close(mini->fd[0]);
	}
	if (check_pipe_builtins(mini) == 1)
		execute_builtins(mini);
	else if (check_pipe_builtins(mini) == 0)
	{
		if (execve(path, mini->cmds.cmd, env) != 0)
			g_check.exit_status = 1;
	}
}

void	help_execve(t_mini *mini, char **env, char *path)
{
	int	fds;

	fds = redir(mini);
	if (fds == -1)
		exit(0);
	if (mini->pid == -1)
	{
		g_check.exit_status = 1;
		ft_putendl_fd(strerror(errno), 1);
	}
	else if (mini->pid == 0)
	{
		execute_child(mini, fds, env, path);
		exit(g_check.exit_status);
	}
}

int	execute_parent(t_mini *mini)
{
	close(mini->fd[1]);
	if (mini->cmds.type == END)
	{
		close(mini->fd[0]);
		waitpid(mini->pid, &mini->sig_status, 0);
		child_sig_handler(mini->sig_status);
		if (mini->glob.fd_in != 0)
			close(mini->glob.fd_in);
		mini->glob.fd_in = 0;
		while (waitpid(0, 0, 0) >= 0)
			;
	}
	if (mini->cmds.type == PIPE)
		mini->glob.fd_in = mini->fd[0];
	if (mini->glob.fd_prv == -1)
		mini->glob.fd_prv = mini->glob.fd_in;
	else
	{
		if (mini->glob.fd_prv != 0)
			close(mini->glob.fd_prv);
		mini->glob.fd_prv = mini->glob.fd_in;
	}
	return (mini->sig_status);
}

void	call_execve(t_mini *mini, char **env, char *path)
{
	pipe(mini->fd);
	mini->pid = fork();
	if (mini->pid == -1 || mini->pid == 0)
		help_execve(mini, env, path);
	else
		execute_parent(mini);
}
