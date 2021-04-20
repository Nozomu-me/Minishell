/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:22:04 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/20 16:29:12 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cflist	*lstnew_cmd(char *v_cmd, int type)
{
	t_cflist	*new;

	new = (t_cflist *)malloc(sizeof(t_cflist));
	if (new)
	{
		new->name = ft_strdup(v_cmd);
		new->type = type;
		new->next = NULL;
	}
	return (new);
}

void	lstadd_cmd(t_cflist **alst, t_cflist *new)
{
	t_cflist	*list;

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

t_cflist	*file_lst_new(void *filename, int filetype)
{
	t_cflist	*head;

	head = (t_cflist *)malloc(sizeof(t_cflist));
	if (head == NULL)
		return (NULL);
	head->name = ft_strdup(filename);
	head->type = filetype;

	head->next = NULL;
	return (head);
}

void	file_lstadd_back(t_cflist **alst, t_cflist *new)
{
	t_cflist	*temp;

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

