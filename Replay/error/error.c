/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:30:33 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/13 15:56:13 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	initial_symbol(t_symbol *sbl)
{
	sbl->pipe = OFF;
	sbl->semi = OFF;
	sbl->s_quote = OFF;
	sbl->d_quote = OFF;
	sbl->great = OFF;
	sbl->less = OFF;
	sbl->d_great = OFF;
	sbl->error = OFF;
}

void	off_flags(t_symbol *smbl)
{
	smbl->d_great = 0;
	smbl->less = 0;
	smbl->great = 0;
	smbl->semi = 0;
	smbl->pipe = 0;
}

void	ft_error(t_symbol *smbl, char *str)
{
	ft_putstr_fd(RED, 1);
	ft_putendl_fd(str, 1);
	ft_putstr_fd(WHITE, 1);
	smbl->error = ON;
}

int	check_flags(t_symbol *smbl)
{
	int	sum;

	sum = smbl->d_great + smbl->less + smbl->great + smbl->semi + smbl->pipe;
	return (sum);
}

int	count_back(char *line)
{
	int	cp;

	cp = 0;
	while (*line == '\\')
	{
		cp++;
		line--;
	}
	if (cp % 2 == 0)
		return (0);
	return (1);
}

char	*check_symbols(t_symbol *smbl, char *line, int i)
{
	while (line[++i] && !smbl->error)
	{
		if (line[i] == '"')
			line = check_d_quote(smbl, line, i);
		else if (line[i] == '\'')
			line = check_s_quote(smbl, line, i);
		else if (line[i] == '|')
			line = check_pipe(smbl, line, i);
		else if (line[i] == ';')
			line = check_semicolone(smbl, line, i);
		else if (line[i] == '>' && line[i + 1] == '>')
			line = check_redirection(smbl, line, i++, &smbl->d_great);
		else if (line[i] == '>')
			line = check_redirection(smbl, line, i, &smbl->great);
		else if (line[i] == '<')
			line = check_redirection(smbl, line, i, &smbl->less);
		else if (line[i] == ' ')
			line = check_space(smbl, line, i);
		else if (line[i] == '$')
			line = ft_turn_dollar(smbl, line, i);
		else if (check_flags(smbl) && line[i] != ' ')
			off_flags(smbl);
	}
	return (line);
}
/*check " & ' if is closed or note & change ; | to non printable characters */

char	*partition_stage(t_symbol *smbl, char *line)
{
	int	i;

	i = 0;
	initial_symbol(smbl);
	line = ft_strtrim(line, " ");
	if (line[0] == '|')
		ft_error(smbl, "bash: syntax error near unexpected token `|'");
	if (line[0] == ';')
		ft_error(smbl, "bash: syntax error near unexpected token `;'");
	line = check_symbols(smbl, line, -1);
	if (!smbl->error && (smbl->d_great || smbl->d_quote || smbl->s_quote
			|| smbl->pipe || smbl->great || smbl->less))
		ft_error(smbl, "syntax error near unexpected token `newline'");
	return (line);
}
