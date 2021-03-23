/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lets_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 22:57:49 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/03/22 18:12:38 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	ft_error(char *str, char *first_color, char *second_color)
{
	ft_putstr(first_color);
	ft_putendl_fd(str, 1);
	ft_putstr(second_color);
}

void	check_quote(char *line)
{
	int cp;

	while (*line)
	{
		if (*line == '"' && line[-1] != '\\')
			cp++;
		line++;
	}
}

void	check_line(t_token *token)
{
	t_bool brk;

	while (token)
	{
		if (token->type >= G_S_QUOTE && token->type <= D_QUOTE)
		{
			if (token->next->type != WORD)
				ft_error("syntax error near unexpected token `newline'", red, white);
		}
		else if (token->type == SEMI)
		{
			if (token->value[1] == ';' || token->next->type == PIPE
			|| token->next->type == SEMI)
				ft_error("syntax error near unexpected token `;;'", red, white);
		}
		else if (token->type == PIPE)
		{
			if (token->next->type == SEMI || token->next->type == PIPE
			|| token->next->type == END || token->value[1] == '|')
				ft_error("syntax error near unexpected token `||'", red, white);
		}
		token = token->next;
	}
}
