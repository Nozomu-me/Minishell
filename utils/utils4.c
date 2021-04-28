/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:51:25 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/28 00:37:02 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fd_put(int c)
{
	write(1, &c, 1);
	return (0);
}

int	check_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*get_export_value(char *name)
{
	int		i;
	char	*value;

	i = 0;
	while (name[i] != '\0')
	{
		if (name[i] == '=')
			break ;
		i++;
	}
	value = ft_substr(name, i + 1, ft_strlen(name) - i + 2);
	return (value);
}

void	print_value(char *value, int fd)
{
	int	i;

	i = 0;
	while (value[i] != '\0')
	{
		if (value[i] == '\"')
			ft_putchar_fd('\\', fd);
		ft_putchar_fd(value[i], fd);
		i++;
	}	
}

void	print_export(t_list *export, int fd)
{
	t_list		*tmp;
	char		**split;
	char		*value;

	tmp = export;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->content, "_=", 2) != 0)
		{
			split = ft_split(tmp->content, '=');
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(split[0], fd);
			if (check_valid(tmp->content) == 1)
			{
				ft_putstr_fd("=\"", fd);
				value = get_export_value(tmp->content);
				print_value(value, fd);
				ft_putstr_fd("\"\n", fd);
				free(value);
			}
			else
				ft_putchar_fd('\n', fd);
			free_tabl(split);
		}
		tmp = tmp->next;
	}
}
