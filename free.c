/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:49:52 by amouassi          #+#    #+#             */
/*   Updated: 2021/02/27 14:49:59 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	free_tab(char **s)
{
	int		i;

	i = 0;
	while(s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
}
