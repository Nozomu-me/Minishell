/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 21:47:20 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/21 21:59:21 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_termcap(t_termcap *term, t_list **history, char **cmdline)
{
	ioctl(0, TIOCGWINSZ, &term->win);
	term->c = 0;
	term->lstsize = ft_lstsize(*history);
	*cmdline = NULL;
	term->histadd = NULL;
	term->prevlen = 0;
	term->histpos = term->lstsize;
}

int		check_buffer(t_termcap *term, t_list **history, char **cmdline)
{
	if (!strcmp(term->buffer, UP))
	{
		// fprintf(stderr, "check=%d\n", term->check);
		// fprintf(stderr ,"save=%s\n",term->save);
		if (term->save != NULL && term->check == 0)
		{
			term->check = 1;
			tputs(tgoto(tgetstr("LE", NULL),0, ft_strlen(term->save)), 0, fd_putchar);
			tputs(tgoto(tgetstr("ce", NULL),0, ft_strlen(term->save)), 0, fd_putchar);
		}
		uphistory(term, history, cmdline);
	}
	else if (!strcmp(term->buffer, DOWN))
	{
		downhistory(term, history, cmdline);
	}
	else if (term->buffer[0] == DELETE || term->buffer[0] == CTRLD
		|| term->buffer[0] == LEFTRIGHT || term->buffer[0] == ENTER)
	{
		if (termcap(term, cmdline) == 1)
		{
			return (1) ;	
		}
	}
	else
		get_cmdline(term, cmdline);
	return (0);
}

void	readline(t_mini *mini, char **cmdline, t_list **history)
{
	t_termcap term;

	term.save = NULL;
	term.check = 0;
	init_termcap(&term, history, cmdline);
	while(1)
	{
		term.buffer[0] = '\0';
		term.ret = read(0, term.buffer, 4);
		if (g_check.exit_status == -1)
		{
			g_check.exit_status = 1;
			free(*cmdline);
			*cmdline = NULL;
		}
		term.buffer[term.ret] = '\0';
		if (check_buffer(&term, history, cmdline) == 1)
			break ;
	}
	if (*cmdline != NULL && ft_strlen(*cmdline) != 0)
		ft_lstadd_back(history, ft_lstnew(ft_strdup(*cmdline)));
}