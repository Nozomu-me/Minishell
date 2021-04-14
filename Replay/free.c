/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:57:26 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/14 13:49:06 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_free_tab(char **args)
{
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
	}
}

void	ft_free(t_parse *parse)
{
	ft_free_tab(parse->s_semi);
	parse->s_semi = NULL;
	ft_free_tab(parse->s_pipe);
	parse->s_pipe = NULL;
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

void	free_cmds_struct(t_parse *cmds)
{
	ft_free_tab(cmds->cmds->args);
	cmds->cmds->args = NULL;
	free_file_list(cmds->cmds->file);
	cmds->cmds->file = NULL;
	ft_free(cmds);
}
