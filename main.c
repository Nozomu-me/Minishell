/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 21:28:51 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/20 13:59:44 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc,  char **argv)
{
	extern char **environ;
	t_mini		mini;
	t_cflist *tmp;
	struct termios term;
	// t_parse	*parse;
	char	**env;

	signal(SIGINT,sig_handler);
	signal(SIGQUIT,sig_handler);
	init(&mini, environ);
	shlvl(&mini);
	set_terminal(term);
	env = list_to_tabl(mini.export_env);
	mini.parse = initail_struct(mini.parse, env);
	while(1)
	{
		ft_putstr("\033[33mminishell\033[0m\033[32m~$\033[0m ");
		readline(&mini, &mini.cmdline, &mini.history);
		ft_putchar_fd('\n', 1);
		mini.cmdline = partition_stage(mini.parse->smbl, mini.cmdline);
		if (mini.cmdline != NULL)
		{
			if (!mini.parse->smbl->error)
				split_semi_pipe(mini.parse, mini.cmdline, 0, -1);
			// tmp = mini.splited_cmd;
			tmp = mini.parse->f_cmd;
			mini.glob.fd_prv = -1;
			while(tmp != NULL)
			{
				mini.cmds.file = NULL;
				g_check.exit_sig = 1;
				mini.cmds.type = tmp->type;
				// printf("here\n");
				mini.parse->f_cmd->name = check_dollr(mini.parse, tmp->name);
				push_to_struct(mini.parse, mini.parse->f_cmd->name);
				printf("here\n");
				// inito(&mini, tmp->name);
				execute_cmd(&mini);
				free(mini.parse->under_score);
				mini.parse->under_score = ft_strdup(mini.parse->f_cmd->name);
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
	return (mini.glob.mini_ret);
}