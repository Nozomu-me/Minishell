/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_semi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 10:27:30 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/20 13:13:44 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_semi_off(t_symbol *smbl, char *line, int i)
{
	if (count_back(line + (i - 1)))
		line[i] *= -1;
	else if (redirection(smbl))
	{
		ft_error(smbl, "1=>syntax error near unexpected token `;'");
		off_flags(smbl);
	}
	else
	{
		if (smbl->semi == ON)
		{
			ft_error(smbl, "2=>syntax error near unexpected token `;'");
			smbl->semi = OFF;
		}
		else if (smbl->pipe == ON)
		{
			ft_error(smbl, "3=>syntax error near unexpected token `;'");
			off_flags(smbl);
		}
		else
			smbl->semi = ON;
	}
	return (line);
}

char	*check_semicolone(t_symbol *smbl, char *line, int i)
{
	if (smbl->d_quote == OFF && smbl->s_quote == OFF)
		line = check_semi_off(smbl, line, i);
	else
	{
		if (smbl->d_quote == ON || smbl->s_quote == ON)
			line[i] *= -1;
		else
		{
			if (smbl->semi == OFF)
				smbl->semi = ON;
			else
				ft_error(smbl, "3=>syntax error near unexpected token `;'");
		}
	}
	return (line);
}

void	ft_error_pipe_semi(t_symbol *smbl, char *str)
{
	ft_error(smbl, str);
	off_flags(smbl);
}

char	*check_pipe_off(t_symbol *smbl, char *line, int i)
{
	if (count_back(line + (i - 1)))
		line[i] *= -1;
	else if (redirection(smbl))
		ft_error_pipe_semi(smbl, "syntax error near unexpected token `|'");
	else
	{
		if (smbl->pipe == ON)
		{
			ft_error(smbl, "syntax error near unexpected token `|'");
			smbl->pipe = OFF;
		}
		else if (smbl->semi == ON)
			ft_error_pipe_semi(smbl, "syntax error near unexpected token `|'");
		else
		{
			smbl->pipe = ON;
			if (smbl->already_pipe == 0)
				smbl->already_pipe = 1;
			else
				smbl->already_pipe = 0;
		}
	}
	return (line);
}

char	*check_pipe(t_symbol *smbl, char *line, int i)
{
	if (smbl->d_quote == OFF && smbl->s_quote == OFF)
		check_pipe_off(smbl, line, i);
	else
	{
		if (smbl->d_quote == ON || smbl->s_quote == ON)
			line[i] *= -1;
		else
		{
			if (smbl->pipe == OFF)
				smbl->pipe = ON;
			else
				ft_error(smbl, "4=>syntax error near unexpected token `|'");
		}
	}
	return (line);
}

int	check_flags(t_symbol *smbl)
{
	int	sum;

	sum = smbl->d_great + smbl->less + smbl->great + smbl->semi + smbl->pipe;
	return (sum);
}
