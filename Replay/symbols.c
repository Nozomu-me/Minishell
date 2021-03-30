/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdel-ke <abdel-ke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 17:02:55 by abdel-ke          #+#    #+#             */
/*   Updated: 2021/03/29 18:47:53 by abdel-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*check_d_quote(t_symbol *smbl, char *line)
{
	if (count_back(line))
	{
		if (smbl->d_quote == OFF && smbl->s_quote == OFF)
			smbl->d_quote = ON;
		else if (smbl->d_quote == ON && smbl->s_quote == OFF)
			smbl->d_quote = OFF;
	}
	if (smbl->s_quote == ON)
		*line *= -1;
	return (line);
}

char	*check_s_quote(t_symbol *smbl, char *line)
{
	if (smbl->s_quote == ON)
		smbl->s_quote = OFF;
	else if (smbl->s_quote == OFF && count_back(line))
		if (smbl->d_quote == OFF)
			smbl->s_quote = ON;
	if (smbl->d_quote == OFF)
		*line *= -1;
	return (line);
}
