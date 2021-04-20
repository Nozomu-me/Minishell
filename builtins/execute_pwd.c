/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 19:29:17 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/17 14:44:23 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_pwd(t_mini *mini)
{
	char	buf[PATH_MAX];

	g_check.exit_status = 0;
	if (getcwd(buf, PATH_MAX) == NULL)
	{
		mini->glob.pwd = buf;
		ft_putendl_fd(mini->glob.pwd, mini->glob.fd_red);
	}
	else
	{
		mini->glob.pwd = buf;
		ft_putendl_fd(mini->glob.pwd, mini->glob.fd_red);
	}
}
