/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 13:57:26 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/20 13:17:35 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

// void	ft_lstclear(t_file **lst)
// {
// 	t_file	*list;
// 	t_file	*prev;

// 	if (!lst)
// 		return ;
// 	list = *lst;
// 	while (list)
// 	{
// 		prev = list;
// 		list = list->next;
// 		free(prev->filename);
// 		free(prev);
// 	}
// 	*lst = NULL;
// }

// void	free_file_list(t_file *file)
// {
// 	t_file	*curr_file;
// 	t_file	*next_file;

// 	curr_file = file;
// 	while (curr_file)
// 	{
// 		next_file = curr_file->next;
// 		free(curr_file);
// 		curr_file = next_file;
// 	}
// }

// void	free_first_cmd(t_cflist *cmd)
// {
// 	t_cflist	*curr_cmd;	
// 	t_cflist	*nxt_cmd;

// 	curr_cmd = cmd;
// 	while (curr_cmd)
// 	{
// 		nxt_cmd = curr_cmd->next;
// 		free(curr_cmd);
// 		curr_cmd = nxt_cmd;
// 	}
// }

// void	free_cmds_struct(t_parse *cmds)
// {
// 	if (cmds->cmds != NULL)
// 	{
// 		ft_free_tab(cmds->cmds->args);
// 		cmds->cmds->args = NULL;
// 		ft_lstclear(&cmds->cmds->file);
// 		cmds->cmds->file = NULL;
// 		free(cmds->cmds);
// 	}
// }
