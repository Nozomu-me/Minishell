/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:22:04 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/19 16:06:02 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_f_cmd	*lstnew_cmd(char *v_cmd, int type)
{
	t_f_cmd	*new;

	new = (t_f_cmd *)malloc(sizeof(t_f_cmd));
	if (new)
	{
		new->cmd = ft_strdup(v_cmd);
		new->type = type;
		new->next = NULL;
	}
	return (new);
}

void	lstadd_cmd(t_f_cmd **alst, t_f_cmd *new)
{
	t_f_cmd	*list;

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

t_file	*file_lst_new(void *filename, int filetype)
{
	t_file	*head;

	head = (t_file *)malloc(sizeof(t_file));
	if (head == NULL)
		return (NULL);
	head->filename = ft_strdup(filename);
	head->filetype = filetype;
	head->next = NULL;
	return (head);
}

void	file_lstadd_back(t_file **alst, t_file *new)
{
	t_file	*temp;

	if (!alst || !new)
		return ;
	temp = *alst;
	if (temp != NULL)
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new;
		new->next = NULL;
	}
	else
	{
		*alst = new;
		new->next = NULL;
	}
}

