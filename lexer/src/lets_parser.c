/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lets_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 22:57:49 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/03/21 01:29:49 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	ft_error(char *str)
{
	ft_putendl_fd(str, 1);
}

void	check_line(t_token *token)
{
	t_bool brk;

	while (token)
	{
		if (token->type == NONE)
		{
			if (token->next->type == SEMI || token->next->type == PIPE)
			{
				puts("\t\t\t\tNONE");
				ft_error("Syntax error");
			}
		}
		else if (token->type >= G_S_QUOTE && token->type <= D_QUOTE)
		{
			if (token->next->type != WORD)
			{
				puts("\t\t\t\tQuote");
				ft_error("syntax error\n");
			}
		}
		else if (token->type == SEMI)
		{
			if (token->value[1] == ';' || token->next->type == PIPE
			|| token->next->type == SEMI)
			{
				puts("\t\t\t\tSEMI");
				ft_error("Syntax error");
			}
		}
		else if (token->type == PIPE)
		{
			if (token->next->type == SEMI || token->next->type == PIPE
			|| token->next->type == END || token->value[1] == '|')
			{
				puts("\t\t\t\tPIPE");
				ft_error("Syntax error");
			}
		}
		token = token->next;
	}
}
