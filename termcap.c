/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 21:48:59 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/27 23:52:36 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete(char **cmdline, t_termcap *term)
{
	char	*tmp;
	char	*tmp2;

	if (term->c > 0)
	{
		tputs(tgoto(tgetstr("LE", NULL), 0, 1), 0, fd_put);
		tputs(tgoto(tgetstr("ce", NULL), 0, 1), 0, fd_put);
		if (((term->c + 12) % term->win.ws_col) == 0)
		{
			tputs(tgoto(tgetstr("up", NULL), 0, 1), 0, fd_put);
			tputs(tgoto(tgetstr("RI", NULL), 0, term->win.ws_col), 0, fd_put);
			tputs(tgoto(tgetstr("ce", NULL), 0, 1), 0, fd_put);
		}
	}
	if (term->c > 0)
		term->c -= 1;
	if (term->save != NULL && ft_strcmp(term->save, *cmdline) == 0)
	{
		tmp2 = ft_strdup(term->save);
		free(term->save);
		term->save = ft_substr(tmp2, 0, ft_strlen(tmp2) - 1);
		free(tmp2);
	}
	tmp = ft_strdup(*cmdline);
	free(*cmdline);
	*cmdline = ft_substr(tmp, 0, term->c);
	free(tmp);
	tmp = NULL;
	if (term->prevlen > 0)
		term->prevlen -= 1;
}

void	exec_ctrld(char *cmdline)
{
	if ((cmdline == NULL || (cmdline != NULL && ft_strlen(cmdline) == 0)))
	{
		ft_putstr_fd("exit\n", 1);
		exit(EXIT_SUCCESS);
	}
}

int	termcap(t_termcap *term, char **cmdline)
{
	if (term->buffer[0] == DELETE)
	{
		if (*cmdline != NULL)
			delete(cmdline, term);
	}
	else if (term->buffer[0] == CTRLD)
		exec_ctrld(*cmdline);
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

void	help_get_cmdline(t_termcap *term, char **cmdline, char *tmp_save)
{
	char	*tmp;

	tmp = *cmdline;
	*cmdline = ft_strjoin(*cmdline, term->buffer);
	if (*cmdline != NULL)
	{
		term->check = 0;
		tmp_save = term->save;
		term->save = ft_strdup(*cmdline);
		if (tmp_save != NULL)
			free(tmp_save);
	}
	free(tmp);
}

void	get_cmdline(t_termcap *term, char **cmdline)
{
	char	*tmp_save;

	tmp_save = NULL;
	if (*cmdline == NULL)
	{
		*cmdline = ft_strdup(term->buffer);
		if (*cmdline != NULL)
		{
			term->check = 0;
			tmp_save = term->save;
			term->save = ft_strdup(*cmdline);
			if (tmp_save != NULL)
				free(tmp_save);
		}
	}
	else
		help_get_cmdline(term, cmdline, tmp_save);
	term->c += 1;
	ft_putstr_fd(term->buffer, 1);
}
