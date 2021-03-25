/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 13:41:51 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/03/25 16:18:18 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	get_line(t_token *token)
{
	int		check;
	char	*line;

	line = NULL;
	check = 0;
	int cp = 0;
	while(1337)
	{
		ft_putstr(MINISHELL);
		get_next_line(&line);
		check_quote(line, &check);
		if (!check)
			token = lexer_line(line);
		check = 0;
		free(line);
		line = NULL;
	}
}

int main(void)
{
	t_token *token;

	token = NULL;
	get_line(token);
	while (token)
	{
		// printf("|INDEX|\t|TYPES|\t[VALUES]\n");
		// printf("|%d|\t|%d|\t[%s]\n", token->index, token->type, token->value);
		token = token->next;
	}
}
