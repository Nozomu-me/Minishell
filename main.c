/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 21:28:51 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/20 12:29:41 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int main(int argc,  char **argv)
{
	char *buf;
	int ret;
	extern char **environ;
	t_minishell		mini;

	mini.env = init_environ(environ);
	mini.export_env = init_environ(environ);
	mini.unset = ft_lstnew(NULL);
	signal(SIGINT,sig_handler);
	signal(SIGQUIT,sig_handler);
	exit_status = 0;
	ret = 2;
	while(1)
	{
		// if (ret != 0)
		ft_putstr("\033[33mminishell\033[0m\033[32m~$\033[0m ");
		ret = get_next_line(1, &buf);
		mini.cmd = init_cmd(buf);
		execute_cmd(&mini);
		// printf("here\n");
		free(buf);
		free_tab(mini.cmd);
	}
	return (0);
}