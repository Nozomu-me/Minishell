/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 22:41:40 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/03/24 23:11:49 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

char	*scape_space(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	return line;
}

void	semi_or_pipe_line(char *line)
{
	// line = scape_space(line);
	// if ((*line == ';' || *line == '|') && (line = scape_space(line)))
	// 	ft_error("Syntax error", RED, WHITE);
	while (*line)
	{
		line = scape_space(line);
		if ((*line == ';' || *line == '|') && (line = scape_space(line)))
			ft_error("Syntax error", RED, WHITE);
		line++;
	}
}
