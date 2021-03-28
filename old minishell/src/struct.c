/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:22:04 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/03/25 18:47:55 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

t_token		*ft_lstnew(int index, t_token_type type, char *value)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	if (new)
	{
		new->index = index;
		new->type = type;
		new->value = value;
		new->next = NULL;
	}
	return (new);
}

void	ft_lstadd_back(t_token **alst, t_token *new)
{
	t_token *list;

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
