/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 21:28:51 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/21 15:28:24 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc,  char **argv)
{
	extern char **environ;
	t_mini		mini;
	t_cflist *tmp;
	struct termios term;
	char	**env;
	char	*tmpline;

	signal(SIGINT,sig_handler);
	signal(SIGQUIT,sig_handler);
	init(&mini, environ);
	shlvl(&mini);
	set_terminal(term);
	initail_struct(&mini, env);
	while(1)
	{
		ft_putstr("\033[33mminishell\033[0m\033[32m~$\033[0m ");
		readline(&mini, &mini.cmdline, &mini.history);
		ft_putchar_fd('\n', 1);
		if (mini.cmdline != NULL)
		{
			tmpline = mini.cmdline;
			mini.cmdline = partition_stage(mini.smbl, mini.cmdline);
			free(tmpline);
			if (!mini.smbl->error)
					splitpipesemi(&mini);
			tmp = mini.splited_cmd;
			mini.glob.fd_prv = -1;
			while(tmp != NULL)
			{
				mini.cmds.file = NULL;
				g_check.exit_sig = 1;
				mini.cmds.type = tmp->type;
				env = list_to_tabl(mini.export_env);
				mini.env2 = create_env_list(env);
				tmp->name = check_dollr(&mini , tmp->name);
				push_to_struct(&mini, tmp->name);
				execute_cmd(&mini);
				free(mini.under_score);
				mini.under_score = ft_strdup(mini.splited_cmd->name);
				g_check.exit_sig = 0;
				tmp = tmp->next;
				if (mini.cmds.file != NULL)
				{
					cf_lstclear(&mini.cmds.file, free);
					mini.cmds.file = NULL;
				}
				if (mini.cmds.cmd != NULL)
				{
					free_tabl(mini.cmds.cmd);
					mini.cmds.cmd = NULL;
				}
				free_tabl(env);
				env_lstclear(&mini.env2, free);
			}
			if (mini.glob.b_exit == 1)
			{
				if (mini.cmdline != NULL)
					free(mini.cmdline);
				break ;
			}
		}
		if (mini.cmdline != NULL)
			free(mini.cmdline);
		if (mini.splited_cmd != NULL)
		{
			cf_lstclear(&mini.splited_cmd, free);
			mini.splited_cmd = NULL;
		}
	}
	free_mini(&mini);
	free(mini.under_score);
	free(mini.smbl);
	return (mini.glob.mini_ret);
}