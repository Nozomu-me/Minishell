/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:57:26 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/15 15:18:14 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_free_tab(char **args)
{
	// puts("im here");
	int		i;

	i = 0;
	if (args != NULL)
	{
		while (args[i] != NULL)
		{
			free(args[i]);
			i++;
		}
		free(args);
	// puts("im here2");
	}
}

void	ft_free(t_parse *parse)
{
	if (parse->s_semi)
	{
		ft_free_tab(parse->s_semi);
		parse->s_semi = NULL;
	}
	if (parse->s_pipe != NULL)
	{
		ft_free_tab(parse->s_pipe);
		parse->s_pipe = NULL;
	}
	if (parse->src_new)
	{
		free(parse->src_new);
		parse->src_new = NULL;
	}
	if (parse->new)
	{
		free(parse->new);
		parse->new = NULL;
	}
}

void	free_file_list(t_file *file)
{
	t_file	*curr_file;
	t_file	*next_file;

	curr_file = file;
	while (curr_file)
	{
		next_file = curr_file->next;
		free(curr_file);
		curr_file = next_file;
	}
}

void	free_first_cmd(t_f_cmd *cmd)
{
	t_f_cmd	*curr_cmd;	
	t_f_cmd	*nxt_cmd;

	curr_cmd = cmd;
	while (curr_cmd)
	{
		nxt_cmd = curr_cmd->next;
		free(curr_cmd);
		curr_cmd = nxt_cmd;
	}
}

void	free_list(t_parse *parse)
{
	ft_free_tab(parse->s_semi);
	ft_free_tab(parse->s_pipe);
	ft_free_tab(parse->split);
	free_first_cmd(parse->f_cmd);
}

void	free_cmds_struct(t_parse *cmds)
{
	if (cmds->cmds != NULL)
	{
		ft_free_tab(cmds->cmds->args);
		cmds->cmds->args = NULL;
		free_file_list(cmds->cmds->file);
		cmds->cmds->file = NULL;
		ft_free(cmds);
	}
}
