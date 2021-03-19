/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 19:29:17 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/19 09:23:23 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    execute_pwd()
{
	char    buf[PATH_MAX];
	
	if (getcwd(buf, PATH_MAX) == NULL)
	{
		error_pwd("pwd: ",errno);
		exit_status = errno;
		// exit(EXIT_FAILURE);
	}
	else
	{
		printf("%s\n", buf);
	}
}