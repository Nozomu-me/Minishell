/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_new_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:37:04 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/14 17:32:01 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ret(char *line, int i)
{
	char *new;
	int j;

	j = -1;
	new = malloc(sizeof(char) * i + 1);
	while (++j < i)
		new[j] = line[j];
	new[j] = 0;
	return (new);
}

char	*check_f_cmd(t_parse *parse, char *line)
{
	int i;
	int j;
	int cp;

	i = 0;
	j = -1;
	cp = 0;
	while (line[++j])
	{
		
		if (parse->smbl->d_quote == OFF && parse->smbl->s_quote == OFF)
		{
			if (line[j] == '\\')
			{
				cp++;
				line[i++] = line[++j];
			}
			else
			{
				if (line[j] == '"' && cp % 2 == 0)
					parse->smbl->d_quote = ON;
				else if (line[j] == '\'' && cp % 2 == 0)
					parse->smbl->s_quote = ON;
				else
					line[i++] = line[j];
			}
		}
		else
		{
			if (parse->smbl->d_quote == ON)
			{
				if (line[j] == '"')
					parse->smbl->d_quote = OFF;
				else if (line[j] == '\\' && line[j + 1] == '\\')
					line[i++] = line[++j];
				else if (line[j] == '\\' && line[j + 1] < 0 && line[j + 1] != '\'' * -1)
					line[i++] = line[++j];
				else
					line[i++] = line[j];
			}
			else if (parse->smbl->s_quote == ON)
			{
				while (line[j] != '\'')
					line[i++] = line[j++];
				parse->smbl->s_quote = OFF;
			}
		}
		if (line[j] != '\\')
			cp = 0;
	}
	line[i] = 0;
	i = -1;
	while (line[++i])
		if (line[i] < 0)
			line[i] *= -1;
	return (line);
}

// char	*check_f_cmd(t_parse *parse, char *line)
// {
// 	char 	*new;
// 	int		i;
// 	int 	cp;

// 	new = line;
// 	i = 0;
// 	cp = 0;
// 	while (*new)
// 	{
// 		if (parse->smbl->d_quote == OFF && parse->smbl->s_quote == OFF)
// 		{
// 			if (*new == '\\')
// 			{
// 				cp++;
// 				line[i++] = *(++new);
// 			}
// 			else
// 			{
// 				if (*new == '"' && cp % 2 == 0)
// 					parse->smbl->d_quote = ON;
// 				else if (*new == '\'' && cp % 2 == 0)
// 					parse->smbl->s_quote = ON;
// 				else
// 					line[i++] = *new;
// 				cp = 0;
// 			}
// 		}
// 		else
// 		{
// 			if (parse->smbl->d_quote == ON)
// 			{
// 				if (*new == '"')
// 					parse->smbl->d_quote = OFF;
// 				else if (*new == '\\' && new[1] == '\\')
// 					line[i++] = *(++new);
// 				else if (*new == '\\' && new[1] < 0)
// 					line[i++] = *(++new);
// 				else
// 					line[i++] = *new;
// 			}
// 			else if (parse->smbl->s_quote == ON)
// 			{
// 				while (*new != '\'')
// 					line[i++] = *new++;
// 				parse->smbl->s_quote = OFF;
// 			}
// 		}
// 		if (*new != '\\')
// 			cp = 0;
// 		new++;
// 	}
// 	line[i] = 0;
// 	i = -1;
// 	while (line[++i])
// 		if (line[i] < 0)
// 			line[i] *= -1;
// 	return (line);
// }
