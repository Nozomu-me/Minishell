/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 17:02:55 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/03/31 15:15:28 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*check_d_quote(t_symbol *smbl, char *line)
{
	if (count_back(line))
	{
		if (smbl->d_quote == OFF && smbl->s_quote == OFF)
			smbl->d_quote = ON;
		else if (smbl->d_quote == ON && smbl->s_quote == OFF)
			smbl->d_quote = OFF;
	}
	if (smbl->s_quote == ON)
		*line *= -1;
	return (line);
}

char	*check_s_quote(t_symbol *smbl, char *line)
{
	if (smbl->s_quote == ON)
		smbl->s_quote = OFF;
	else if (smbl->s_quote == OFF && smbl->d_quote == OFF)
		if (count_back(line))
			smbl->s_quote = ON;
	if (smbl->d_quote == OFF)
		*line *= -1;
	return (line);
}

char	*check_semicolone(t_symbol *smbl, char *line)
{
	if (smbl->d_quote == OFF && smbl->s_quote == OFF)
		if (redirection(line) == ON || smbl->semi == ON)
			ft_error("SYntax error ';'", RED, WHITE);
	else
	{
		if (smbl->d_quote == ON || smbl->s_quote == ON)
			*line *= -1;
		else
			smbl->semi = ON;
	}
}

char	*check_pipe(t_symbol *smbl, char *line)
{
	if (smbl->d_quote == OFF && smbl->s_quote == OFF)
		if (redirection(line) == ON || smbl->pipe == ON)
			ft_error("SYntax error ';'", RED, WHITE);
	else
	{
		if (smbl->d_quote == ON || smbl->s_quote == ON)
			*line *= -1;
		else
			smbl->pipe = ON;
	}
}

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

char	*check_redirection(t_symbol *smbl, char *line)
{
	if (smbl->d_quote == ON || smbl->s_quote == ON)
		*line *= -1;
	else if(redirection(line) == OFF)
		;
	return (line);
}