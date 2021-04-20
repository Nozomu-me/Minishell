/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 21:48:59 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/18 13:32:47 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     fd_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

void    delete(char **cmdline, t_termcap *term)
{
	char	*tmp;

	if (term->c > 0)
	{
		tputs(tgoto(tgetstr("LE", NULL),0, 1), 0, fd_putchar);
		tputs(tgoto(tgetstr("ce", NULL),0, 1), 0, fd_putchar);
		if (((term->c + 11) % term->win.ws_col) == 0)
		{
			tputs(tgoto(tgetstr("up", NULL),0, 1), 0, fd_putchar);
			tputs(tgoto(tgetstr("RI", NULL),0, term->win.ws_col), 0, fd_putchar);
			tputs(tgoto(tgetstr("ce", NULL),0, 1), 0, fd_putchar);
		}
	}
	if (term->c > 0)
		term->c -= 1;
	tmp = ft_strdup(*cmdline);
	free(*cmdline);
	*cmdline = ft_substr(tmp, 0, term->c);
	if (term->prevlen > 0)
		term->prevlen -= 1;
	free(tmp);
}

void	exec_ctrld(char *cmdline, t_termcap *term)
{
	if ((cmdline == NULL || (cmdline != NULL && ft_strlen(cmdline) == 0)))
	{
		ft_putstr_fd("exit\n", 1);
		exit(EXIT_SUCCESS);
	}
}

int		termcap(t_termcap *term, char **cmdline)
{
	if (term->buffer[0] == DELETE)
	{
		if (*cmdline != NULL)
			delete(cmdline, term);
	}
	else if(term->buffer[0] == CTRLD)
		exec_ctrld(*cmdline, term);
	else if (term->buffer[0] == LEFTRIGHT)
		;
	else if (term->buffer[0] == ENTER)
	{
		if (*cmdline != NULL)
			term->c += ft_strlen(*cmdline);
		return (1);
	}
	return (0);
}

void	get_cmdline(t_termcap *term, char **cmdline)
{
	char	*tmp;

	if (*cmdline == NULL)
		*cmdline = ft_strdup(term->buffer);
	else
	{
	    tmp = *cmdline;
		*cmdline = ft_strjoin(*cmdline, term->buffer);
	    free(tmp);
	}
	term->c += 1;
	ft_putstr_fd(term->buffer,1);
}