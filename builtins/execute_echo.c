/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:08:18 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/19 22:05:03 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    execute_echo(char **cmd)
{
    int     i;
    int     check;

    i = 1;
    check = 0;
    while (cmd[i] != NULL)
    {
        if (ft_strcmp(cmd[i], "-n") == 0)
        {
            check = 1;
            break ;
        }
        i++;
    }
    i = 2;
    while (cmd[i] != NULL)
    {
        ft_putstr(cmd[i]);
        if (cmd[i + 1] != NULL)
            ft_putstr(" ");
        i++;
    }
    if (check == 0)
        ft_putstr("\n");
}