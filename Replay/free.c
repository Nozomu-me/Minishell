/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:57:26 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/13 15:10:53 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_free_tab(char **args)
{
	int		i;

	i = 0;
	if (args != NULL)
	{
		while(args[i] != NULL)
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
	ft_free_tab(parse->s_pipe);
}

void	free_file_list(t_file *file)
{
	t_file *curr_file;
	t_file *next_file;

	curr_file = file;
	while(curr_file)
	{
		next_file = curr_file->next;
		free(curr_file);
		curr_file = next_file;
	}
}


void	free_cmds_struct(t_cmds *cmds)
{
	ft_free_tab(cmds->args);
	cmds->args = NULL;
	free_file_list(cmds->file);
	cmds->file = NULL;
}