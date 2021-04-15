/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 18:31:32 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/04/15 15:10:03 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	replace_searche(t_parse *parse, char *str, char *org, char *rep)
{
	while (*str)
	{
		if (ft_strnstr(str, org, ft_strlen(str)) == str)
		{
			strcpy(&parse->src_new[parse->src_i], rep);
			parse->src_i += parse->src_len1;
			str += parse->src_len2;
		}
		else
			parse->src_new[parse->src_i++] = *str++;
	}
}

char	*search_replace(t_parse *parse, char *str, char *org, char *rep)
{
	parse->src_count = 0;
	parse->src_len1 = ft_strlen(rep);
	parse->src_len2 = ft_strlen(org);
	while (str[parse->src_i] != '\0')
	{
		if (strstr(&str[parse->src_i], org) == &str[parse->src_i])
		{
			parse->src_count++;
			parse->src_i += parse->src_len2 - 1;
		}
		parse->src_i++;
	}
	parse->src_new = (char *)malloc(parse->src_i + parse->src_count
			*(parse->src_len1 - parse->src_len2) + 1);
	parse->src_i = 0;
	replace_searche(parse, str, org, rep);
	parse->src_new[parse->src_i++] = '\0';
	return (parse->src_new);
}
