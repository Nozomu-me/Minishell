/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 19:29:17 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/23 16:38:04 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    execute_pwd(t_minishell *mini)
{
	char    buf[PATH_MAX];
	
	if (getcwd(buf, PATH_MAX) == NULL)
	{
		mini->glob.pwd = buf;
		printf("%s\n", mini->glob.pwd);
	}
	else
	{
		mini->glob.pwd = buf;
		printf("%s\n", mini->glob.pwd);
	}
}