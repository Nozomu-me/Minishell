/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 21:28:51 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/16 19:44:38 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int main(int argc,  char **argv)
{
	char *buf;
	int ret;
	extern char **environ;
	t_list	*env;
	char	**cmd;

	env = init_environ(environ);
	signal(SIGINT,sig_handler);
	signal(SIGQUIT,sig_handler);
	ret = 2;
	while(1)
	{
		if (ret != 0)
			ft_putstr("\033[33mminishell\033[0m\033[32m~$\033[0m ");
		ret = get_next_line(1, &buf);
		cmd = init_cmd(buf);
		execute_cmd(cmd, env);
		free(buf);
		free_tab(cmd);
	}
	return (0);
}