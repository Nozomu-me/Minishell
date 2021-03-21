/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 00:26:46 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/03/21 01:29:59 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

t_bool	check_symbol(char c)
{
	if (c == ';')
		return (TRUE);
	else if (c == '|')
		return (TRUE);
	else if (c == '>')
		return (TRUE);
	else if (c == '<')
		return (TRUE);
	return (FALSE);
}

char	*get_redirection(t_token *token, int *index, char *line)
{
	if (*line == '>')
	{
		if (line[1] == '>')
		{
			ft_lstadd_back(&token, ft_lstnew(++(*index), D_QUOTE, ">>"));
			++line;
		}
		else
			ft_lstadd_back(&token, ft_lstnew(++(*index), G_S_QUOTE, ">"));
	}
	else if (*line == '<')
		ft_lstadd_back(&token, ft_lstnew(++(*index), L_S_QUOTE, "<"));
	return (line);
}

char	*get_symbole(t_token *token, int *index, char *line)
{
	if (*line == ';')
	{
		if (line[1] == ';')
		{
			ft_lstadd_back(&token, ft_lstnew(++(*index), SEMI, ";;"));
			++line;
		}
		else
			ft_lstadd_back(&token, ft_lstnew(++(*index), SEMI, ";"));
	}
	else if (*line == '|')
	{
		if (line[1] == '|')
		{
			ft_lstadd_back(&token, ft_lstnew(++(*index), PIPE, "||"));
			++line;
		}
		else
			ft_lstadd_back(&token, ft_lstnew(++(*index), PIPE, "|"));
	}
	else
		line = get_redirection(token, index, line);
	return (line);
}

char	*get_word(t_token *token, int *index, char *line)
{
	int i;
	int j;
	char *word;

	i = 0;
	j = -1;
	while (line[i] && !check_symbol(line[i]))
		i++;
	word = malloc(sizeof(char) * i);
	while (++j < i)
		word[j] = line[j];
	word[j] = '\0';
	ft_lstadd_back(&token, ft_lstnew(++(*index), WORD, word));
	return (line + --i);
}

void	check_token(t_token *token, char *line)
{
	int index;

	index = 0;
	while (*line)
	{
		if (check_symbol(*line))
			line = get_symbole(token, &index, line);
		else if (!check_symbol(*line))
			line = get_word(token, &index, line);
		line++;
	}
	ft_lstadd_back(&token, ft_lstnew(-1, END, "END"));
}

t_token		*lexer_line(char *line)
{
	t_token *token;
	token = NULL;
	token = ft_lstnew(0, NONE, "(null)");
	check_token(token, line);
	check_line(token);
	return (token);
}
