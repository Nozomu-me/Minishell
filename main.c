/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 21:28:51 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/27 13:37:00 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc,  char **argv)
{
	char *buf;
	int ret;
	extern char **environ;
	t_minishell		mini;

	mini.env = init_env_environ(environ);
	mini.export_env = init_export_environ(environ);
	mini.unset = ft_lstnew(NULL);
	mini.glob.exit_status = 0;
	signal(SIGINT,sig_handler);
	signal(SIGQUIT,sig_handler);
	// mini.glob.exit_status = status;
	// printf("status=%d\n",status);
	mini.glob.home = ft_getenv("HOME", mini.env);
	mini.glob.mini_ret = 0;
	mini.glob.b_exit = 0;
	mini.glob.oldpwd = NULL;
	mini.glob.oldpwd_env = 0;
	mini.glob.pwd = NULL;
	mini.glob.shlvl = 2;
	shlvl(&mini);
	ret = 2;
	while(1)
	{
		if (ret != 0)
			ft_putstr("\033[33mminishell\033[0m\033[32m~$\033[0m ");
		ret = get_next_line(1, &buf);
		mini.cmds->cmd = init_cmd(buf);
		execute_cmd(&mini);
		if (mini.glob.b_exit == 1)
		{
			free(buf);
			free_tab(mini.cmds->cmd);
        	break ;
		}
		free(buf);
		free_tab(mini.cmds->cmd);
	}
	ft_lstclear(&mini.env, free);
	ft_lstclear(&mini.export_env, free);
	ft_lstclear(&mini.unset, free);
	free_tab(mini.glob.home);
	if (mini.glob.oldpwd != NULL)
		free(mini.glob.oldpwd);
	return (mini.glob.mini_ret);
}