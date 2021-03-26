/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 21:27:11 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/26 12:09:03 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void sig_handler(int sig)
{
	if(sig == SIGINT)
	{
		// status = 131;
		ft_putstr("\b\b  \b\b\n\033[33mminishell\033[0m\033[32m~$\033[0m ");
	}
	if (sig == SIGQUIT)
	{
		// status = 132;
		ft_putstr("\b\b  \b\b");
	}
}