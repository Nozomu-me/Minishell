/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 17:02:55 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/02 22:55:40 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		redirection(t_symbol *smbl)
{
	if (smbl->great == ON)
		return (1);
	if (smbl->less == ON)
		return (1);
	if (smbl->d_great == ON)
		return (1);
	return (0);
}
/* 			1 		  */

char	*check_d_quote(t_symbol *smbl, char *line, int i)
{
	// printf("1=> |%s|\t|%c|\tR:|%d|\tS_:|%d|\t|%c|\n", line, line[i - 2], r, smbl->d_quote, line[i]);
	if (!count_back(line + (i - 1)))
	{
		if (smbl->d_quote == OFF && smbl->s_quote == OFF)
			smbl->d_quote = ON;
		else if (smbl->d_quote == ON && smbl->s_quote == OFF)
			smbl->d_quote = OFF;
		else if (smbl->s_quote == ON)
			line[i] *= -1;
	}
	else if (smbl->d_quote == ON)
		line[i] *= -1;
	// printf("2=> |%s|\t|%c|\tR:|%d|\tS_:|%d|\t|%c|\n\n", line, line[i - 2], r, smbl->d_quote, line[i]);
	return (line);
}

char	*check_s_quote(t_symbol *smbl, char *line, int i)
{
	if (smbl->s_quote == OFF && smbl->d_quote == OFF)
	{
			if (smbl->d_great == ON)
				smbl->d_great = OFF;
			if (smbl->great == ON)
				smbl->great = OFF;
			if (smbl->less == ON)
				smbl->less = OFF;
		if (count_back(line + (i - 1)))
			smbl->s_quote = ON;
	}
	else
	{
		if (smbl->s_quote == ON)
			smbl->s_quote = OFF;
		else if (smbl->d_quote == ON)
			line[i] *= -1;
	}
	return (line);
}

char	*check_semicolone(t_symbol *smbl, char *line, int i)
{
	if (smbl->d_quote == OFF && smbl->s_quote == OFF)
	{
		if (redirection(smbl) == ON)// || smbl->semi == ON)
			ft_error("SYntax error ';'", RED, WHITE);
		else
		{
			if (smbl->semi == ON)
			{
				ft_error("1SYntax error ';'", RED, WHITE);
				smbl->semi = OFF;
			}
			else
				smbl->semi = ON;
		}
	}
	else
	{
		if (smbl->d_quote == ON || smbl->s_quote == ON)
			line[i] *= -1;
		else
		{
			if (smbl->semi == OFF)
				smbl->semi = ON;
			else
			ft_error("1SYntax error ';'", RED, WHITE);
		}
	}
	return (line);
}

char	*check_pipe(t_symbol *smbl, char *line, int i)
{
	if (smbl->d_quote == OFF && smbl->s_quote == OFF)
	{
		if (redirection(smbl) == ON)// && smbl->pipe == ON)
			ft_error("SYntax error '|'", RED, WHITE);
		else
		{
			if (smbl->pipe == ON)
			{
				ft_error("SYntax error '|'", RED, WHITE);
				smbl->pipe = OFF;
			}
			else smbl->pipe = ON;
		}
	}
	else
	{
		if (smbl->d_quote == ON || smbl->s_quote == ON)
			line[i] *= -1;
		else
		{
			if (smbl->pipe == OFF)
				smbl->pipe = ON;
			else
			ft_error("SYntax error '|'", RED, WHITE);
		}
	}
	return (line);
}

char	*check_redirection(t_symbol *smbl, char *line, int i, int *type)
{
	if (smbl->d_quote == ON || smbl->s_quote == ON)
		line[i] *= -1;
	else
	{
		if(redirection(smbl) == OFF)
			*type = ON;
		else ft_error("SYntax error REDIRECTION", RED, WHITE);
	}
	return (line);
}
