/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 18:50:40 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/16 13:44:42 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	is_charset(char c, char *charset)
{
	size_t	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static size_t	get_start_index(char const *s, char *set)
{
	size_t		start;

	start = 0;
	while (s[start] != '\0' && is_charset(s[start], set))
		start++;
	return (start);
}

static size_t	get_end_index(char const *s, char *set, size_t len)
{
	while (len && is_charset(s[len], set))
		len--;
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*str;
	size_t		start;
	size_t		end;

	if (!s1)
		return (NULL);
	start = get_start_index(s1, (char *)set);
	end = get_end_index(s1, (char *)set, ft_strlen(s1) - 1);
	if (end >= start)
	{
		str = malloc(end + 2 - start);
		if (str)
		{
			ft_memcpy(str, &s1[start], end + 1 - start);
			str[end + 1 - start] = '\0';
		}
	}
	else
	{
		str = malloc(1);
		if (str)
			str[0] = '\0';
	}
	return (str);
}
