/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:08:18 by amouassi          #+#    #+#             */
/*   Updated: 2021/03/25 19:09:45 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
static char  *check_valid(char *str)
{
    int     i;
    int     len;
    char    *ret;

    ret = NULL;
    len = ft_strlen(str) - 2;
    if (len > 0)
    {
        ret = malloc(len*sizeof(char));
        i = 2;
        while(str[i] != '\0')
        {
            ret[i - 2] = str[i];
            i++;
        }
    }
    return (ret);
        
}

void    execute_echo(char **cmd, t_minishell *mini)
{
    int     i;
    int     b;
    char    *check;
    char    *str;

    i = 1;
    b = 0;
    while (cmd[i] != NULL && ft_strncmp(cmd[i], "-n", 2) == 0)
    {
        b = 1;
        i++;
    }
    while (cmd[i] != NULL)
    {
        if (ft_strncmp(cmd[i], "$?",2) == 0)
        { 
            str = ft_itoa(mini->glob.exit_status);
           ft_putstr(str);
           check = check_valid(cmd[i]);
           if (check != NULL)
                ft_putstr(check);
            free(check);
            free(str);
        }
        else
            ft_putstr(cmd[i]);
        if (cmd[i + 1] != NULL)
            ft_putstr(" ");
        i++;
    }
    if (b == 0)
        ft_putstr("\n");
}