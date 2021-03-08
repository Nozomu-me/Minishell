/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 10:30:00 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/03/07 15:17:57 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int		count_word(char *str)
{
	int i;
	int word;
	int pos;

	word = 0;
	i = 0;
	pos = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] <= '=')
			pos = 0;
		else
		{
			if (pos == 0)
				word++;
			pos = 1;
		}
		i++;
	}
	return (word);
}

char	*write_word(char *str, int *n)
{
	int		i;
	int		sp;
	int		ch;
	char	*word;

	i = *n;
	while (str[i] < '!')
		i++;
	ch = i;
	while (str[i] > ' ')
		i++;
	sp = i;
	word = (char *)malloc(sizeof(char) * (sp - ch + 1));
	*n = i;
	i = 0;
	while (ch < sp)
	{
		word[i] = str[ch];
		ch++;
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *str)
{
	int		i;
	int		count;
	char	**rst;
	int 	cnt_word;

	cnt_word = count_word(str);
	rst = (char**)malloc(sizeof(char*) * cnt_word + 1);
	i = 0;
	count = 0;
	while (count < cnt_word)
	{
		rst[count] = write_word(str, &i);
		count++;
	}
	rst[count] = 0;
	return (rst);
}
