/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 13:41:51 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/03/22 18:14:55 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	get_line(t_token *token)
{
	int		r;
	char	*line;

	line = NULL;
	ft_putstr("\e[1;32m$minishel\033[1;34m=>\033[0m");
	while(1337)
	{
		get_next_line(&line);
		token = lexer_line(line);
		while (token)
		{
			printf("|%d|\t|%d|\t[%s]\n", token->index, token->type, token->value);
			token = token->next;
		}
		ft_putstr("\n\e[1;32m$minishel\033[1;34m=>\033[0m");
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
		printf("|%d|\t|%d|\t[%s]\n", token->index, token->type, token->value);
		token = token->next;
	}
}
