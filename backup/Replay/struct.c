/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:22:04 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/03/28 11:02:39 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_file		*ft_lstnew_file(char *f_name, char *f_type)
{
	t_file *new;

	new = malloc(sizeof(t_cmds));
	if (new)
	{
		new->name = f_name;
		new->filetype = f_type;
		new->next = NULL;
	}
	return (new);
}

void		ft_lstadd_back_file(t_file **alst, t_file *new)
{
	t_file *list;

	if (!alst || !new)
		return ;
	if (*alst)
	{
		list = *alst;
		while (list && list->next)
			list = list->next;
		list->next = new;
	}
	else
		*alst = new;
}

t_cmds		*ft_lstnew(char **v_cmd, char *v_type, char *f_name, char *f_type)
{
	t_cmds *new;

	new = malloc(sizeof(t_cmds));
	if (new)
	{
		new->cmd = v_cmd;
		new->type = v_type;
		ft_lstadd_back_file(&new->file, ft_lstnew_file(f_name, f_type));
		new->file->next = NULL;
		new->next = NULL;
	}
	return (new);
}

void		ft_lstadd_back(t_cmds **alst, t_cmds *new)
{
	t_cmds *list;

	if (!alst || !new)
		return ;
	if (*alst)
	{
		list = *alst;
		while (list && list->next)
			list = list->next;
		list->next = new;
	}
	else
		*alst = new;
}

void		affichage(char *line, t_cmds *cmds)
{
	cmds = NULL;
	cmds = parser(cmds, line);
	while (cmds)
	{
		printf("CMDS ==>  ");
		while (*cmds->cmd)
			printf("|%s| ", *cmds->cmd++);
		printf("\nTYPE ==>  |%s|\n", cmds->type);
		while (cmds->file)
		{
			printf("FILE ==>  ");
			printf("|%s|\t|%s|\n", cmds->file->name, cmds->file->filetype);
			cmds->file = cmds->file->next;
		}
		if (cmds->next)
			puts("");
		cmds = cmds->next;
	}
}
