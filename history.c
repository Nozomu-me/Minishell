/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 12:39:58 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/21 21:59:31 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    uphistory(t_termcap *term, t_list **history, char **cmdline)
{
    char **hist_tab;

	// printf("|line=%s|",*cmdline);
	// if (*cmdline != NULL)
	// {
	// 	tputs(tgoto(tgetstr("LE", NULL),0, term->prevlen), 0, fd_putchar);
	// 	tputs(tgoto(tgetstr("ce", NULL),0, term->prevlen), 0, fd_putchar);
	// }
    if (term->lstsize != 0)
	{
		if (term->prevlen != 0)
		{
			tputs(tgoto(tgetstr("LE", NULL),0, term->prevlen), 0, fd_putchar);
			tputs(tgoto(tgetstr("ce", NULL),0, term->prevlen), 0, fd_putchar);
		}
		hist_tab = list_to_tabl(*history);
		if (term->histpos != 0)
			term->histpos -=1;
		ft_putstr_fd(hist_tab[term->histpos], 1);
		term->prevlen = ft_strlen(hist_tab[term->histpos]);
		if (*cmdline != NULL)
			free(*cmdline);
		if (hist_tab[term->histpos] != NULL)
		{
			*cmdline = ft_strdup(hist_tab[term->histpos]);
			term->c = ft_strlen(*cmdline);
		}
        free_tabl(hist_tab);
	}
}

void    delete_dhist(t_termcap *term, char **cmdline)
{
	// fprintf(stderr,"delete\n");
    tputs(tgoto(tgetstr("LE", NULL),0, term->prevlen), 0, fd_putchar);
	tputs(tgoto(tgetstr("ce", NULL),0, term->prevlen), 0, fd_putchar);
    free(*cmdline);
	*cmdline = NULL;
}

void    downhistory(t_termcap *term, t_list **history, char **cmdline)
{
    char **hist_tab;

    if ((term->prevlen != 0 && term->histpos != term->lstsize)
		|| (term->prevlen != 0 && term->histpos == term->lstsize 
		&& term->save != NULL))
        delete_dhist(term, cmdline);
	hist_tab = list_to_tabl(*history);
	if (term->histpos < term->lstsize)
		term->histpos +=1;
	if (term->histpos < term->lstsize)
	{
		ft_putstr_fd(hist_tab[term->histpos], 1);
		term->prevlen = ft_strlen(hist_tab[term->histpos]);
	}
	if (term->histpos == term->lstsize)
	{
		if (term->save != NULL)
		{
			// if (*cmdline != NULL)
			ft_putstr(term->save);
			*cmdline = ft_strdup(term->save);
			// fprintf(stderr ,"cmdline=%s\n", *cmdline);
			term->prevlen = ft_strlen(term->save);
		}
		else 
			term->prevlen = 0;
	}
	if (hist_tab[term->histpos] != NULL)
	{
        free(*cmdline);
		*cmdline = ft_strdup(hist_tab[term->histpos]);
		term->c = ft_strlen(*cmdline);
	}
    free_tabl(hist_tab);
}