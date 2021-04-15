/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 17:02:55 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/15 09:25:42 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	redirection(t_symbol *smbl)
{
	if (smbl->great == ON)
		return (62);
	if (smbl->less == ON)
		return (60);
	if (smbl->d_great == ON)
		return (63);
	return (0);
}

char	*check_d_quote(t_symbol *smbl, char *line, int i)
{
	if (!count_back(line + (i - 1)))
	{
		if (smbl->pipe == ON)
			smbl->pipe = OFF;
		if (smbl->d_quote == OFF && smbl->s_quote == OFF)
			smbl->d_quote = ON;
		else if (smbl->d_quote == ON && smbl->s_quote == OFF)
			smbl->d_quote = OFF;
		else if (smbl->s_quote == ON)
			line[i] *= -1;
	}
	else if (smbl->d_quote == ON)
		line[i] *= -1;
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
		if (!count_back(line + (i - 1)))
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
	{
		line = check_semi_off(smbl, line, i);
		/* if (count_back(line + (i - 1)))
			line[i] *= -1;
		else
		if (redirection(smbl))
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
		} */
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
				ft_error(smbl, "3=>syntax error near unexpected token `;'");
		}
	}
	return (line);
}

char	*check_space(t_symbol *smbl, char *line, int i)
{
	if (smbl->d_quote == ON || smbl->s_quote == ON)
		line[i] *= -1;
	return (line);
}

char	*check_pipe_off(t_symbol *smbl, char *line, int i)
{
	if (count_back(line + (i - 1)))
		line[i] *= -1;
	else if (redirection(smbl))
	{
		ft_error(smbl, "1=>syntax error near unexpected token `|'");
		off_flags(smbl);
	}
	else
	{
		if (smbl->pipe == ON)
		{
			ft_error(smbl, "2=>syntax error near unexpected token `|'");
			smbl->pipe = OFF;
		}
		else if (smbl->semi == ON)
		{
			ft_error(smbl, "3=>syntax error near unexpected token `|'");
			off_flags(smbl);
		}
		else
			smbl->pipe = ON;
	}
	return (line);
}

char	*check_pipe(t_symbol *smbl, char *line, int i)
{
	if (smbl->d_quote == OFF && smbl->s_quote == OFF)
	{
		check_pipe_off(smbl, line, i);
		/* if (count_back(line + (i - 1)))
			line[i] *= -1;
		else if (redirection(smbl))
		{
			ft_error(smbl, "1=>syntax error near unexpected token `|'");
			off_flags(smbl);
		}
		else
		{
			if (smbl->pipe == ON)
			{
				ft_error(smbl, "2=>syntax error near unexpected token `|'");
				smbl->pipe = OFF;
			}
			else if (smbl->semi == ON)
			{
				ft_error(smbl, "3=>syntax error near unexpected token `|'");
				off_flags(smbl);
			}
			else
				smbl->pipe = ON;
		} */
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
			ft_error(smbl, "4=>syntax error near unexpected token `|'");
		}
	}
	return (line);
}

void	error_red(t_symbol *smbl, char *error, char c)
{
	if (c == 63)
		printf("%s%s `%s'%s\n", RED, error, ">>", WHITE);
	else
		printf("%s%s `%c'%s\n", RED, error, c, WHITE);
	smbl->error = 1;
}

char	*check_redirection(t_symbol *smbl, char *line, int i, int *type)
{
	if (smbl->d_quote == ON || smbl->s_quote == ON)
	{
		if (line[i + 1] == '>')
			line[i + 1] *= -1;
		line[i] *= -1;
	}
	else
	{
		if (redirection(smbl) == OFF)
			*type = ON;
		else
		{
			if (line[i + 1] == '>')
				error_red(smbl, "syntax error near unexpected token", 63);
			else
				error_red(smbl, "syntax error near unexpected token", line[i]);
		}
	}
	return (line);
}
