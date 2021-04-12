/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:31:56 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/12 18:32:09 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		skip_spaces(char *line)
{
	int i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (i);
}

int		skip_sp_red(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != ' '  && line[i] != '\t'  && line[i] != '>'
	 && line[i] != '<')
		i++;
	return (i);
}

char	*ft_substr2(char *s, unsigned int start, size_t len)
{
    size_t	i;
    char	*str;

    if (!s)
        return (NULL);
    if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
        return (NULL);
    i = 0;
    while (start < len)
        str[i++] = s[start++];
    str[i] = '\0';
    return (str);
}

char	*sort_redirection(char *line)
{
	int i;
	int j;
	char *file;
	char *args;

	i = 0;
	j = 0;
	args = NULL;

	while (line[i] && line[i] != '>' && line[i] != '<')
		i++;
	if (line[i] == '>' || line[i] == '<')
	{
		args = ft_substr2(line, 0, i);
		j = i;
		if (line[i + 1] == '>')
			i++;
		i++;
		i += skip_spaces(line + i);
		i += skip_sp_red(line + i);
		file = ft_substr2(line, j, i);
		j = i;
	}
	while (line[i])
	{
		i += skip_spaces(line + i);
		if (line[i] != '>' && line[i] != '<')
		{
			i += skip_spaces(line + i);
			i += skip_sp_red(line + i);
			args = ft_strjoin(args, ft_substr2(line, j, i));
			j = i;
		}
		else
		{
			if (line[i + 1] == '>')
				i ++;
			i++;
			i += skip_spaces(line + i);
			i += skip_sp_red(line + i);
			file = ft_strjoin(file, ft_substr2(line, j, i));
			j = i;
		}
		i++;
	}
	if (j != 0)// && args && file)
	{
		return (ft_strjoin(args, file));
	}
	return line;
}
