/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 16:43:14 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/28 15:48:47 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_command(char *command)
{
	ft_putstr("minishell: ");
	ft_putstr(command);
	ft_putstr(": command not found\n");
}

void	error_permission(char *command)
{
	ft_putstr("minishell: ");
	ft_putstr(command);
	ft_putstr(": Permission denied\n");
}

void	error_file_nodir(char *command)
{
	ft_putstr("minishell: ");
	ft_putstr(command);
	if (command[0] == '$' && command[0] != '?')
		ft_putstr(": ambiguous redirect\n");
	else if (command[0] == '/')
		ft_putstr(": Permission denied\n");
	else
		ft_putstr(": No such file or directory\n");
}
