/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:31:56 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/14 14:24:45 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

// int		skip_spaces(char *line)
// {
// 	int i;

// 	i = 0;
// 	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
// 		i++;
// 	return (i);
// }

// int		skip_sp_red(char *line)
// {
// 	int i;

// 	i = 0;
// 	while (line[i] && line[i] != ' '  && line[i] != '\t'  && line[i] != '>'
// 	 && line[i] != '<')
// 		i++;
// 	return (i);
// }

/* 
int	red_read_write(char **line, char **args, char **file, int *i)
{
	int j;

	j = 0;
	*args = ft_substr2(*line, 0, (*i));
	j = (*i);
	if (*line[(*i) + 1] == '>')
		(*i)++;
	(*i)++;
	(*i) += skip_spaces(*line + (*i));
	(*i) += skip_sp_red(*line + (*i));
	*file = ft_substr2(*line, j, (*i));
	return (*i);
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
		// j = red_read_write(&line, &args, &file, &i);
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
	if (j != 0)
		return (ft_strjoin(args, file));
	return line;
}
 */